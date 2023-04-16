#include"httpconn.hpp"
#include"lst_timer.h"
#include"TcpServer.hpp"
using namespace std;


// void test_parse_line()
// {
//   cout<<"test"<<endl;
//   httpconn* t=new httpconn();
//   cout<<"test1"<<endl;

//   std::string s="get /wwwroot http1.1";
//   cout<<"test2"<<endl;

//   t->parse_request_line(s);
//   cout<<"test3"<<endl;

//   std::cout<<t->m_request->m_url<<endl;
//   cout<<"test4"<<endl;
//   cout<<t->m_request->m_method<<endl;
// }

// void test_parse_line(){
//   httpconn* tmp=new httpconn();
//   tmp->read_buffer="abcdef";
//   tmp->parse_line();
//   tmp->parse_line();
//   tmp->parse_line();
//   return;
// }


// void test_parse_request_header()
// {
//    httpconn* tmp=new httpconn();
//  //  string text="Content-Length: 18";
//    string text1="Connection: keep-alive";
//   // string text2="Host: 8081";

//   //tmp->parse_request_header(text);
//    tmp->parse_request_header(text1);
//   // tmp->parse_request_header(text2);
// }

void test_analy_url()
{
    // httpconn* tmp=new httpconn();
    // tmp->read_buffer="post /main http1.1\n\rContent-Length: 18\r\nConnection: keep-alive\r\n\r\na=19b=20";
    //tmp->parse_request_line(s);
    //AnalyUri测试成功
    //AnalyFile测试成功
   // tmp->AnalyUri();
  //  tmp->AnalyFile();
   // tmp->do_request();
}

// void test_parse_read()
// {
//     httpconn* tmp=new httpconn();
//     tmp->read_buffer="get /CMakeCache.txt http1.1\n\rContent-Length: 0\n\r\n\r";
//     tmp->read_buffer="get /1111.txt http1.1\n\rContent-Length: 0\n\r\n\r";

//     cout<<tmp->read_buffer.size();
//     tmp->process();
// }


// void test_lst_timer()
// {
//   sort_timer_list* lst=new sort_timer_list();
//   //测试add_timer接口
//   util_timer* ut1=new util_timer();
//   util_timer* ut2=new util_timer();
//   util_timer* ut3=new util_timer();
//   util_timer* ut4=new util_timer();
//   util_timer* ut5=new util_timer();

//   ut1->expire=1;
//   ut2->expire=2;
//   ut3->expire=4;
//   ut4->expire=3;
//   ut5->expire=0;

//   lst->add_timer(ut1);
//   lst->add_timer(ut2);
//   lst->add_timer(ut3);
//   lst->add_timer(ut4);
//   lst->add_timer(ut5);
//   // ut2->expire=6;
//   // lst->adjust_timer(ut2);
//  lst->del_timer(ut3);
//  lst->del_timer(ut5);
// }


void test_tcp_server()
{
  TcpServer* tcp=TcpServer::GetTcpServer(8081);
  int sockfd=tcp->GetListenfd();
  int fd=tcp->Accept();
  string s="http/1.1 200 OK\r\n\r\n";
  int size=send(fd,s.c_str(),s.size(),0);
  cout<<size<<endl;
  return;
}
int main()
{
  //test_parse_line();
  //test_parse_request_header();
  //test_analy_url();S
  //test_parse_read();
  //test_lst_timer();
  test_tcp_server();
  return 0;
}

