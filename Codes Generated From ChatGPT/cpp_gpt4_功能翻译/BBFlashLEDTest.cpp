#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <string>
#include <condition_variable>

class LEDTest {
public:
    enum class LED {
        OFF, ON, FLASH
    };

    LEDTest() : ledState(LED::OFF), working(false), successFlag(true) {}

    void StartTest() {
        if (!working) {
            std::thread([this]() {
                working = true;
                successFlag = true;

                // simulate opening camera
                std::this_thread::sleep_for(std::chrono::seconds(1));

                if (!working) {
                    std::cout << "Failed to open camera\n";
                    successFlag = false;
                    return;
                }

                // simulate the flash LED test
                for (int i = 0; i < 3; ++i) {
                    SetLED(LED::ON);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    SetLED(LED::OFF);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }

                SetLED(LED::FLASH);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                SetLED(LED::OFF);

                std::cout << "Test finished\n";
                working = false;
            }).detach();
        }
    }

    void StopTest() {
        working = false;
    }

    void SetLED(LED state) {
        if (!working) return;
        switch (state) {
            case LED::OFF:
                std::cout << "LED off\n";
                break;
            case LED::ON:
                std::cout << "LED on\n";
                break;
            case LED::FLASH:
                std::cout << "LED flash\n";
                break;
        }
        ledState = state;
    }

    LED GetLED() const {
        return ledState;
    }

    bool IsWorking() const {
        return working;
    }

    bool IsSuccess() const {
        return successFlag;
    }

private:
    std::atomic<LED> ledState;
    std::atomic<bool> working;
    std::atomic<bool> successFlag;
};

int main() {
    LEDTest test;
    test.StartTest();

    // simulate waiting for the test to finish
    while (test.IsWorking()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Test success: " << (test.IsSuccess() ? "yes" : "no") << "\n";

    return 0;
}
