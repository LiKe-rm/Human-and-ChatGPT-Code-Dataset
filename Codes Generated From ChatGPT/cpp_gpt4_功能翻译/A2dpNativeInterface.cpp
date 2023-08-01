#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <mutex>
#include <asio.hpp>
#include <asio/bluetooth/bluetooth.hpp>

class A2dpNativeInterface {
public:
    static A2dpNativeInterface& getInstance() {
        std::lock_guard<std::mutex> lock(instance_mutex);
        if (!instance) {
            instance = new A2dpNativeInterface();
        }
        return *instance;
    }

    bool connectA2dp(const std::string& device_address);
    bool disconnectA2dp(const std::string& device_address);

    // Other public methods ...

private:
    A2dpNativeInterface() = default;

    asio::io_context io_context;
    asio::bluetooth::rfcomm::socket socket{io_context};
    static A2dpNativeInterface* instance;
    static std::mutex instance_mutex;
};

A2dpNativeInterface* A2dpNativeInterface::instance = nullptr;
std::mutex A2dpNativeInterface::instance_mutex;

bool A2dpNativeInterface::connectA2dp(const std::string& device_address) {
    asio::error_code ec;
    asio::bluetooth::rfcomm::endpoint endpoint(asio::bluetooth::address(device_address), 1);
    socket.connect(endpoint, ec);

    if (ec) {
        std::cerr << "Error connecting to device: " << ec.message() << std::endl;
        return false;
    }

    return true;
}

bool A2dpNativeInterface::disconnectA2dp(const std::string& device_address) {
    asio::error_code ec;
    socket.shutdown(asio::socket_base::shutdown_both, ec);
    socket.close(ec);

    if (ec) {
        std::cerr << "Error disconnecting from device: " << ec.message() << std::endl;
        return false;
    }

    return true;
}

// Other private methods ...

std::string format_address(const unsigned char (&addr)[6]) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(2) << static_cast<int>(addr[0]) << ':'
        << std::setw(2) << static_cast<int>(addr[1]) << ':'
        << std::setw(2) << static_cast<int>(addr[2]) << ':'
        << std::setw(2) << static_cast<int>(addr[3]) << ':'
        << std::setw(2) << static_cast<int>(addr[4]) << ':'
        << std::setw(2) << static_cast<int>(addr[5]);
    return oss.str();
}

int main() {
    A2dpNativeInterface& a2dp_native_interface = A2dpNativeInterface::getInstance();
    
    unsigned char device_address[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    std::string address = format_address(device_address);

    if (a2dp_native_interface.connectA2dp(address)) {
        std::cout << "Connected to device: " << address << std::endl;

        // Use the connection ...
        
        if (a2dp_native_interface.disconnectA2dp(address)) {
            std::cout << "Disconnected from device: "<< address << std::endl;
        } else {
            std::cerr << "Failed to disconnect from device: " << address << std::endl;
        }
    } else {
        std::cerr << "Failed to connect to device: " << address << std::endl;
    }

    return 0;
}

