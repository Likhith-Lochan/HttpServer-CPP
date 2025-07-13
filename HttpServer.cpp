#include "HttpServer.hpp"


#define BACKLOG 10
#define BUFFER_SIZE 4096

HttpServer::HttpServer(const std::string& ip,int port):ip(ip),port(port),server_fd(-1){}

HttpServer::~HttpServer(){
    if(server_fd!=-1){
        close(server_fd);
    }
}


void HttpServer::setupSocket(){
    server_fd=socket(AF_INET,SOCK_STREAM,0);

    if(server_fd==-1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);

    if(inet_pton(AF_INET,ip.c_str(),&addr.sin_addr)<=0){
        perror("Invalid IP address");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if(bind(server_fd,(struct sockaddr*)&addr,sizeof(addr))<0){
        perror("Bind failed ");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,BACKLOG)<0){
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout<< " Server started and listening on : "<<ip<<":"<<port<<std::endl;

}

void HttpServer::start(){
    setupSocket();
    acceptConnections();
}


void HttpServer::acceptConnections(){

    while(true){

        sockaddr_in client_addr{};
        socklen_t addr_len=sizeof(client_addr);

        int client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addr_len);

        if(client_fd < 0){
            perror(" Accept failed");
            continue;
        }

        std::thread([this,client_fd](){

            handleClient(client_fd);
            close(client_fd);

        }).detach();


    }
}

void HttpServer::handleClient(int client_fd){
    char buffer[BUFFER_SIZE]={0};

    ssize_t bytes_received = recv(client_fd,buffer,BUFFER_SIZE-1,0);

    if(bytes_received<=0){
        perror("Receive failed");
        return ;
    }

    std::string request(buffer);
    std::cout<<"Request : \n"<<request<<"\n";

    std::string method;

    size_t method_end=request.find(' ');

    if(method_end!=std::string::npos){
        method=request.substr(0,method_end);
    }

    std::string body ;
    std::string response;

    if(method == "GET"){
        body="GET method handled";
        response=
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.length()) + "\r\n"
            "\r\n" + body;
    }

    else if(method == "POST"){
        body="POST method handled";
        response=
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.length()) + "\r\n"
            "\r\n" + body;
    }
    
    else if(method == "PUT"){
        body="PUT method handled";
        response=
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.length()) + "\r\n"
            "\r\n" + body;
    }
    else if(method == "DELETE"){
        body = "DELETE method handled";
        response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.length()) + "\r\n"
            "\r\n" + body;
    }
    else{
        body ="Method not allowed";
        response =
            "HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: " + std::to_string(body.length()) + "\r\n"
            "\r\n" + body;
    }

    send(client_fd, response.c_str(), response.length(), 0);
}


