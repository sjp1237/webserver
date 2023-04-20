#include"webserver.hpp"
#include<signal.h>


webserver* webserver::instant=nullptr;
mutex webserver::m_mutex;


void Util::setnoblocking(int fd)
{
  int oldstat=fcntl(fd,F_GETFL);
  int newstat=oldstat|O_NONBLOCK;
  fcntl(fd,F_SETFL,newstat);
  return;
}

int* Util::m_pipe=NULL;
webserver* webserver::GetInstant()
{
  if(instant==nullptr){
    m_mutex.lock();
   if(instant==nullptr){
    instant=new webserver();
    }
     m_mutex.unlock();
  }
  return instant;
}

webserver::webserver(int port)
 :m_port(port)
{
  m_usrs=new httpconn[MAX_FD];
  try{
    m_threadpool=new threadpool<httpconn>;
     //创建管道
   if(socketpair(AF_UNIX,SOCK_STREAM,0,m_pipe)<0)
   throw "创建管道失败";
 }
 catch(...){
    exit(-1);
 }
 m_tcp=TcpServer::GetTcpServer(port);
 m_listenfd=m_tcp->GetListenfd();;
 m_epollfd=epoll_create(1024);
 timer_list=new sort_timer_list();
 
 timers=new client_data[MAX_FD];
 m_events=new epoll_event[MAX_FD];
 Util::m_pipe=m_pipe;
}

void Util::handler(int arg)
{
  //将信号发送过去
  int save_errno = errno;
  char msg=arg;
  if(send(m_pipe[1],&msg,sizeof(msg),0)==-1){
    cout<<"send error"<<endl;
  }
  errno = save_errno;
  return;
}

void Util::sig_handler(int sig)
{
  struct sigaction sa;
  memset(&sa,'\0',sizeof(sa));
  sa.sa_handler=handler;
  //sa.sa_flags=0;
  sigemptyset(&sa.sa_mask);
  if(sigaction(sig,&sa,NULL)==-1){
    cout<<"webserver.cpp 68 : signaction fail"<<endl;
  }
}

//关闭链接
void webserver::del(int sockfd)
{
  epoll_ctl(m_epollfd,EPOLL_CTL_DEL,sockfd,NULL);
  close(sockfd);
}

//删除epoll对象的数据，并且删除lst_timer上的数据
//关闭连接
void cb_func(client_data* data)
{
  //data->server为NULL
  webserver* server=data->server;
  util_timer* timer=data->timer;
  server->GetTimerList()->del_timer(timer);
  server->del(data->sockfd);//关闭链接,并删除epoll对象上的节点
}

//初始化client_data
void webserver::add_timer(int sockfd)
{
    timers[sockfd].sockfd=sockfd;
    //timers[sockfd].server=this;    
    timers[sockfd].timer=new util_timer();
    timers[sockfd].server=this;
    int curtime=time(NULL); 
    timers[sockfd].timer->expire=curtime+expiretime;
    timers[sockfd].timer->user_data=&timers[sockfd];
    //将新的时间节点插入到链表中
    timers[sockfd].timer->cb_func=cb_func;
    //将新的timer插入到timer节点中
    timer_list->add_timer(timers[sockfd].timer);
    //timer的删除是在定时链表的del_timer接口就已经清除了
    return;
}

//将新连接放入到epoll对象中
//并将event存放到events里面
void webserver::addevent(int sockfd,int m_event=EPOLLIN,bool shot)
{
  epoll_event event;
  event.events=EPOLLET|m_event;
  event.data.fd=sockfd;
  if(shot){
    event.events|=EPOLLONESHOT;
  }
  epoll_ctl(m_epollfd, EPOLL_CTL_ADD,sockfd,&event);  
}

