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
#include<mutex>
#define EXPIRETIME 1
#define ALARMTIME 100000
using std::cout;
using std::endl;

//初始化服务器
//1.初始化线程池，epoll对象，lst_timer对象,TcpServer服务器
// httpconn* usrs：存储每个用户的httpconn的信息
//用户数据结构

class webserver;
struct client_data{
  public:
  int sockfd;//文件描述符
  util_timer* timer;//定时器
  webserver* server;
};

class Util{
  public:
  static int* m_pipe;
  static void handler(int arg);
  static void sig_handler(int sig);
  static void setnoblocking(int fd);
};



class webserver{
public:
//添加新的sockfd放进epoll对象中
void Run();

private:
//设计为单例模式---懒汉模式
webserver(int port=8081);
webserver(webserver&)=delete;
public:
   static webserver* instant;
   static webserver* GetInstant();
   static mutex m_mutex;
public:
   //定时链表有关
   //添加新的节点到lst_timer
    void add_timer(int sockfd);
    //epoll有关
    void addevent(int sockfd,int events=EPOLLIN,int op=EPOLL_CTL_ADD,bool flaget=true,bool shot=false);
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

    bool timeout=false;
    bool stop_server=false;

    //在堆区创建空间
    epoll_event* m_events;
    httpconn* m_usrs;
    client_data* timers;

    sort_timer_list* timer_list;
    Util m_utils;
};





