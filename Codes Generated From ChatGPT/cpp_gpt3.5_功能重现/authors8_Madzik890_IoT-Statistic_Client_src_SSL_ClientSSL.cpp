#include <iostream>
#include <cstring>
#include <stdexcept>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class ClientSSL {
private:
    SSL_CTX* ctx;
    SSL* ssl;
    int sockfd;

public:
    ClientSSL();
    ~ClientSSL();

    SSL_CTX* init_ssl_ctx();
    void send_message(const std::string& message, std::string* response = nullptr);
    void connect_to_server(const std::string& ip_address, int port);
    void send_xml(const std::string& xml);
    void send_log(const std::string& log);
    void cleanup_ssl();
};

ClientSSL::ClientSSL() {
    ctx = nullptr;
    ssl = nullptr;
    sockfd = -1;
}

ClientSSL::~ClientSSL() {
    cleanup_ssl();
}

SSL_CTX* ClientSSL::init_ssl_ctx() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD* method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        throw std::runtime_error("Unable to create SSL_CTX.");
    }
    return ctx;
}

void ClientSSL::connect_to_server(const std::string& ip_address, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Unable to create socket.");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_address.c_str(), &server_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid IP address.");
    }

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Unable to connect to the server.");
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);
    if (SSL_connect(ssl) != 1) {
        throw std::runtime_error("SSL connection failed.");
    }
}

void ClientSSL::send_message(const std::string& message, std::string* response) {
    if (!ssl) {
        throw std::runtime_error("SSL not initialized.");
    }

    if (SSL_write(ssl, message.c_str(), message.length()) < 0) {
        throw std::runtime_error("Unable to send message.");
    }

    if (response) {
        char buffer[4096];
        int bytes_received = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        if (bytes_received < 0) {
            throw std::runtime_error("Unable to read response.");
        }
        buffer[bytes_received] = '\0';
        *response = std::string(buffer);
    }
}

void ClientSSL::send_xml(const std::string& xml) {
    send_message(xml);
}

void ClientSSL::send_log(const std::string& log) {
    send_message(log);
}

void ClientSSL::cleanup_ssl() {
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        ssl = nullptr;
    }

    if (ctx) {
        SSL_CTX_free(ctx);
        ctx = nullptr;
    }

    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }

    ERR_free_strings();
}
