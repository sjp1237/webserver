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


void test_parse_request_header()
{
   httpconn* tmp=new httpconn();
   string text="Content-Length: 18";
   tmp->parse_request_header(text);

}
int main()
{
  //test_parse_line();
  test_parse_request_header();
  return 0;
}