//处理可写事件
//此时的响应已经构建完成
//如果数据发送成功，则将重新将初始化httpconn的数据
//如果发送失败，则断开连接
void webserver::DealWrite(int sockfd)
{
  //此时的响应已经构建完成
  //httpconn调用write，是将响应中的数据一次性发送给对端
  //如果数据发送成功，则将重新将初始化httpconn的数据
  //如果发送失败，则断开连接
  auto httpconn=m_usrs[sockfd];
  if(httpconn.Write()){
    //发送成功
    //调整timer_list节点
    timer_list->adjust_timer(timers[sockfd].timer);
    //清除http中的数据
    httpconn.init();
    //进行下一次的
    addevent(sockfd,EPOLLIN,true);
  }else{
    //发送失败   
    //清除httpconn上的数据
    httpconn.clear();
    del(sockfd);//关闭连接，清除epoll上的节点
    timer_list->del_timer(timers[sockfd].timer);//删除定时链表中的节点
  }
}


void webserver::DealSig()
{
  //将管道中的信号给读取到sig_nums数组中，并将
  char sig_nums[1024];
    int ch;
    int sz=recv(m_pipe[0],sig_nums,sizeof(sig_nums),0);
    if(sz==0){
      return;
    }
    else if(sz<0){
      return;
    }
    else{
      for(int i=0;i<sz;i++)
      {
        switch(sig_nums[i])
        {
          case SIGALRM:
            timeout=true;
            break;
          case SIGTERM:
           stop_server=true;
           break;
        }
      }//for
    }
}

//执行完之后，在设置一个闹钟。
void webserver::DealAlarm()
{
  timer_list->tick();
  alarm(ALARMTIME);
  timeout=false;
}

void webserver::DealNewlinker()
{
   struct sockaddr peer; 
   socklen_t len;
   int fd=accept(m_listenfd,&peer,&len);  
    //并将链接放进lst_timer
   add_timer(fd);
   m_usrs[fd].setfd(fd);
   //将新链接放进epoll对象中
   //将事件记录到events
   addevent(fd,EPOLLIN,true);
}

/*
1. 读取socket缓冲区到read_buffer
2. 将httpconn对象放入到线程池中
3. 调整timer在timers_list中的位置
*/
void webserver::DealRead(int sockfd)
{
  auto& httpusr=m_usrs[sockfd];
  //将缓冲区中的数据给读取上来
  m_usrs[sockfd].Read();
  //将http对象放进线程池中
  m_threadpool->Push(&httpusr);
  //调整lst_timer
  util_timer* timer=timers[sockfd].timer;
  timer_list->adjust_timer(timer);
}


void webserver::DealError(int sockfd)
{
  //错误事件
  //清除httpconn对象上的数据
  //将该sockfd从epoll对象中给删除掉
  //将sockfd从timer_list中给删除掉
  httpconn usr=m_usrs[sockfd];
  usr.init();
  del(sockfd);
  timer_list->del_timer(timers[sockfd].timer);
}

void webserver::Run()
{
  //创建一个数组用于保存所有的客户端信息
  addevent(m_listenfd);
  addevent(m_pipe[0]);
  Util::setnoblocking(m_pipe[1]);
  Util::setnoblocking(m_pipe[0]);

  //设置自定信号函数
  Util::sig_handler(SIGALRM);
  Util::sig_handler(SIGTERM);
  //设置一个闹钟
  alarm(ALARMTIME);
  while(!stop_server)
  {
    int num=epoll_wait(m_epollfd,m_events,MAX_FD,0);
    if(num<0)
    {
      throw std::bad_alloc();
    }
    else if(num==0)
    {
      cout<<"without event"<<endl;
    }
    else{
       for(int i=0;i<num;i++)
       {
         int sockfd=m_events[i].data.fd;
         if(m_events[i].events==EPOLLIN){
          //可读事件    
          //可能是listensock，获取新链接
          //可能是管道发出的信号
          if(sockfd==m_listenfd){    
            //获取到新链接
           DealNewlinker();
          }
          else if(sockfd==m_pipe[0]){
            //处理信号，因为IO操作是比较
            DealSig();//
          }
          else{
            //普通链接的读取操作
            DealRead(sockfd);
          }
         }
         else if(m_events[i].events==EPOLLOUT)
         {
            DealWrite(sockfd);
         }
         else if(m_events[i].events&(EPOLLERR|EPOLLHUP|EPOLLRDHUP)){
          DealError(sockfd);
         }
       }//for
    }//else

    if(timeout)
    {
      //进入链表执行定时tick
      DealAlarm();
    }
  }//while
}