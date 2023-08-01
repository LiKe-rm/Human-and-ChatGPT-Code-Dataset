#include <iostream>
#include <string>
#include <map>
#include <zmq.hpp>

class ProductionLineAPI {
public:
    ProductionLineAPI(int port, const std::string &initialProductionSite)
        : context(1), socket(context, ZMQ_REP), productionSite(initialProductionSite) {
        socket.bind("tcp://*:" + std::to_string(port));
    }

    void processRequests();

private:
    std::string handleRequest(const std::string &request);
    std::string handleSensorRequest(const std::string &site, const std::string &sensor);
    std::string handleActuatorRequest(const std::string &site, const std::string &actuator, const std::string &action);

    void log(const std::string &message);
    void debug(const std::string &message);

    zmq::context_t context;
    zmq::socket_t socket;
    std::string productionSite;
};

void ProductionLineAPI::log(const std::string &message) {
    std::cout << "[LOG] " << message << std::endl;
}

void ProductionLineAPI::debug(const std::string &message) {
    std::cout << "[DEBUG] " << message << std::endl;
}

std::string ProductionLineAPI::handleRequest(const std::string &request) {
    // Example request format: "sensor siteName sensorName"
    // Example request format: "actuator siteName actuatorName action"
    std::istringstream iss(request);
    std::string type, site, item, action;
    iss >> type >> site >> item;

    if (type == "sensor") {
        return handleSensorRequest(site, item);
    } else if (type == "actuator") {
        iss >> action;
        return handleActuatorRequest(site, item, action);
    } else {
        return "Invalid request type";
    }
}

std::string ProductionLineAPI::handleSensorRequest(const std::string &site, const std::string &sensor) {
    log("Handling sensor request for site: " + site + " and sensor: " + sensor);
    // Simulate sensor data retrieval.
    // Replace this code with actual sensor data retrieval from the production site.
    std::map<std::string, std::string> sensorData = {
        {"temperature", "25.0"},
        {"pressure", "101.3"},
        {"humidity", "50"}
    };

    if (sensorData.find(sensor) != sensorData.end()) {
        return sensorData[sensor];
    } else {
        return "Invalid sensor";
    }
}

std::string ProductionLineAPI::handleActuatorRequest(const std::string &site, const std::string &actuator, const std::string &action) {
    log("Handling actuator request for site: " + site + ", actuator: " + actuator + " and action: " + action);
    // Simulate actuator control.
    // Replace this code with actual actuator control at the production site.
    std::map<std::string, std::string> validActions = {
        {"start", "ok"},
        {"stop", "ok"},
        {"extend", "ok"},
        {"retract", "ok"},
        {"on", "ok"},
        {"off", "ok"}
    };

    if (validActions.find(action) != validActions.end()) {
        return validActions[action];
    } else {
        return "Invalid action";
    }
}

void ProductionLineAPI::processRequests() {
    while (true) {
        zmq::message_t request;
        socket.recv(&request);

        std::string requestString(static_cast<char *>(request.data()), request.size());
        debug("Received request: " + requestString);

        std::string responseString = handleRequest(requestString);

        zmq::message_t response(responseString.size());
        memcpy(response.data(), responseString.c_str(), responseString.size());

        socket.send(response);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <initial_production_site>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string initialProductionSite = argv[2];

    ProductionLineAPI api(port, initialProductionSite);

    api.processRequests();

    return 0;
}
