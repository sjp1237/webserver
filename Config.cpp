#include"Config.hpp"
#include"FileUtil.hpp"
bool Config::LoadConfit(){                                   
          sjp::FileUtil fu("./Config.txt");                  
          std::string body;                                  
          fu.GetContent(body);                               
          Json::Value root;                                  
          sjp::JsonUtil::UnSerialize(root,body);                  
                                                             
          hot_time=root["HotTime"].asInt();                  
          server_port=root["ServerPort"].asInt();            
          ip=root["Ip"].asString();                          
          url_prefix=root["UrlPrefix"].asString();           
          pack_dir=root["PackDir"].asString();               
          back_dir=root["BackDir"].asString();               
          back_file_info=root["BackFileInfo"].asString();    
          pack_file_suffix=root["PackFileSuffix"].asString();    
 }          

           
 Config* Config::instant=nullptr;
std::mutex Config::lock;          