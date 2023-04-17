#include"httpconn.hpp"
#include<sys/types.h>
#include<sys/socket.h>
#include<iostream>
#include<string.h>
#include<sys/socket.h>   
#include <sys/stat.h>


#include"tool.hpp"                                                               
//分析url资源
//判断文件是否存在
//判断文件是否是一个可执行文件，如果是一个可执行文件，则调用cgi机制
//判断一个文件是否一个普通文件，则将该文件提前打开，并保存相关文件的fd

void add(int epoll_fd,int sockfd,int shot)
{
  epoll_event event;
  uint32_t events=EPOLLET|EPOLLIN;
  if(shot){
    events|=EPOLLONESHOT;
  }
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD,sockfd,&event);  
}

  void  httpconn::AnalyFile(){
        std::string path=m_request->m_path;
        m_request->m_path="wwwroot";
        m_request->m_path+=path;
        //添加wwwroot前缀
        if(m_request->m_path[m_request->m_path.size()-1]=='/'){
          m_request->m_path+=HOME_PAGE;
          IsSendPage=true;
        }

        struct stat buf;
        if(stat(m_request->m_path.c_str(),&buf)==0){
          if(S_ISDIR(buf.st_mode)){
            //路径是一个目录，打开该目录下的首页信息
            m_request->m_path+="/";
            m_request->m_path+=HOME_PAGE;//HOME_PAGE: index.html
            IsSendPage=true;
          }
          else if(buf.st_mode&S_IXUSR||buf.st_mode&S_IXGRP||buf.st_mode&S_IXOTH){
            //可执行文件
            cgi=true;
            return ;
          }
          else{
            //普通文件
            IsSendPage=true;
          }
        }
        else{
          //找不到该文件
          //打开文件描述符
          m_response->code=NOT_FOUND;//404
          m_request->m_path=NOT_FOUND_PAGE;
          m_response->suffix="html";
          stat(m_request->m_path.c_str(),&buf);
          m_response->content_size=buf.st_size;
          IsSendPage=true;
          return ;
        }
        //文件大小,也就是响应的正文的大小
        m_response->content_size=buf.st_size;
        //查找文件后缀
        int pos=m_request->m_path.rfind(".");
        if(pos>0){
          //文件后缀
          m_response->suffix=m_request->m_path.substr(pos+1);
        }else{
          //文件没有后缀,默认是html
          m_response->suffix="html";
        }
    }
       
//直接将数据读取上来的方式不好，会发生tcp黏包
int httpconn::Read(){
  //缓冲区满了
  if(m_read_idx>=READ_BUFFER_SIZE){
    return false;
  }
  while(true){
    ssize_t size=recv(socket,(void*)read_buffer[m_read_idx],READ_BUFFER_SIZE-m_read_idx,MSG_DONTWAIT);
     if(size==0){
       //对端关闭
       return false;
    }
    else if(size<0){
      if(errno&EAGAIN||errno&EWOULDBLOCK){
        //没有数据了
        break;
      }
      else{
        return false;
      }
    }
    m_read_idx+=size;
    if(m_read_idx>=READ_BUFFER_SIZE){
      break;
    }
  }
  return true;
}

httpconn::HTTP_CODE httpconn::process_write()
{
   //构建响应
   //响应行: http/1.1 响应状态码 响应状态码描述
   //响应报头：Content-Length: 
   //Content-Type: Text/html
   //Connection: keep-alive或者是close
   //将响应数据构建在response_body中
   //构建响应行和响应报头
   
   //
   //缺少添加状态描述符
   BuildReponseLine();
   //缺少添加文件类型的描述
   BuildResponseHeaer();
}

//工作线程进行解析请求
int httpconn::process(){
  //解析请求，并解析对应的url资源
  httpconn::HTTP_CODE res=process_read();
   if(res==httpconn::NO_REQUEST){
       //重新将socket设置进epoll对象中
       add(epoll_fd,socket,true);
       return 0;
   }
   //读取完请求后，解析好请求，接下来构建响应
  res=process_write();
  return 0;
}

