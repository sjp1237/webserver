#pragma once
#include<iostream>
using namespace std;


class util_timer;

class client_data;

//定时器
class util_timer{
  public:
   util_timer* pre;
   util_timer* next;
   time_t expire;//任务超时时间
   //任务回调
   void (*cb_func)(client_data*);//任务回调函数
   client_data* user_data;
  public:
   util_timer():pre(nullptr),next(nullptr){}   
};


//定时器链表,是一个升序的双向链表
class sort_timer_list{
  public:
    sort_timer_list();
    ~sort_timer_list();

    //将目标定时器添加到链表当中
    //add_timer测试完毕
    void add_timer(util_timer* timer);
      
    //将timer插入到lst_head后面部分的链表中
    void add_timer(util_timer* timer,util_timer* lst_head);
    //判断timer放在最后面
    void adjust_timer(util_timer* timer); 
    //SIGALARM信号每次被触发就在信号处理函数中执行以此tick函数
    //处理链表上到期的任务
    void tick();
    void del_timer(util_timer* timer);
  private:
    util_timer* head;
    util_timer* tail;
};



