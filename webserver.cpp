#include"webserver.hpp"




void add(int epoll_fd,int sockfd,int shot);
//关闭链接
int webserver::del(int epoll_fd,int sockfd)
{
  epoll_ctl(epoll_fd,EPOLL_CTL_DEL,sockfd,NULL);
  close(sockfd);
}

void webserver::timer(int sockfd)
{
    timers[sockfd].sockfd=sockfd;
    int curtime=time(NULL);
    timers[sockfd].timer->expire=curtime+expiretime;
    //将新的时间节点插入到链表中
    timer_list->add_timer(timers[sockfd].timer);
}


void webserver::addevent(int sockfd,int events)
{
    events[sockfd].data.fd=sockfd;
    events[sockfd].events=events;
}


int webserver::dealwrite(int sockfd)
{
  //此时的响应已经构建完成
  //httpconn调用write，是将响应中的数据一次性发送给对端
  //如果数据发送成功，则将重新将初始化httpconn的数据
  //如果发送失败，则断开连接
  auto httpconn=usrs[sockfd];
  if(httpconn.Write()){
    //发送成功
    //调整timer_list节点
    timer_list->adjust_timer(timers[sockfd].timer);
    //一次请求完成，初始化http中的成员变量
    httpconn.init();
  }else{
    //发送失败
    //关闭连接，清除epoll上的节点，清除timers中的
    del(m_epollfd,sockfd);
    timer_list->del_timer(timers[sockfd].timer);
  }
}

void webserver::Run()
{
  //创建一个数组用于保存所有的客户端信息
  add(m_epollfd,m_listenfd,1);
  while(true)
  {
    int num=epoll_wait(m_epollfd,events,MAX_FD,0);
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
         int sockfd=events[i].data.fd;
         if(events[i].events==EPOLLIN){
          //可读事件    
          //可能是listensock，获取新链接
          //可能是管道发出的信号
          if(sockfd==m_listenfd){    
            //获取到新链接
            struct sockaddr peer; 
            socklen_t len;
            int fd=accept(m_listenfd,&peer,&len);
            //将新链接放进epoll对象中
            
            add(m_epollfd,fd,1);
            //并将链接放进lst_timer
            timer(fd);
            //将事件记录到events
            addevent(fd,EPOLLIN);
          }
          else if(events[i].data.fd==usrs->pipefd[0]){
            //有信号发生，检查一下lst_timer

          }
          else{
            //将缓冲区的数据读取上来
            auto httpusr=usrs[sockfd];
            usrs[sockfd].Read();
            //将事件放进线程池中
            m_threadpool->Push(&httpusr);
            //调整lst_timer
            timer_list->adjust_timer();
          }
         }
         else if(events[i].events==EPOLLOUT)
         {
          //可写事件
          //此时的响应已经构建完成
          //如果数据发送成功，则将重新将初始化httpconn的数据
          //如果发送失败，则断开连接
          dealwrite(sockfd);
         }
         else if(events[i].events&(EPOLLERR|EPOLLHUP|EPOLLRDHUP)){
          //错误事件
          //将该sockfd从epoll对象中给删除掉
          //将sockfd从timer_list中给删除掉
          del(m_epollfd,sockfd);
          timer_list->del_timer(timers[sockfd].timer);
         }
       }
    }
  }
}