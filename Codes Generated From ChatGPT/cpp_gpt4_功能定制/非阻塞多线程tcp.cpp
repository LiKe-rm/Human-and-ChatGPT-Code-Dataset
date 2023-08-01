include <sys/types.h>
include <sys/socket.h>
include<netinet/in.h>
include <arpa/inet.h>
include <unistd.h>
include <fcntl.h>

const char* SERVER_ADDRESS = "127.0.0.1";
const int SERVER_PORT = 8888;

// 创建服务器套接字
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
if (server_socket < 0) {
    perror("socket error");
    exit(EXIT_FAILURE);
}

// 设置服务器套接字非阻塞
fcntl(server_socket, F_SETFL, O_NONBLOCK);

// 绑定服务器地址和端口号
struct sockaddr_in server_address;
memset(&server_address, 0, sizeof(server_address));
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
server_address.sin_port = htons(SERVER_PORT);
if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    if (errno == EADDRINUSE) {
        // 端口已被占用
        // ...
    } else if (errno == EACCES) {
        // 没有权限绑定地址和端口
        // ...
    } else {
        // 其他错误
        // ...
    }
}

// 监听客户端连接请求
if (listen(server_socket, 5) < 0) {
    perror("listen error");
    exit(EXIT_FAILURE);
}

// 循环等待客户端连接
while (1) {
    // 接受客户端连接请求
    struct sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);
    if (client_socket < 0) {
        // 如果没有连接，则继续循环等待
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            continue;
        }
        // 错误处理
    }

    // 创建新线程处理客户端请求
    std::thread client_thread(handle_client, client_socket);
    client_thread.detach();
}

// 关闭服务器套接字
close(server_socket);
void handle_client(int client_socket) {
    // 设置客户端套接字非阻塞
    fcntl(client_socket, F_SETFL, O_NONBLOCK);

    // 接收客户端发送的数据
    char buffer[1024];
    while (1) {
        int n = recv(client_socket, buffer, sizeof(buffer), 0);
        if (n < 0) {
            // 如果没有数据，则继续循环等待
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            }else {
                // 接收数据出错，关闭客户端套接字
                perror("recv error");
                close(client_socket);
                return;
        	}
        } else if (n == 0) {
            // 客户端关闭了连接，退出循环
            break;
        } else {
            // 处理接收到的数据
            handle_data(buffer, n);
        }
    }

    // 关闭客户端套接字
    close(client_socket);
}