#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <chrono>

class Test {
public:
    std::string id;
    std::string name;

    Test(std::string id, std::string name) : id(id), name(name) {}

    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual void destroy() = 0;
    virtual void onFinish() = 0;
    virtual void onTick() = 0;
};

class CarrierSignalTest : public Test {
public:
    int signalStrength;
    std::map<int, std::string> signalStrengthMap;

    CarrierSignalTest(std::string id, std::string name) : Test(id, name) {
        signalStrengthMap[1] = "SIGNAL STRENGTH NONE OR UNKNOWN";
        signalStrengthMap[2] = "SIGNAL STRENGTH POOR";
        signalStrengthMap[3] = "SIGNAL STRENGTH MODERATE";
        signalStrengthMap[4] = "SIGNAL STRENGTH GOOD";
        signalStrengthMap[5] = "SIGNAL STRENGTH GREAT";
    }

    void setUp() override {
        signalStrength = 1; // Initialize signal strength as NONE OR UNKNOWN
        std::cout << "CarrierSignalTest is setting up...\n";
    }

    void initView() override {
        std::cout << "CarrierSignalTest is initializing view...\n";
    }

    void destroy() override {
        std::cout << "CarrierSignalTest is being destroyed...\n";
    }

    void onFinish() override {
        std::cout << "CarrierSignalTest has finished...\n";
    }

    void onTick() override {
        // Simulate signal strength change
        signalStrength = (signalStrength % 5) + 1;

        std::cout << "Signal strength changed: " << signalStrengthMap[signalStrength] << "\n";

        if (signalStrength == 5) {
            onFinish();
        }
    }

    void start() {
        setUp();
        initView();
        std::cout << "CarrierSignalTest has started...\n";

        // Simulate tick every second
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            onTick();
        }

        destroy();
    }
};

int main() {
    CarrierSignalTest cst("test1", "Test 1");
    cst.start();

    return 0;
}
