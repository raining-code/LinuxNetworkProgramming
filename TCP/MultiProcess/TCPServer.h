#pragma once
#include<iostream>
#include<string>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
using std::cout;
using std::endl;
using std::string;
class TCPServer {
public:
    TCPServer(uint16_t port = 8080, int queueMaxLen = 20);
    ~TCPServer();
    int Accept(string* ip, uint16_t* port);//获取新连接
private:
    int Socket();
    bool Bind(uint16_t port);
    bool Listen(int QueueMaxLen = 20);//设置全连接队列的最大长度
private:
    int sock;
};