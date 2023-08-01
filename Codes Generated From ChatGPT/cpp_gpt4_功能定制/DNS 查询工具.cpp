#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>

#include <asio.hpp>

struct Server {
    std::string ip;
    unsigned short port;
};

class Packet {
public:
    Packet(const std::string& hostname) {
        // Generate DNS packet
    }

    const std::vector<unsigned char>& get_data() const {
        return data;
    }

private:
    std::vector<unsigned char> data;
};

std::atomic<bool> quit(false);

void signal_handler(int) {
    quit.store(true);
}

void print_usage() {
    std::cout << "Usage: dns_query_tool -s <server_ip> -p <server_port> -d <data_file> [-l <local_ip>] [-n <num_requests>] [-h]\n";
}

int main(int argc, char** argv) {
    std::signal(SIGINT, signal_handler);

    std::string server_ip, data_file, local_ip;
    unsigned short server_port = 53;
    int num_requests = 1;

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-s" && i + 1 < argc) {
            server_ip = argv[++i];
        } else if (std::string(argv[i]) == "-p" && i + 1 < argc) {
            server_port = static_cast<unsigned short>(std::stoi(argv[++i]));
        } else if (std::string(argv[i]) == "-d" && i + 1 < argc) {
            data_file = argv[++i];
        } else if (std::string(argv[i]) == "-l" && i + 1 < argc) {
            local_ip = argv[++i];
        } else if (std::string(argv[i]) == "-n" && i + 1 < argc) {
            num_requests = std::stoi(argv[++i]);
        } else if (std::string(argv[i]) == "-h") {
            print_usage();
            return 0;
        } else {
            print_usage();
            return 1;
        }
    }

    if (server_ip.empty() || data_file.empty()) {
        print_usage();
        return 1;
    }

    Server server {server_ip, server_port};

    std::ifstream infile(data_file);
    std::string line;
    std::vector<std::string> hostnames;
    while (std::getline(infile, line)) {
        hostnames.push_back(line);
    }

    asio::io_context io_context;
    asio::ip::udp::socket socket(io_context);
    socket.open(asio::ip::udp::v4());
    if (!local_ip.empty()) {
        asio::ip::udp::endpoint local_endpoint(asio::ip::address::from_string(local_ip), 0);
        socket.bind(local_endpoint);
    }

    asio::ip::udp::endpoint server_endpoint(asio::ip::address::from_string(server.ip), server.port);
    std::size_t requests_sent = 0;

    auto start = std::chrono::steady_clock::now();
    while (!quit.load()) {
        for (const auto& hostname : hostnames) {
            Packet packet(hostname);
            socket.send_to(asio::buffer(packet.get_data()), server_endpoint);
            requests_sent++;
            if (requests_sent >= num_requests) {
                break;
            }
        }
        if (requests_sent >= num_requests) {
            break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::
        chrono::milliseconds>(end - start).count();
    std::cout << "Total requests sent: " << requests_sent << std::endl;
    std::cout << "Elapsed time: " << elapsed << " ms" << std::endl;
    std::cout << "Requests per second: " << (requests_sent * 1000.0 / elapsed) << std::endl;

    socket.close();
    io_context.stop();

    return 0;
}
