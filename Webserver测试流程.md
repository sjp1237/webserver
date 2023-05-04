## Webserver测试流程

打 " √ " ,则说明该过程没问题，测试环境是用fiddler给我们的服务器发送数据包：

![image-20230504202400888](C:\Users\A\AppData\Roaming\Typora\typora-user-images\image-20230504202400888.png) 

测试用例：

请求服务器的主页的的主页

```
get / http/1.1
User-Agent: Fiddler
Host: 119.23.41.13:8081
Content-Length: 0
```



### 测试webserver

测试webserver的构造函数：

- 创建epoll；       √
- 创建定时链表；     √
- 创建线程池；         √
- 创建通信管道         √

- #### 创建Tcperver通信  √



## 测试服务器流程

##### 产生SIFALRM信号后测试流程

- 捕捉SIGALRM，SIGTERM信号，设置自定义函数  √
- 当SIGALRM信号触发时，是否调用handler，将信号往m_pipe[1]管道中发送。√
- epoll中是否触发m_pipe[0]管道的事件发生 。√
- 触发m_pipe[0]的事件后是否将m_pipe[0]将管道中信号给读取，并将timeout给设置为true√
- 触发timeout后，进入DealAlarm函数          √
- 调用time_list中的tick遍历整个链表查看是否有节点超时，如果有超时，则执行回调函数cb_func清除epoll中的节点和lst_timer上的节点。         √





#### 获取新链接

listenfd是否触发读事件。   √

进入listenfd将新链接获取上来，并将设定对应的  √

请求后，线程处理process后的response_body结果 √

生成response_body后，能否触发EPOLLOUT  √

测试DealWrite能否正确的将数据发送给客服端.  √

线程池中的线程是否被唤醒，获取到任务     √

获取任务后执行 httpconn 中的 process 生成一个httpconn的报文。√

生成httpconn报文后能否触发socket的写事件   √

触发写事件后调用write函数能否将数据发送给客户端 √





##### 测试将httpconn发送给客户端的流程

1. 判断epoll对象是否收到写事件。

第一次测试：没有触发socket的写事件，原因 ：   

- socket已经添加到epoll对象中，则不能再一次将socket添加到epoll对象，所以获取到写事件，只能通过EPOLL_CTL_MOD将socket

  修改为EPOLLOUT。

第二次测试，成功

2. 调用write能否将httpconn的数据发送给对端                  √

3. 发送完成后，如果是长连接： Connection: keep-alive  √

- 定时链表是否调整                                                              √

- 是否初始化httpconn对象                                                 √

- 将epoll节点设置为读事件。                                             √

- 客户端再一次发送数据，判断是否会再次建立连接（判断listenfd是否被触发）  √

- 客户端处理长连接的第二次请求的时候发生了阻塞，原因 

  由于httpconn在创建的时候没有引用，导致init没有初始化数组的httpconn对象，httpconn对象中的CHECK_STATE没有被初始化。

  <img src="C:\Users\A\AppData\Roaming\Typora\typora-user-images\image-20230423205346403.png" alt="image-20230423205346403" style="zoom:50%;" />1

如果是短链接：

- 删除lst_timer对应的节点              √
- 删除epoll上的节点，并关闭链接  √



### 服务器的压力测试

> Webbench是Linux上一款知名的、优秀的web性能压力测试工具。它是由Lionbridge公司开发。
>
> 测试处在**相同硬件上，不同服务的性能**以及**不同硬件上同一个服务的运行状况。**
>
> 展示服务器的两项内容:**每秒钟响应请求数和每秒钟传输数据量**。

基本原理: Webbench首先 fork出多个子进程，每个子进程都循环做web访问测试。子进程把访问的结果通过pipe告诉父进程，父进程做最终的统计结果。

测试示例：

```c++
./webbench -c 1000 -t 5 http://119.23.41.13:8081/webbench -c 1000 -t 5
```

测试结果：

![image-20230504201840292](C:\Users\A\AppData\Roaming\Typora\typora-user-images\image-20230504201840292.png)



创建1000个客户端，跑5秒钟的结果：

最终结果是，服务器的速度是7704个字节。

