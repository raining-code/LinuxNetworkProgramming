#include"Client.h"
UDPClient::UDPClient() {
    sock = Socket();
    if (sock == -1) {
        cout << "创建套接字失败" << endl;
    }
}
string UDPClient::Recvform() {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    socklen_t len = sizeof(serverAddr);
    char message[BUFSIZ] = { 0 };
    size_t size = recvfrom(sock, message, BUFSIZ - 1, 0/*表示阻塞*/, reinterpret_cast<struct sockaddr*>(&serverAddr), &len);
    if (size == -1) {
        cout << "读取错误" << endl;
    }
    else {
        message[size] = 0;
    }
    return message;
}
bool UDPClient::Sendto(string message, string ip, uint16_t port) {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(inet_addr(ip.c_str()));
    int ret = sendto(sock, message.c_str(), message.length(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        cout << "发送失败" << endl;
        return false;
    }
    return true;
}
UDPClient::~UDPClient() {
    close(sock);
}
int UDPClient::Socket() {
    return socket(AF_INET, SOCK_DGRAM, 0);
}
