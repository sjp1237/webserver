#ifndef THREADPOOL_H
#define THREADPOOL_H
#include<pthread.h>
#include<list>
#include<iostream>
#include"locker.hpp"
using namespace std;
template<class T>
class threadpool{
  public:
    threadpool(int thread_num=8,int max_requests=2000);
    ~threadpool(); 
    //往队列中添加任务
    bool Push(T* request);
private:
  int m_thread_num;//线程的数量
  //线程数组
  pthread_t* m_threads=nullptr;
  //请求队列中最多允许的，等待处理的请求的数量
  int m_max_requests;
  //工作队列
  std::list<T*> m_workqueue;
  static void* work(void* arg);
  //互斥锁
  locker m_lock;
  sem m_sem;
  //信号量
  //是否结束线程
    
};

 template<class T>
  threadpool<T>::threadpool(int thread_num,int max_requests)
      :m_thread_num(thread_num),
      m_max_requests(max_requests)
  {
    m_threads=new pthread_t[m_thread_num];
    if(m_threads==nullptr){
      throw exception();
    }
    //创建num个线程，并将线程脱离
    for(int i=0;i<m_thread_num;i++){
      if(pthread_create(m_threads+i,NULL,work,this)!=0){
        delete[] m_threads;
        throw exception();
      }
      if(pthread_detach(m_threads[i])!=0){
        delete[] m_threads;
        throw exception();
      }
    }
    //>
  }

  template<class T>
  threadpool<T>::~threadpool(){
     delete[] m_threads; 
  }

  template<class T>
  bool threadpool<T>::Push(T* avg){
    //加锁
    //判断队列中的数量是否大于最大的数量
    //将任务放进队列中
    //解锁
    m_lock.lock();
    if(m_workqueue.size()>m_max_requests){
      return false;
    }
    m_workqueue.push_back(avg);
    m_lock.unlock();
    m_sem.post();
  }

  template<class T>
  void* threadpool<T>::work(void* arg){
    threadpool* tp=(threadpool*) arg;
    while(true){
       //通过信号量来判断是否有任务生成
       //加锁的目的是保证一次只能有一个线程能够进入线程池
       tp->m_sem.wait();
       tp->m_lock.lock();
       if(tp->m_workqueue.empty()){
         tp->m_workqueue.unlock();
         continue;
       }
       T* task=tp->front();
       tp->pop_front();
       tp->m_lock.unlock();

       if(!task){
         continue;
       }

       //任务处理
       //实现一个task任务的处理
    }
  }
#endif
