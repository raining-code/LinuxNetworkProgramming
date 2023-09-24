#pragma once
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<iostream>
#include<string>
#include<unistd.h>
#include<string.h>
using std::cout;
using std::endl;
using std::string;
class TCPClient {
public:
    TCPClient();
    ~TCPClient();
    bool Write(string message);
    string Read();
    bool Connect(string ip, uint16_t port);
private:
    int Socket();
private:
    int sock;
};