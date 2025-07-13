#ifndef __HTTP_SERVER__
#define __HTTP_SERVER__

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

class HttpServer{
    public:
        HttpServer(const std::string& ip,int port);
        ~HttpServer();

        void start();
    
    private:
        int server_fd;
        std::string ip;
        int port;


        void setupSocket();
        void acceptConnections();
        void handleClient(int client_fd);
};


#endif // __HTTP_SERVER__