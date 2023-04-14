#pragma once
#include<unordered_map>
#include<vector>
#include<sys/socket.h>                                                                
#include<iostream>              
#include<string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include<sys/epoll.h>
#include"lst_timer.h"

#define HOME_PAGE "index.html"
#define NOT_FOUND_PAGE "wwwroot/404.html"
#define NOT_FOUND "404"
#define OK "200"
#define BLANK "\r\n"
#define MAX_FD 1024
static std::unordered_map<std::string,std::string> suffix_type{{"html","text/html"}};
 class Request{
    public:
     enum METHOD
    {
        GET = 0,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATH
    };
    void init()
    {
      m_request_line.clear();
      m_url.clear();
      m_version.clear();
      m_path.clear();
      m_parameter.clear();
      m_host.clear();
      m_content_len=0;
      content.clear();
    //  request_header.clear();
     // header_map.clear();

      m_content_pos=0;
    }
      std::string m_request_line;
      METHOD m_method;        //请求方法
      std::string m_url;      //url
      std::string m_version;  //请求版本
      std::string m_path;     //请求路径
      std::string m_parameter;//参数
      std::string m_host;   //主机名
      int m_content_len;   //请求正文的大小
      int m_content_pos; //读取请求正文的下标
      std::string content; //请求正文
     // std::vector<std::string> request_header;
      //存储响应报头
    //  std::unordered_map<std::string,std::string> header_map;              
  };

 class Response{    
    public:    
      std::string response_line;    
      std::string version;    
      std::string code="200";    
      std::string code_des;    
      int fd;//网页文件的打开    
      std::string suffix;//后缀    
      int content_size; //响应正文的大小
      std::string response_body;//响应行+响应报头
      std::string response_content;//响应正文

      std::string cgi_res;
      int size=0;//整个响应报文的大小

      void init()
      {
        response_line.clear();
        version.clear();
        response_body.clear();
        response_content.clear();
        cgi_res.clear();
        content_size=0;
        size=0;
      }
      ~Response(){          
      }    
  };    


class httpconn{
    static const int FILENAME_LEN = 200;
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SIZE = 1024;
  public:
  util_timer timers[MAX_FD];
  int pipefd;
  public:
    httpconn()
    {
      m_request=new Request();
      m_response=new Response();
    }
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,//解析请求行
        CHECK_STATE_HEADER=1,         //解析请求报头	
        CHECK_STATE_CONTENT=2        //解析消息体
    };

    enum HTTP_CODE
    {
        NO_REQUEST,              //请求不完整
        GET_REQUEST,            //	获得了完整的HTTP请求
        BAD_REQUEST,             //HTTP请求报文有语法错误
        NO_RESOURCE,            //没有请求资源
        FORBIDDEN_REQUEST,      //资源被禁止访问
        FILE_REQUEST,           //文件请求
        INTERNAL_ERROR,          
        CLOSED_CONNECTION       //关闭链接
    };

    enum LINE_STATUS
    {
        LINE_OK = 0,  //完整读取一行
        LINE_BAD,     //报文语法有误
        LINE_OPEN     //读取的行不完整
    };
    
    
  public:
    //从读缓冲区中读取一行数据
    LINE_STATUS parse_line();
    //返回一行的起始位置
    const char* read_line(){
      return read_buffer.c_str()+m_start_line;
    }
    int Read();//将缓冲区中的数据读取到read_buffer中
    //处理read_buffer中的数据,有限状态机处理

    //将response中的response_body和response_content中的数据发送给对端
    bool Write();
    //由工作线程进行工作
    int process(); 

    //解析http请求
    HTTP_CODE process_read();
    //构建响应
    HTTP_CODE process_write();
    //解析请求报头
    HTTP_CODE parse_request_header(std::string text);
    //解析请求正文
    HTTP_CODE parse_request_content();
    //解析文件
    //do_request中的cgihandle没有测试完成，其余的测试好了
    int  do_request();
    bool CgiHandle();
  private:
    //将url中的路径和参数给分离开来
    //分析文件
    void init();

    private:
    //测试成功的接口
    bool AnalyUri();
    void  AnalyFile();
    HTTP_CODE parse_request_line(std::string text); 
  public:

    Request* m_request;
    Response* m_response;
    std::string read_buffer;
  private:
    
    void BuildReponseLine();
    void BuildResponseHeaer();
    
    std::string write_buffer;
    size_t m_read_idx;//保存read_buffer指向的位置
    size_t m_read_start;//保存read_buffer的起始位置
    size_t m_check_idx;//检查缓冲区的位置
    int m_line_idx;//当前解析行的位置
    size_t m_start_line;//当前行的起始位置
    CHECK_STATE m_check_state;//记录解析哪个位置,请求行，请求报头，请求正文
    size_t m_start_content;
    int socket;
    bool m_linger=false;

    int file_size=0;//发送静态网页的大小
   // int fd;//发送静态网页的文件描述符
    bool IsSendPage=false;
    bool cgi=false;
    int epoll_fd;
};
<<<<<<< HEAD

//master
=======
//测试
>>>>>>> sjp
