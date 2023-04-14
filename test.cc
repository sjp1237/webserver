#include"httpconn.hpp"
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

void test_parse_read()
{
    httpconn* tmp=new httpconn();
    tmp->read_buffer="post /main http1.1\n\rContent-Length: 8\n\rConnection: keep-alive\n\r\n\ra=19b=20";
    cout<<tmp->read_buffer.size();
    tmp->process_read();
}
int main()
{
  //test_parse_line();
  //test_parse_request_header();
  //test_analy_url();
  test_parse_read();
  return 0;
}

