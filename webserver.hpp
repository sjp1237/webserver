#pragma once 
#include"lst_timer.h"
#include"TcpServer.hpp"
#include"httpconn.hpp"
#include"threadPool.hpp"
#include<iostream>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>
#define EXPIRETIME 5
using std::cout;
using std::endl;

//初始化服务器
//1.初始化线程池，epoll对象，lst_timer对象,TcpServer服务器
// httpconn* usrs：存储每个用户的httpconn的信息
//

class webserver{
public:
//添加新的sockfd放进epoll对象中
void Run();

webserver(int port)
 :m_port(port)
{
  try{
    m_threadpool=new threadpool<httpconn>;
     //创建管道
   if(socketpair(m_pipe)<0)
   throw "创建管道失败";
   
 }
 catch(...){
    exit(-1);
 }
 m_tcp=TcpServer::GetTcpServer(port);
 m_listenfd=m_tcp->GetListenfd();;
 m_epollfd=epoll_create(0);
 timer_list=new sort_timer_list();
 m_usrs=new httpconn[MAX_FD];
 timers=new client_data[MAX_FD];
 m_events=new epoll_event[MAX_FD];
 Util::m_pipe=m_pipe;
}

   //定时链表有关
   //添加新的节点到lst_timer
    void add_timer(int sockfd);

    //epoll有关
    void addevent(int sockfd,int events,bool shot=false);
    //关闭链接
    void del(int sockfd);
   // static void* ThreadRun(void* arg);
   // void Getnewlink();
    void DealSig();
    void DealNewlinker();
    void DealAlarm();
    void DealWrite(int sockfd);
    void DealRead(int sockfd);
    void DealError(int sockfd);

    sort_timer_list* GetTimerList(){
      return timer_list;
    }
  private:
    int m_port;
    int m_epollfd;
    int m_listenfd;
    int expiretime=EXPIRETIME;
    TcpServer* m_tcp;
    threadpool<httpconn>* m_threadpool;
    int threadnum;

    int m_pipe[2];//信号的管道
    int over_time;

    bool timeout=true;
    bool stop_server=true;
    epoll_event* m_events;
    httpconn* m_usrs;
    client_data* timers;

    sort_timer_list* timer_list;
    Util m_utils;
};


class Util{
  public:
  static int* m_pipe;
  static void handler(int arg);
  static void sig_handler(int sig);
  static void setnoblocking(int sig);
};

int* Util::m_pipe=NULL;
//用户数据结构
struct client_data{
  public:
  int sockfd;//文件描述符
  util_timer* timer;//定时器
  webserver* server;
};