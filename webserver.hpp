#pragma once 
#include"lst_timer.h"
#include"TcpServer.hpp"
#include"httpconn.hpp"
#include"threadPool.hpp"
#include<iostream>
#include<signal.h>

#include<unistd.h>
#define EXPIRETIME 5
using std::cout;
using std::endl;

class webserver{
public:
//添加新的sockfd放进epoll对象中

//关闭链接
int del(int epoll_fd,int sockfd);

int dealwrite(int sockfd);
webserver(int port)
 :m_port(port)
{
  try{
    m_threadpool=new threadpool<httpconn>;
  }
  catch(...){
    exit(-1);
  }

 m_tcp=TcpServer::GetTcpServer(port);
 m_listenfd=m_tcp->GetListenfd();;
 m_epollfd=epoll_create(0);
 usrs=new httpconn[MAX_FD];
 timers=new client_data[MAX_FD];
 timer_list=new sort_timer_list();
 events=new epoll_event[MAX_FD];
}
   //添加新的节点到lst_timer
    void timer(int sockfd);
    void Run();
    void addevent(int sockfd,int events);
    private:
    int m_port;
    int m_epollfd;
    int m_listenfd;
    int expiretime=EXPIRETIME;
    TcpServer* m_tcp;
    threadpool<httpconn>* m_threadpool;
    int threadnum;
    
    httpconn* usrs;
    client_data* timers;
    sort_timer_list* timer_list;
    epoll_event* events;
    int pipe[2];
};