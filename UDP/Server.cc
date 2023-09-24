#include"Server.h"
UDPServer::UDPServer(uint16_t port) {
    sock = Socket();
    if (sock < 0) {
        cout << "创建套接字失败" << endl;
        exit(0);
    }
    if (!Bind(port)) {
        cout << "绑定端口失败" << endl;
        exit(0);
    }
}
UDPServer:: ~UDPServer() {
    close(sock);
}
string UDPServer::Recvform(string* ip, uint16_t* port) {//获取客户端的ip和端口
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t len = sizeof(clientAddr);
    char message[BUFSIZ] = { 0 };
    size_t size = recvfrom(sock, message, BUFSIZ - 1, 0/*表示阻塞*/, reinterpret_cast<struct sockaddr*>(&clientAddr), &len);
    if (size == -1) {
        cout << "读取错误" << endl;
    }
    else {
        message[size] = 0;
        *ip = inet_ntoa(clientAddr.sin_addr);//将数字ip转化为字符串ip
        // cout << "客户端的端口是:" << ntohs(clientAddr.sin_port) << endl;
        *port = ntohs(clientAddr.sin_port);
    }
    return message;
}
bool UDPServer::Sendto(string message, string ip, uint16_t port) {
    struct sockaddr_in clientAddr;
    // cout << "客户端ip与端口:" << ip << ' ' << port << endl;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(port);
    // clientAddr.sin_addr.s_addr = htonl(inet_addr(ip.c_str()));
    clientAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    int ret = sendto(sock, message.c_str(), message.length(), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
    if (ret < 0) {
        cout << "发送失败" << endl;
        return false;
    }
    return true;
}
int UDPServer::Socket() {
    return socket(AF_INET, SOCK_DGRAM, 0);
}
bool UDPServer::Bind(uint16_t port) {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    return bind(sock, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == 0;
}
