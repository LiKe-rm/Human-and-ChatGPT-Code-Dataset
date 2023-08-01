#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>

#define CHARGERLEDPATH "/sys/class/leds/red/brightness"
#define CHARGERLEDPATH2 "/sys/class/leds/green/brightness"

class ChargerLEDTest {
private:
    std::string chargerLedPath = CHARGERLEDPATH;
    std::string chargerLedValue;
    bool flag = false;
    std::mutex mtx;

public:
    ChargerLEDTest() {
        std::ifstream infile(chargerLedPath);
        if (!infile.good()) {
            chargerLedPath = CHARGERLEDPATH2;
        }
    }

    void testprogress() {
        while (!flag) {
            std::lock_guard<std::mutex> lock(mtx);
            std::ifstream file(chargerLedPath);
            if (file.is_open()) {
                std::getline(file, chargerLedValue);
                file.close();
                if (std::stoi(chargerLedValue) > 0) {
                    std::cout << "Charger LED is bright!" << std::endl;
                } else {
                    std::cout << "Charger LED is not bright!" << std::endl;
                    flag = true;
                }
            } else {
                std::cout << "Unable to open file" << std::endl;
                flag = true;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void runTest() {
        std::thread progressThread(&ChargerLEDTest::testprogress, this);
        progressThread.join();
    }
};

int main() {
    ChargerLEDTest test;
    test.runTest();

    return 0;
}
