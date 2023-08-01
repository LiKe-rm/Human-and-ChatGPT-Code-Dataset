#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

// Shadowsocks服务器地址和端口
const char* server_addr = "xxx.xxx.xxx.xxx";
const int server_port = 8388;

// 本地代理监听地址和端口
const char* local_addr = "127.0.0.1";
const int local_port = 1080;

// Shadowsocks密码和加密方式
const char* password = "your_password";
const char* method = "aes-256-cfb";

// 函数声明
int create_socket(const char* addr, int port);
int connect_to_server();
void handle_request(int client_sock, int server_sock);
void handle_data(int sock);

int main() {
    // 创建本地监听socket
    int local_sock = create_socket(local_addr, local_port);
    if (local_sock == -1) {
        cerr << "Failed to create local socket." << endl;
        return 1;
    }

    // 连接到Shadowsocks服务器
    int server_sock = connect_to_server();
    if (server_sock == -1) {
        cerr << "Failed to connect to server." << endl;
        close(local_sock);
        return 1;
    }

    // 处理请求
    while (true) {
        handle_request(local_sock, server_sock);
    }

    // 关闭socket
    close(local_sock);
    close(server_sock);

    return 0;
}

// 创建socket
int create_socket(const char* addr, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cerr << "Failed to create socket." << endl;
        return -1;
    }

    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = inet_addr(addr);

    if (bind(sock, (sockaddr*)&addr_in, sizeof(addr_in)) == -1) {
        cerr << "Failed to bind socket." << endl;
        close(sock);
        return -1;
    }

    if (listen(sock, 5) == -1) {
        cerr << "Failed to listen on socket." << endl;
        close(sock);
        return -1;
    }

    return sock;
}

// 连接到Shadowsocks服务器
int connect_to_server() {
    // 创建socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        cerr << "Failed to create socket." << endl;
        return -1;
    }

    // 获取服务器地址信息
    hostent* server = gethostbyname(server_addr);
    if (server == NULL) {
        cerr << "Failed to get server address." << endl;
        close(sock);
        return -1;
    }

    // 设置服务器地址和端口
    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(server_port);
    memcpy(&addr_in.sin_addr.s_addr, server->h_addr, server->h_length);

    // 连接服务器
    if (connect(sock, (sockaddr*)&addr_in, sizeof(addr_in)) == -1) {
        cerr << "Failed to connect to server." << endl;
        close(sock);
        return -1;
    }

    // 发送密码和加密方式
    string message = string(password) + ":" + string(method);
    if (send(sock, message.c_str(), message.length(), 0) == -1) {
        cerr << "Failed to send message to server." << endl;
        close(sock);
        return -1;
    }

    return sock;
}

// 处理请求
void handle_request(int client_sock, int server_sock) {
    // 接受客户端连接
    sockaddr_in client_addr_in;
    socklen_t client_addr_len = sizeof(client_addr_in);
    int client_sock_fd = accept(client_sock, (sockaddr*)&client_addr_in, &client_addr_len);
    if (client_sock_fd == -1) {
        cerr << "Failed to accept client connection." << endl;
        return;
    }

    // 读取客户端请求
    char buf[1024];
    int len = recv(client_sock_fd, buf, sizeof(buf), 0);
    if (len == -1) {
        cerr << "Failed to read client request." << endl;
        close(client_sock_fd);
        return;
    }

    // 转发请求到Shadowsocks服务器
    if (send(server_sock, buf, len, 0) == -1) {
        cerr << "Failed to send request to server." << endl;
        close(client_sock_fd);
        return;
    }

    // 处理服务器响应
    handle_data(server_sock);

    // 关闭客户端socket
    close(client_sock_fd);
}

// 处理数据
void handle_data(int sock) {
    char buf[1024];
    int len = recv(sock, buf, sizeof(buf), 0);
    if (len == -1) {
        cerr << "Failed to read data from server." << endl;
        return;
    }

    // 转发数据到客户端
    send(client_sock, buf, len, 0);
}