#include"TCPServer.h"

TCPServer::TCPServer(uint16_t port, int queueMaxLen) {
    sock = Socket();
    if (sock < 0) {
        cout << "创建套接字失败" << endl;
        exit(0);
    }
    if (Bind(port) == false) {
        cout << "绑定失败" << endl;
        exit(0);
    }
    if (Listen(queueMaxLen) == false) {
        cout << "监听失败" << endl;
        exit(0);
    }
}
TCPServer::~TCPServer() {
    close(sock);
}
int TCPServer::Socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}
bool TCPServer::Bind(uint16_t port) {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    return bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0;
}
bool TCPServer::Listen(int QueueMaxLen) {
    return listen(sock, QueueMaxLen) == 0;
}
int TCPServer::Accept(string* ip, uint16_t* port) {//accept:将底层建立好的连接获取上来
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t len = sizeof(clientAddr);
    int fd = accept(sock, (struct sockaddr*)&clientAddr, &len);
    if (fd != -1) {
        *ip = inet_ntoa(clientAddr.sin_addr);//将网络字节序整数ip转字符串ip
        *port = ntohs(clientAddr.sin_port);
    }
    return fd;
}