//解析请求
httpconn::HTTP_CODE httpconn::process_read(){
  //解析行
  LINE_STATUS line_state=LINE_OK;
  const char * text=nullptr;
  //从读缓冲区读取一行
  while(m_check_state==CHECK_STATE_CONTENT||parse_line()==LINE_OK){
    //获取一行的起始位置
    text=read_line();
    //获取检查的起始位置
    m_start_line=m_check_idx;
    //解析结果
    httpconn::HTTP_CODE ret=NO_REQUEST;
    switch(m_check_state){
      case httpconn::CHECK_STATE_REQUESTLINE:
      {
        //解析请求行
        ret=parse_request_line(text);
        if(BAD_REQUEST==ret){
          return BAD_REQUEST;
        }
        break;
      }

      case httpconn::CHECK_STATE_HEADER:
        //解析请求报头
       ret=parse_request_header(text);
        if(BAD_REQUEST==ret){
          return BAD_REQUEST;
        }
        //请求完整
        else if(GET_REQUEST==ret){
          do_request();
          return httpconn::GET_REQUEST;
        }
        break;
      case httpconn::CHECK_STATE_CONTENT:
        //将正文请求正文的数据读取上来
        ret=parse_request_content();
        if(httpconn::GET_REQUEST==ret){
          do_request();
          return GET_REQUEST;
        }
        break;
    }
  }
  return httpconn::NO_REQUEST;
}
   //调用可执行文件
   //将处理结果返回给主进程，可能为静态网页，也可能是处理是计算结果
   //
  bool httpconn::CgiHandle(){
        //  std::cout<<"CgiHandle .."<<std::endl;
          //利用管道给cgi程序发送数据
          int pipe0[2];//父进程发送给子进程的管道
          int pipe1[2];//父进程接收子进程的管道
          if(pipe(pipe0)!=0){
            std::cout<<"pipe create fail"<<std::endl;
            return false;
          }
          if(pipe(pipe1)!=0){
            std::cout<<"pipe create fail"<<std::endl;
            return false;
          }

        if(fork()==0){
            //子进程
            close(pipe0[1]);//pipe0[0] 子进程用来读
            close(pipe1[0]);//pipe1[1] 子进程用来写
            dup2(pipe1[1],1);
            dup2(pipe0[0],0);
            //程序替换后,所有的数据和代码都会被清空,包括文件描述符，
            //只有环境变量不会替换掉
            //所以通过重定向文件描述符,则子进程可以通过cin向父进程输入数据
            //cout从管道中读取数据
            //子进程需要知道是什么方法来，从而判断是往管道还是环境变量中获取参数
            //子进程需要知道参数的大小，从而判断是否有读漏
            std::string method_env="METHOD=";
            method_env+=m_request->m_method;
            putenv((char*)method_env.c_str());
            if(m_request->m_method==Request::GET){
              std::string parameter="PARAMETER=";
              parameter+=m_request->m_parameter;
              putenv((char*)parameter.c_str());
            }
            else if(m_request->m_method==Request::POST){
              std::string body_size="Content-Length=";
              body_size+=std::to_string(m_request->m_content_len);
              putenv((char*)body_size.c_str());
          }
          //程序替换
          execl(m_request->m_path.c_str(),m_request->m_path.c_str(),NULL);  
        }
        else{
            //父进程
            close(pipe0[0]);//pipe0[1]用来写数据给子进程
            close(pipe1[1]);//pipe1[0]读取子进程中的数据
            if(m_request->m_method==Request::POST){
            auto& content=m_request->content;
            //std::cout<<"content:"<<content<<std::endl;
             int sumsize=0;
             while(true){
              //将请求正文发送给子进程
              int size=content.size();
              int sz=write(pipe0[1],content.c_str()+sumsize,size);
              if(sz>0){
                sumsize+=sz;
                if(sumsize==m_request->m_content_len)
                  break;
              }
              else{
                //写失败
                cout<<"父进程向子进程发送数据失败"<<endl;
                break;
              }
            }
          }

          //父进程读取子进程的处理结果
          while(true){
              char ch;
              int sz=read(pipe1[0],&ch,1);
              if(sz>0){
                //读取成功
                m_response->cgi_res.push_back(ch);
              }else{
                //对端关闭
                break;
              }
            }//while
            //IS-SendPage: trueX 
            auto& cgi_res=m_response->cgi_res;
            int begin1=cgi_res.find(": ")+2;
            int end1=cgi_res.find("X");

            std::string is_sendpage=m_response->cgi_res.substr(begin1,end1-begin1);
            // LOG(INFO,is_sendpage.c_str());
            if(is_sendpage=="true"){
              //发送静态网页
              //Page-index:wwwroot/regisuccess.htmlX
              IsSendPage=true;
              int begin2=cgi_res.find(": ",end1+1)+2;
              int end2=cgi_res.find("X",begin2);
              std::string page_index=cgi_res.substr(begin2,end2-begin2);
              m_response->fd=open(page_index.c_str(),O_RDONLY);
              struct stat buf;
              stat(page_index.c_str(),&buf);
              //最终content_size大小为文件
              m_response->content_size=buf.st_size;
            }
            else{
              //请求正文
              m_response->response_content=cgi_res;
              m_response->content_size=m_response->cgi_res.size();
              //std::cout<<"response_body:"<<response.response_body<<std::endl;
            }
            close(pipe0[1]);
            close(pipe1[0]);
        }      
 }


