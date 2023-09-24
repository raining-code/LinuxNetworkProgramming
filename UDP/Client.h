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
class UDPClient {
public:
    UDPClient();
    string Recvform();
    bool Sendto(string message, string ip, uint16_t port);
    ~UDPClient();
private:
    int Socket();
private:
    int sock;
};