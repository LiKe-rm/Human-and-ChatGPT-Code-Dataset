#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <libssh/libssh.h>
#include <unistd.h>

class SshTunnel {
public:
    SshTunnel(const std::string &gateway, const std::string &remote_host,
              int remote_port, int local_port)
            : gateway_(gateway), remote_host_(remote_host),
              remote_port_(remote_port), local_port_(local_port) {
        ssh_init();
        connect_ssh();
        create_tunnel();
    }

    ~SshTunnel() {
        ssh_channel_free(channel_);
        ssh_disconnect(session_);
        ssh_free(session_);
        ssh_finalize();
    }

private:
    void connect_ssh() {
        session_ = ssh_new();
        if (session_ == nullptr) {
            throw std::runtime_error("Failed to create SSH session");
        }

        ssh_options_set(session_, SSH_OPTIONS_HOST, gateway_.c_str());

        int rc = ssh_connect(session_);
        if (rc != SSH_OK) {
            throw std::runtime_error("Failed to connect to SSH gateway");
        }

        rc = ssh_userauth_publickey_auto(session_, nullptr, nullptr);
        if (rc != SSH_AUTH_SUCCESS) {
            throw std::runtime_error("Failed to authenticate with SSH gateway");
        }
    }

    void create_tunnel() {
        channel_ = ssh_channel_new(session_);
        if (channel_ == nullptr) {
            throw std::runtime_error("Failed to create SSH channel");
        }

        int rc = ssh_channel_open_forward(channel_, remote_host_.c_str(),
                                          remote_port_, nullptr, local_port_);
        if (rc != SSH_OK) {
            throw std::runtime_error("Failed to open SSH tunnel");
        }
    }

    std::string gateway_;
    std::string remote_host_;
    int remote_port_;
    int local_port_;
    ssh_session session_;
    ssh_channel channel_;
};

int main() {
    std::string gateway = "gateway.example.com";
    std::string remote_host = "remote_host.example.com";
    int remote_port = 5900;
    int local_port = 5901;

    try {
        SshTunnel tunnel(gateway, remote_host, remote_port, local_port);
        std::cout << "SSH tunnel created successfully" << std::endl;

        // 使用VNC连接到本地端口
        std::string vnc_command = "vncviewer localhost:" + std::to_string(local_port);
        int result = system(vnc_command.c_str());
        if (result != 0) {
            throw std::runtime_error("Failed to run VNC Viewer");
        }
    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
