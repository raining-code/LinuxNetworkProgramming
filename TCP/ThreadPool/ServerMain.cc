#include"TCPServer.h"
#include"ThreadPool.hpp"
#include<sys/wait.h>
#include<pthread.h>
#include"Task.h"
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "输入服务端绑定的端口(ip已经通过INADDR_ANY进行了设置)\n";
        exit(0);
    }
    ThreadPool<Task*> threadPool(5, 500);
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
        threadPool.push_task(new Task(fd, clientIP, clientPort));
    }
    return 0;
}