#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
#include<unistd.h>
#include<string.h>
using std::cout;
using std::endl;
using std::string;
class UDPServer {
public:
    UDPServer(uint16_t port = 9999);
    ~UDPServer();
    string Recvform(string* ip, uint16_t* port);
    bool Sendto(string message, string ip, uint16_t port);
private:
    int Socket();
    bool Bind(uint16_t port);
private:
    int sock;
};