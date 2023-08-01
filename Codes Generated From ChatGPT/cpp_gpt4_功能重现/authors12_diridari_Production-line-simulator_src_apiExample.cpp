#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <zmq.hpp>

class ManufacturingClient {
public:
    ManufacturingClient(const std::string &serverAddress)
        : context(1), socket(context, ZMQ_REQ) {
        socket.connect(serverAddress);
    }

    void runOneTime();

private:
    void handleConveyorBelt();
    void handlePusher();
    void handleMiller();

    std::string sendMessage(const std::string &message);
    
    zmq::context_t context;
    zmq::socket_t socket;
};

std::string ManufacturingClient::sendMessage(const std::string &message) {
    zmq::message_t request(message.size());
    memcpy(request.data(), message.c_str(), message.size());

    socket.send(request);

    zmq::message_t reply;
    socket.recv(&reply);

    return std::string(static_cast<char *>(reply.data()), reply.size());
}

void ManufacturingClient::handleConveyorBelt() {
    std::string response = sendMessage("set conveyorBelt start");
    if (response == "ok") {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sendMessage("set conveyorBelt stop");
    }
}

void ManufacturingClient::handlePusher() {
    std::string response = sendMessage("set pusher extend");
    if (response == "ok") {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        sendMessage("set pusher retract");
    }
}

void ManufacturingClient::handleMiller() {
    std::string response = sendMessage("set miller on");
    if (response == "ok") {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        sendMessage("set miller off");
    }
}

void ManufacturingClient::runOneTime() {
    handleConveyorBelt();
    handlePusher();
    handleMiller();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <server_address>" << std::endl;
        return 1;
    }

    ManufacturingClient client(argv[1]);

    while (true) {
        client.runOneTime();
    }

    return 0;
}
