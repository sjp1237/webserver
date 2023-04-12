#include"httpconn.hpp"
using namespace std;

int main()
{
  cout<<"test"<<endl;
  httpconn* t=new httpconn();
  cout<<"test1"<<endl;

  std::string s="get /wwwroot http1.1";
  cout<<"test2"<<endl;

  t->parse_request_line(s);
  cout<<"test3"<<endl;

  std::cout<<t->m_request->m_url<<endl;
  cout<<"test4"<<endl;

  cout<<t->m_request->m_method<<endl;
  
  return 0;
}

