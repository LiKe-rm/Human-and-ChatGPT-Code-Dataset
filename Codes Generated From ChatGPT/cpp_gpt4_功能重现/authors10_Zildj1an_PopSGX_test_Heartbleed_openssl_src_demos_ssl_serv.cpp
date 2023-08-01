#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

using namespace std;

// SSL上下文结构体
struct SSL_CTX_Delete
{
    void operator()(SSL_CTX* ptr) const
    {
        SSL_CTX_free(ptr);
    }
};

// SSL结构体
struct SSL_Delete
{
    void operator()(SSL* ptr) const
    {
        SSL_free(ptr);
    }
};

int main()
{
    SSL_library_init(); // 加载SSL算法
    OpenSSL_add_all_algorithms(); // 加载所有SSL算法
    SSL_load_error_strings(); // 加载SSL错误信息

    // 创建SSL上下文
    unique_ptr<SSL_CTX, SSL_CTX_Delete> ssl_ctx(SSL_CTX_new(TLS_server_method()));
    if (!ssl_ctx)
    {
        cout << "Failed to create SSL context." << endl;
        return -1;
    }

    // 加载证书和私钥文件
    if (SSL_CTX_use_certificate_file(ssl_ctx.get(), "cert.pem", SSL_FILETYPE_PEM) <= 0)
    {
        cout << "Failed to load certificate file." << endl;
        return -1;
    }
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx.get(), "key.pem", SSL_FILETYPE_PEM) <= 0)
    {
        cout << "Failed to load private key file." << endl;
        return -1;
    }

    // 创建TCP套接字并绑定端口
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        cout << "Failed to create socket." << endl;
        return -1;
    }
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8000);
    if (bind(listen_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        cout << "Failed to bind socket." << endl;
        return -1;
    }

    // 开始监听连接请求
    if (listen(listen_fd, 10) == -1)
    {
        cout << "Failed to listen on socket." << endl;
        return -1;
    }
    cout << "Listening on port 8000..." << endl;

    // 等待连接请求并创建SSL连接
    while (true)
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd == -1)
        {
            cout << "Failed to accept client connection." << endl;
            continue;
        }

        // 创建SSL结构体
        unique_ptr<SSL, SSL_Delete> ssl(SSL_new(ssl_ctx.get()));
        if (!ssl)
        {
            cout << "Failed to create SSL connection." << endl;
            close(client_fd);
            continue;
        }

        // 将TCP套接字与SSL连接绑定
        if (SSL_set_fd(ssl.get(), client_fd) == 0)
        {
            cout << "Failed to set socket for SSL connection." << endl;
            close(client_fd);
            continue;
        }

        // 在SSL连接上完成握手
        if (SSL_accept(ssl.get()) <= 0)
        {
            cout << "Failed to complete SSL handshake." << endl;
            close(client_fd);
            continue;
        }

        // 检查客户端的证书以确保连接安全
        X509* client_cert = SSL_get_peer_certificate(ssl.get());
        if (!client_cert)
        {
            cout << "No client certificate provided." << endl;
            close(client_fd);
            continue;
        }
        if (SSL_get_verify_result(ssl.get()) != X509_V_OK)
        {
            cout << "Failed to verify client certificate." << endl;
            close(client_fd);
            X509_free(client_cert);
            continue;
        }
        X509_free(client_cert);

        // 与客户端进行数据交换
        const char* message = "Hello, client!";
        if (SSL_write(ssl.get(), message, strlen(message)) <= 0)
        {
            cout << "Failed to send data to client." << endl;
            close(client_fd);
            continue;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = SSL_read(ssl.get(), buffer, sizeof(buffer));
        if (bytes_received <= 0)
        {
            cout << "Failed to receive data from client." << endl;
            close(client_fd);
            continue;
        }

        cout << "Received data from client: " << buffer << endl;

        // 关闭SSL连接和TCP套接字
        SSL_shutdown(ssl.get());
        close(client_fd);
    }

    close(listen_fd);

    return 0;
}