#pragma once
#include<iostream>
#include<string>
#include<mutex>
#include<time.h>


class Config{    
      private:    
        time_t hot_time;//热点时间    
        int server_port;//服务器的端口号    
        std::string ip;//ip地址
        std::string url_prefix;//url的前缀
        std::string pack_dir;//压缩目录                                                                                                                                                     
        std::string back_dir;//文件目录                
        std::string back_file_info;//backfile文件      
        std::string pack_file_suffix;//压缩文件后缀    
      private:                                               
        Config(){                                            
          LoadConfit();                                      
        }                                                    
                                                             
        bool LoadConfit();                         
                                                  
     private:
       static Config* instant;
       static std::mutex lock;
      public:
        static Config* GetInstant(){
          if(instant==nullptr){
            lock.lock();
            if(instant==nullptr){
              instant=new Config();
            }
            lock.unlock();
          }
          return instant;
        }
  
        time_t GetHotTime(){
          return hot_time;
        }
  
        std::string GetIp(){
          return ip;
        }
  
        std::string GetPackFileSuffix(){
          return pack_file_suffix;
        }
  
        std::string GetBackFileInfo(){
          return back_file_info;                                                                                                                                                            
        }
        int GetServerPort(){
          return server_port;
        }
 
       std::string GetUrlPrefix(){
          return url_prefix;
        }
  
        std::string GetPackDir(){
          return pack_dir;
        }
  
        std::string GetBackDir(){
          return back_dir;
        }
    };

