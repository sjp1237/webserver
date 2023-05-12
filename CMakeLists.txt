cmake_minimum_required(VERSION 2.8.12.2)

project(TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE  Debug)
include_directories(/home/sjp/webserver) 
add_executable(test FileInfo.cpp test.cc httpconn.cc tool.cc webserver.cpp TcpServer.cc lst_timer.cc bundle.o  FileUtil.cpp Config.cpp )
target_link_libraries(test pthread jsoncpp stdc++fs)