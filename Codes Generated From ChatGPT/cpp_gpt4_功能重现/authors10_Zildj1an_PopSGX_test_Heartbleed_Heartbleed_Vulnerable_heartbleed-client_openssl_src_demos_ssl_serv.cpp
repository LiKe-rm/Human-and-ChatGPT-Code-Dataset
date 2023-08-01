#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CERT_FILE "server.crt" // 证书文件路径
#define KEY_FILE "server.key" // 密钥文件路径
#define CA_CERT_FILE "ca.crt" // CA证书文件路径

int main() {
    SSL_library_init(); // 初始化SSL库
    SSL_load_error_strings(); // 加载错误信息

    // 创建TCP监听套接字
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // 绑定IP地址和端口号
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8888);
    if (bind(listen_fd, (sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return -1;
    }

    // 开始监听套接字
    if (listen(listen_fd, 10) < 0) {
        std::cerr << "Error listening socket" << std::endl;
        return -1;
    }

    // 创建SSL上下文
    SSL_CTX* ssl_ctx = SSL_CTX_new(TLS_server_method());
    if (!ssl_ctx) {
        std::cerr << "Error creating SSL context" << std::endl;
        return -1;
    }

    // 加载证书和密钥
    if (SSL_CTX_use_certificate_file(ssl_ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Error loading certificate file" << std::endl;
        return -1;
    }

    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        std::cerr << "Error loading private key file" << std::endl;
        return -1;
    }

    // 加载CA证书
    if (SSL_CTX_load_verify_locations(ssl_ctx, CA_CERT_FILE, nullptr) <= 0) {
        std::cerr << "Error loading CA certificate file" << std::endl;
        return -1;
    }

    // 客户端证书身份验证
    SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, nullptr);

    while (true) {
        // 接受客户端连接
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(listen_fd, (sockaddr*) &client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Error accepting client" << std::endl;
            continue;
        }

        // 创建SSL套接字
        SSL* ssl = SSL_new(ssl_ctx);
        if (!ssl) {
            std::cerr << "Error creating SSL socket" << std::endl;
            close(client_fd);
            continue;
        }

        // 将SSL套接字绑定到TCP套接字上
        SSL_set_fd(ssl, client_fd);

        // SSL握手
        int ret = SSL_accept(ssl);
        if (ret <= 0) {
            std::cerr << "Error accepting SSL connection" << std::endl;
            SSL_free(ssl);
            close(client_fd);
            continue;
        }

        // 一旦连接被接受，关闭提示套接字连接
        close(listen_fd);

        // 发送和接收数据
        char buffer[1024];
        ret = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (ret <= 0) {
            std::cerr << "Error receiving data" << std::endl;
        } else {
            buffer[ret] = '\0';
            std::cout << "Received data: " << buffer << std::endl;

            ret = SSL_write(ssl, "Message received", 16);
            if (ret <= 0) {
                std::cerr << "Error sending data" << std::endl;
            }
        }

        // 关闭SSL套接字
        SSL_shutdown(ssl);
        SSL_free(ssl);

        // 关闭TCP套接字
        close(client_fd);
    }

    // 清理SSL上下文
    SSL_CTX_free(ssl_ctx);

    return 0;
}
