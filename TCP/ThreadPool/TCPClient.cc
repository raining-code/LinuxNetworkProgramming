#include"TCPClient.h"
TCPClient::TCPClient() {
    sock = Socket();
    if (sock == -1) {
        cout << "创建套接字失败" << endl;
    }
}
TCPClient::~TCPClient() {
    close(sock);
}
int TCPClient::Socket() {
    return socket(AF_INET, SOCK_STREAM, 0);
}
bool TCPClient::Connect(string ip, uint16_t port) {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    return connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == 0;
}
string TCPClient::Read() {
    char message[BUFSIZ] = { 0 };
    ssize_t size = read(sock, message, BUFSIZ - 1);
    if (size <= 0) {
        return "";
    }
    message[size] = 0;
    return message;
}
bool TCPClient::Write(string message) {
    return write(sock, message.c_str(), message.length()) != -1;
}
