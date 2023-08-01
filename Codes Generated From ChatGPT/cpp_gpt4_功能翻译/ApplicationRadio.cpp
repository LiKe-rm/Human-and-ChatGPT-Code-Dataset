#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <chrono>
#include <thread>

class RadioPacket {
public:
    std::vector<uint8_t> data;
    RadioPacket(const std::vector<uint8_t>& data) : data(data) {}
};

class Radio {
public:
    virtual ~Radio() = default;
    virtual void transmitPacket(const RadioPacket& packet, std::chrono::milliseconds duration) = 0;
    virtual void setChannel(int channel) = 0;
    virtual void setOutputPower(double power) = 0;
};

class ApplicationRadio : public Radio {
public:
    ApplicationRadio() : _channel(-1), _outputPower(0) {}

    void transmitPacket(const RadioPacket& packet, std::chrono::milliseconds duration) override {
        std::cout << "Transmitting packet..." << std::endl;
        std::this_thread::sleep_for(duration);
        std::cout << "Transmission finished." << std::endl;
    }

    void setChannel(int channel) override {
        _channel = channel;
        std::cout << "Channel set to " << _channel << std::endl;
    }

    void setOutputPower(double power) override {
        _outputPower = power;
        std::cout << "Output power set to " << _outputPower << " dBm" << std::endl;
    }

private:
    int _channel;
    double _outputPower;
};

int main() {
    ApplicationRadio radio;

    radio.setChannel(10);
    radio.setOutputPower(-15);

    std::vector<uint8_t> data = {1, 2, 3, 4, 5};
    RadioPacket packet(data);

    radio.transmitPacket(packet, std::chrono::milliseconds(1000));

    return 0;
}