bool httpconn::AnalyUri(){
   //将url中的路径和参数给区分开来
    std::string& uri=m_request->m_url;
    //不管是Get方法还是Post方法,只要没找到"?", 则说明uri中一定没有参数
    if(uri.find("?")!=-1){
    //说明uri中带参数
    std::string seq="?";
    Tool::CuttingString(uri,m_request->m_path,m_request->m_parameter,seq);
    }else{
      //没有找到?,说明uri只有路径
       m_request->m_path=uri;    
    }
}

void httpconn::OpenPage()
{
  fd=open(m_request->m_path.c_str(),O_RDONLY);
  if(fd<0){
    //打开失败
    
  }
}


int httpconn::do_request()
{
  //将url中的路径和参数给分开来
  AnalyUri();
  //解析资源
  //判断文件是否存在
  //判断文件是否是一个可执行文件，如果是一个可执行文件，则调用cgi机制
  //判断一个文件是否一个普通文件，则将该文件提前打开，并返回相关文件的fd
  AnalyFile();
  if(cgi)
  {
    //处理cgi文件
     CgiHandle();
  }else if(IsSendPage){
    //处理发送静态网页
    OpenPage();
  }
}

  void httpconn::BuildReponseLine(){
        //构建响应行,版本 状态码 状态码描述
        m_response->response_body+="HTTP/1.0";
        m_response->response_body+=" ";
        m_response->response_body+=m_response->code;
        m_response->response_body+=" ";
        m_response->response_body+=code_desc[m_response->code];
        m_response->response_body+=BLANK;
        //std::cout<<response.response_line<<std::endl;
  }


    //构建请求报头
    void httpconn::BuildResponseHeaer(){
        //构建Content-Type:        
        std::string content_type="Content-Type: ";
        content_type+=suffix_type[m_response->suffix];
        content_type+=BLANK;
        m_response->response_body+=content_type;
        //构建Content-Length
        //非cgi的响应正文是文件的大小
        //cgi处理的响应正文是cgi程序处理的结果
        //构建响应
        std::string content_size="Content-Length: ";
        content_size+=std::to_string(m_response->content_size);
        content_size+=BLANK;
        m_response->response_body+=content_size;

        std::string connection="Connection: ";
        if(m_linger)
        {
          connection+="keep-alive";
        }
        else{
          connection+="close";
        }
        connection+=BLANK;
        m_response->response_body+=connection;
        m_response->response_body+=BLANK;
  }

//测试成功
//测试用例：abcdef abcdef\r\n abcdef\r
httpconn::LINE_STATUS httpconn::parse_line(){
  //从缓冲区中读取一行数据
  //遇到\r\n就停止
  //xxxxxx\n\rxxxxxx\n\r
  //m_check_idx检查缓冲区的位置
  //m_read_idx读取缓冲区的位置
  for( ;m_check_idx<read_buffer.size();m_check_idx++){
      if(read_buffer[m_check_idx]=='\n'){
        if(m_check_idx+1>=read_buffer.size()){
          return LINE_OPEN;
        }
        else if(read_buffer[m_check_idx+1]=='\r'){
             //完整行
              read_buffer[m_check_idx++]='\0';
              read_buffer[m_check_idx++]='\0';
              return LINE_OK;
        }
        else{
          return LINE_BAD;
        }
      }
      else if(m_check_idx>0&&read_buffer[m_check_idx+1]=='\r'){
           read_buffer[m_check_idx-1]='\0';
           read_buffer[m_check_idx++]='\0';
           return LINE_OK;
      }
  }
  return LINE_OPEN;
}

