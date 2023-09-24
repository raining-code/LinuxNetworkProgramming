#include"TCPClient.h"
int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "请输入服务端的ip和端口" << endl;
        exit(0);
    }
    string serverIP = argv[1];
    uint16_t serverPort = atoi(argv[2]);
    TCPClient client;
    int ret = client.Connect(serverIP, serverPort);
    if (ret == false) {
        cout << "与服务器建立连接失败" << endl;
        exit(0);
    }
    while (1) {
        string message;
        cout << "输入要给服务端发送的数据(Enter结束)" << endl;
        std::getline(std::cin, message);
        if (message.empty()) {
            break;
        }
        bool ret = client.Write(message);
        if (ret == false) {
            cout << "发送失败" << endl;
        }
        string s = client.Read();
        cout << "从服务端读取到:" << s << endl;
    }
    return 0;
}