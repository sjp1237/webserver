#pragma once
#include"Config.hpp"   
#include<unordered_map>
#include<vector>
#include<string>
class FileInfo{                         
      public:                                 
        bool pack_sign;    
        size_t file_size;                               
        time_t access_time;    
        time_t modify_time;       
        std::string back_path;    
        std::string pack_path;                      
        std::string url;                     
      public:                     
        FileInfo(const std::string& backpath){                     
          AddFileInfo(backpath);                                   
        }                                                         
        FileInfo(){}                                              
        bool AddFileInfo(const std::string& backpath);                       
}; 


 class FileInfoManger{
    private:
      std::string file_info_path;//存储文件信息的持久化文件
      std::unordered_map<std::string,FileInfo> _table; //backpath-info
      pthread_rwlock_t _rwlock;//读写锁
    private:
      static FileInfoManger* instant;
      static std::mutex lock;
    private:
      FileInfoManger(){
        file_info_path=Config::GetInstant()->GetBackFileInfo();
        pthread_rwlock_init(&_rwlock,NULL);
        InitLoad(); 
        UpdatePackSign();
      }

      FileInfoManger(FileInfoManger&)=delete;
    public:
      bool UpdateFileInfo();
      bool UpdatePackSign();
      static FileInfoManger* GetInstant(){    
          if(instant==nullptr){    
            lock.lock();    
            if(instant==nullptr){    
              instant=new FileInfoManger();    
            }    
            lock.unlock();    
          }    
          return instant;    
        }              
      //插入信息
      bool Insert(const FileInfo& info);
        
      //更新信息
      bool update(const FileInfo& info);
        
      //通过backpath判断该文件是否存在
      bool Exist(const std::string& backpath);
  

      //通过url获取文件信息
      bool GetoneByURL(const std::string& url,FileInfo& info);
      

      //通过相对路径获取文件信息
      bool GetOneByRealPath(const std::string& backpath,FileInfo& info);
 

      //获取所有文件的属性信息
      bool GetAllInfo( std::vector<FileInfo>& arry);
      
      //将table上的所有信息存储持久化到文件上
      bool Storage();
      //将文件的备份信息反序列化字符并组织到body上
      //将文件上的信息加载到内存中
      bool InitLoad();

      ~FileInfoManger(){
        Storage();
      }
  };
  