//测试成功
httpconn::HTTP_CODE  httpconn::parse_request_line(std::string text){
    int pos=text.find(' ');
    if(pos==std::string::npos){
      return BAD_REQUEST;
    }
    //解析出请求方法
   // cout<<text.substr(0,pos)<<endl;
    if(text.substr(0,pos)=="get"){
       m_request->m_method=Request::GET;
    }
    else if(text.substr(0,pos)=="post"){
      m_request->m_method=Request::POST;
    }
    else{
      return BAD_REQUEST;
    }

    //解析出url
    int pos1=text.find(' ',pos+1);
    m_request->m_url=text.substr(pos+1,pos1-pos-1);
    m_request->m_version=text.substr(pos1+1);
    auto& url= m_request->m_url;  
    m_check_state=CHECK_STATE_HEADER;
 }

//解析请求报头
//测试成功
 httpconn::HTTP_CODE httpconn::parse_request_header(std::string text){
     if(text[0]=='\0'){
      //遇到空行
      //如果请求正文不等于0，则需要解析请求正文
      if(m_request->m_content_len!=0){
        m_check_state= CHECK_STATE_CONTENT;
        return NO_REQUEST;
      }
      return GET_REQUEST;
     }

     //查找": ”
     int pos=text.find(":");
     if(pos==std::string::npos){
       return NO_REQUEST;
     }

     if(text.substr(0,pos)=="Content-Length"){
       const char* tmp=(const char*)(&text[pos+2]);
       int comtent_len=atoi(tmp);
        m_request->m_content_len=comtent_len;
        return NO_REQUEST;
     }

     if(text.substr(0,pos)=="Connection"){
        string tmp=text.substr(pos+2);
        if(strcmp(tmp.c_str(),"keep-alive")==0){
            m_linger=true;
            return NO_REQUEST;
        }
     }

    if(text.substr(0,pos)=="Host"){   
        m_request->m_host =text.substr(pos+2);
        return NO_REQUEST;
    }
    return NO_REQUEST;
}

httpconn::HTTP_CODE httpconn::parse_request_content()
{
    //读取请求正文
    //通过content-Length去判断是否读取完毕
    //请求中的正文read_buffer.size()-m_check_idx
    if(read_buffer.size()-m_check_idx<m_request->m_content_len){
      return NO_REQUEST;
    }else{
      m_request->content=read_buffer.substr(m_check_idx,m_request->m_content_len);
      return GET_REQUEST;
    }
}

//生成请求报头
bool httpconn::Write()
{
  //先发送response_body后，
  //判断响应正文是发送静态网页还是发送response_content
  int start=0;
  auto& response_body=m_response->response_body;
  //发送响应报头完成
  while(true)
  {
     //发送response_body
     int len=response_body.size()-start;
     int size=send(socket,response_body.c_str()+start,len,0);
     if(size==0)
     {
          if(size>0){
            start+=size;
            if(start==response_body.size())
              break;
          }else{
            //发送失败
            return false;
          }
     }
  }

  while(true)
  {
    if(IsSendPage)
    {
        if(m_response->fd!=-1){
         int content_size=m_response->content_size; 
         //std::cout<<"content_size: "<<content_size<<std::endl;
         off_t start=0;
         while(true){
           int size=sendfile(socket,m_response->fd,&start,content_size);
           if(start+size>=content_size){
             break;
           }
           if(size<0){
            //发送失败
            return false;
           }
         }          
        //LOG(INFO,"send page success! ");
       }
    }
    else if(cgi)
    {
      //发送cgi处理结果
      start=0;
      auto& response_content=m_response->response_content;
      while(true)
      {
      int len=response_content.size()-start;
      int size=send(socket,response_content.c_str()+start,len,0);
      if(size==0)
      {
          if(size>0){
            start+=size;
            if(start==response_content.size())
              break;
          }else{
            //发送失败
            return false;
          }
      }
    }
  }
 }
  return true;
}


void httpconn::init()
{
  m_request->init();
  m_response->init();
  m_read_idx=0;
  m_read_start=0;
  m_check_idx=0;
  m_line_idx-0;
  m_start_line=0;
  m_check_state=CHECK_STATE_REQUESTLINE;
  m_start_content=0;
  m_linger=false;
  file_size=0;
  IsSendPage=false;
  cgi=false;

  write_buffer.clear();
  read_buffer.clear();
}