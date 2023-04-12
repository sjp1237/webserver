#include<iostream>
using namespace std;


class util_timer;

//用户数据结构
struct client_data{
  int sockfd;//文件描述符
  util_timer* timer;//定时器
};


//定时器
class util_timer{
  public:
   util_timer* pre;
   util_timer* next;
   time_t expire;//任务超时时间
   void (*cb_func)(client_data*);//任务回调函数
   client_data* user_data;
  public:
   util_timer():pre(nullptr),next(nullptr){}   
};


//定时器链表,是一个升序的双向链表
class sort_timer_list{
  public:
    sort_timer_list():head(nullptr),tail(nullptr){}
    ~sort_timer_list(){
      util_timer*  cur=head;
      while(cur!=NULL){
        util_timer* tmp=cur;
        cur=cur->next;
        delete tmp;
      }
    }
    //将目标定时器添加到链表当中
    void add_timer(util_timer* timer){
      //如果目标定时器超时时间小于当前链表中所有定时器的超时时间
      //把该定时器插入到链表的头部，作为链表的新的头节点
      //否则调用重载函数add_timer,把它插入到链表中合适的位置，以保证升序的特性
      
      if(!timer)
      return;
      //如果链表为空，则将head和tail设置为timer；
      if(head==nullptr)
      {
         head=tail=timer;
         head->next=tail;
         tail->pre=head;
         return;
      }

      //timer的超时时间比head还要小，则将timer插入到链表的最前面
      if(head->expire>=timer->expire){
        timer->next=head;
        head->pre=timer;
        head=timer;
        return;
      }
      //将timer插入到head的后面
      add_timer(timer,head);
      return;
    }

    //将timer插入到lst_head后面部分的链表中
    void add_timer(util_timer* timer,util_timer* lst_head){
       //找到超时时间比timer小的节点next_timer的节点，然后插入到next_timer该节点前面
       if(!timer||!lst_head){
        return;
       }

       util_timer* next_timer=lst_head->next;

       while(next_timer)
       {
         if(timer->expire<=next_timer->expire)
         {
           lst_head->next=timer;
           timer->pre=lst_head;
           timer->next=next_timer;
           next_timer->pre=timer;
           return;
         }
         lst_head=next_timer;
         next_timer=lst_head->next;
       }

       //如果timer比最后一个节点的时间还要长，则将该节点插入到末尾
       lst_head->next=timer;
       timer->pre=lst_head;
       tail=timer;
       return;
    }

    //如果某一个节点被改变，调整该节点在链表中的位置
    void adjust_timer(util_timer* timer)
    {
      //如果timer是head或者为空，则不需要改变
      if(!timer){
        return;
      }

      //如果timer等于最后一个节点，或者timer节点超时时间小于下一个节点的超时时间，则不需要改变
      if(timer==tail||timer->next->expire>=timer->expire){
        return; 
      }

      util_timer* next_timer=timer->next;
      util_timer* pre_timer=timer->pre;
      //连接两个节点
      next_timer->pre=pre_timer;
      pre_timer->next=next_timer;
      //将timer节点放在next_timer的后面
      add_timer(timer,next_timer);
    }

    //
    void del_timer(util_timer* timer){
      if(!timer){
        return;
      }

      //只有一个节点
      if(head->next==tail&&tail==timer){
        delete head;
        head=nullptr;
        tail=nullptr;
        return;
      }

      //如果该节点是头头节点
      if(timer==head){
        //删除头节点
        util_timer* next_timer=head->next;
        delete timer;
        timer=nullptr;
        head=next_timer;
      }


      if(timer==tail){
        util_timer* pre_timer=tail->pre;
        delete timer;
        timer=nullptr;
        tail=pre_timer;
      }
      util_timer* next_timer=timer->next;
      util_timer* pre_timer=timer->pre;
      next_timer->pre=pre_timer;
      pre_timer->next=next_timer;
      delete timer;
      timer=nullptr;
      return;
    }
    //SIGALARM信号每次被触发就在信号处理函数中执行以此tick函数
    //处理链表上到期的任务
    void tick(){
      //获取当前系统时间
      int cur_time=time(NULL);

      //遍历每一个节点的时间
      //如果当前时间小于节点的超时时间则跳出
      //如果大于当前时间，则调用处理函数，将删除该节点
      util_timer* cur_timer=head;
      while(cur_timer)
      {
         if(cur_timer->expire<=cur_time){
          //当前时间大于节点的超时时间,则说明该节点超时
          //调用回调函数
          cur_timer->cb_func(cur_timer->user_data);
          util_timer* next_timer=cur_timer->next;
          delete cur_timer;
          head=next_timer;;
          cur_timer=head; 
         }else{
          break;
         }
      }
      return;
    }
  private:
    util_timer* head;
    util_timer* tail;
};



