#include"Server.h"
int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "输入服务端的端口(ip使用INADDR_ANY)" << endl;
        exit(0);
    }
    UDPServer server(atoi(argv[1]));
    while (1) {
        string clientIP;
        uint16_t clientPort;
        string message = server.Recvform(&clientIP, &clientPort);
        printf("客户端[%s : %d]发送过来数据:%s\n", clientIP.c_str(), clientPort, message.c_str());
        bool ret = server.Sendto(message, clientIP, clientPort);
        if (ret == false) {
            cout << "发送数据给客户端失败" << endl;
        }
    }
    return 0;
}