cmake_minimum_required(VERSION 3.10)
project(HttpServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(http_server
   main.cpp
   HttpServer.cpp
   )