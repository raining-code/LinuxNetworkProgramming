#include"Client.h"
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "请输入服务端的ip和端口" << endl;
        exit(0);
    }
    string serverIP = argv[1];
    uint16_t serverPort = atoi(argv[2]);
    UDPClient client;
    while (1) {
        string message;
        cout << "输入要给服务端发送的数据(Enter结束)" << endl;
        std::getline(std::cin, message);
        if (message.empty()) {
            break;
        }
        bool ret = client.Sendto(message, serverIP, serverPort);
        if (ret == false) {
            cout << "发送失败" << endl;
        }
        string s = client.Recvform();
        cout << "从服务端读取到:" << s << endl;
    }
    return 0;
}