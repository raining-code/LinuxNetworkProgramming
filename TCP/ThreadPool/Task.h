#pragma once
#include<iostream>
using std::cout;
using std::endl;
class Task {
public:
    Task(int _fd, string _ip, uint16_t _port) :fd(_fd), ip(_ip), port(_port) {}
    void operator()()const {
        char message[BUFSIZ] = { 0 };
        while (1) {
            ssize_t size = read(fd, message, BUFSIZ - 1);
            if (size == -1) {
                cout << "读取出错" << endl;
                break;
            }
            else if (size == 0) {
                printf("客户端[%s:%d]已经断开\n", ip.c_str(), port);
                break;
            }
            else {
                message[size] = 0;
                printf("从客户端[%s:%d]读取到数据:%s\n", ip.c_str(), port, message);
                write(fd, message, size);//回声服务器
            }
        }
        printf("已经与客户端[%s:%d]断开连接\n", ip.c_str(), port);
        close(fd);
    }
private:
    int fd;
    string ip;
    uint16_t port;
};