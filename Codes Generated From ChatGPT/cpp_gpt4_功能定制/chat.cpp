#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <unordered_map>
#include <asio.hpp>
#include <nlohmann/json.hpp>

using asio::ip::tcp;
using json = nlohmann::json;

class Client : public std::enable_shared_from_this<Client> {
public:
    Client(tcp::socket socket, std::unordered_map<const Client*, std::shared_ptr<Client>>& clients)
        : socket_(std::move(socket)), clients_(clients) {
    }

    void start() {
        do_read();
    }

    void do_read() {
        auto self(shared_from_this());
        asio::async_read_until(socket_, read_buffer_, '\n',
            [this, self](const asio::error_code& ec, std::size_t length) {
                if (!ec) {
                    std::istream stream(&read_buffer_);
                    std::string line;
                    std::getline(stream, line);

                    json msg = json::parse(line);
                    handle_message(msg);

                    do_read();
                } else {
                    handle_disconnect();
                }
            });
    }

    void handle_message(const json& msg) {
        if (msg["type"] == "chat") {
            broadcast_message(msg);
        }
    }

    void broadcast_message(const json& msg) {
        std::string message_string = msg.dump() + "\n";

        for (auto& client_pair : clients_) {
            if (client_pair.first != this) {
                asio::error_code ignored_error;
                asio::write(client_pair.second->socket_, asio::buffer(message_string), ignored_error);
            }
        }
    }

    void handle_disconnect() {
        clients_.erase(this);
    }

private:
    tcp::socket socket_;
    asio::streambuf read_buffer_;
    std::unordered_map<const Client*, std::shared_ptr<Client>>& clients_;
};

class ChatServer {
public:
    ChatServer(asio::io_context& io_context, const tcp::endpoint& endpoint)
        : acceptor_(io_context, endpoint) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept([this](const asio::error_code& error, tcp::socket socket) {
            if (!error) {
                auto client = std::make_shared<Client>(std::move(socket), clients_);
                clients_[client.get()] = client;
                client->start();
            }
            do_accept();
        });
    }

    tcp::acceptor acceptor_;
    std::unordered_map<const Client*, std::shared_ptr<Client>> clients_;
};

int main(int argc, char* argv[]) {
    try {
        asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), 12345);
        ChatServer server(io_context, endpoint);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
