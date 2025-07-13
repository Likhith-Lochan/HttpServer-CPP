#include "HttpServer.hpp"

int main(){
    HttpServer server("0.0.0.0",8080);
    server.start();
    return 0;
}