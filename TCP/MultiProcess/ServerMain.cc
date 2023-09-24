#include"TCPServer.h"
#include<sys/wait.h>
void ContactClient(int fd, string clientIP, uint16_t clientPort) {
    char message[BUFSIZ] = { 0 };
    while (1) {
        ssize_t size = read(fd, message, BUFSIZ - 1);
        if (size == -1) {
            cout << "读取出错" << endl;
            break;
        }
        else if (size == 0) {
            printf("客户端[%s:%d]已经断开\n", clientIP.c_str(), clientPort);
            break;
        }
        else {
            message[size] = 0;
            printf("从客户端[%s:%d]读取到数据:%s\n", clientIP.c_str(), clientPort, message);
            write(fd, message, size);//回声服务器
        }
    }
    printf("已经与客户端[%s:%d]断开连接\n", clientIP.c_str(), clientPort);
    close(fd);
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "输入服务端绑定的端口(ip已经通过INADDR_ANY进行了设置)\n";
        exit(0);
    }
    TCPServer server(atoi(argv[1]), 20);//全连接队列最大长度=20
    while (1) {
        string clientIP;
        uint16_t clientPort;
        int fd = server.Accept(&clientIP, &clientPort);
        if (fd < 0) {
            cout << "accept失败" << endl;
            continue;
        }
        printf("成功获取连接,客户端[%s:%d]\n", clientIP.c_str(), clientPort);
        //accept成功
        if (fork() == 0) {
            if (fork() == 0) {
                ContactClient(fd, clientIP, clientPort);
                exit(0);
            }
            exit(0);
        }
        close(fd);
        wait(nullptr);
    }
    return 0;
}