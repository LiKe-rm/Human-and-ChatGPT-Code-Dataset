#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <ratio>
#include <iomanip>
#include <string>
#include <sstream>

#define BATTERY_TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define BATTERY_VOLT_PATH "/sys/class/power_supply/BAT0/voltage_now"
#define BATTERY_CONT_PATH "/sys/class/power_supply/BAT0/capacity"

class BatteryTempTest {
    public:
        std::string name;
        std::string TAG = "BatteryTempTest";

        BatteryTempTest(std::string id, std::string name) {
            this->name = name;
        }

        void onTick() {
            // TODO
        }

        void onFinish() {
            std::cout << "Test has finished." << std::endl;
        }

        void setUp() {
            std::cout << TAG << "_start_test" << std::endl;
            for (int i = 0; i < 5; i++) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                onTick();
            }
        }

        void destroy() {
            // TODO
        }

        std::string tenthsToFixedString(int x) {
            int tens = x / 10;
            std::ostringstream oss;
            oss << tens << "." << (x - 10 * tens);
            return oss.str();
        }

        std::string milliToFixedString(int x) {
            int tens = x / 1000;
            std::ostringstream oss;
            oss << tens << "." << (x - 1000 * tens);
            return oss.str();
        }

        std::string readBatteryTemp() {
            std::ifstream tempFile(BATTERY_TEMP_PATH);
            std::string line;
            if (tempFile.is_open() && std::getline(tempFile, line)) {
                return line;
            } else {
                return "Unable to read battery temperature.";
            }
        }

        std::string readBatteryVoltage() {
            std::ifstream voltFile(BATTERY_VOLT_PATH);
            std::string line;
            if (voltFile.is_open() && std::getline(voltFile, line)) {
                return line;
            } else {
                return "Unable to read battery voltage.";
            }
        }

        std::string readBatteryContent() {
            std::ifstream contFile(BATTERY_CONT_PATH);
            std::string line;
            if (contFile.is_open() && std::getline(contFile, line)) {
                return line;
            } else {
                return "Unable to read battery content.";
            }
        }

        void executeTest() {
            setUp();
            std::string battTempValue = tenthsToFixedString(std::stoi(readBatteryTemp()));
            std::string battVoltageValue = milliToFixedString(std::stoi(readBatteryVoltage()));
            std::string battContValue = readBatteryContent();

            std::cout << "Battery temperature: " << battTempValue << " C" << std::endl;
            std::cout << "Battery voltage: " << battVoltageValue << " V" << std::endl;
            std::cout << "Battery content: " << battContValue << " %" << std::endl;
            onFinish();
            destroy();
        }
};

int main() {
    BatteryTempTest test("test_id", "Test Name");
    test.executeTest();
    return 0;
}
