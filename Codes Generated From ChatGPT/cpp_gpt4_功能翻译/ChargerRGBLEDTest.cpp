#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

enum class LED { RED, GREEN, BLUE };

class ChargerRGBLEDTest {
    string name;
    int duration;
    LED led;

public:
    ChargerRGBLEDTest(string name, int duration) : name(name), duration(duration), led(LED::RED) {}

    void setUp() {
        cout << name << " test started\n";
        testprogress();
    }

    void testprogress() {
        for (int i = 0; i < duration; i++) {
            switch (led) {
                case LED::RED:
                    cout << "Test red!\n";
                    led = LED::GREEN;
                    break;
                case LED::GREEN:
                    cout << "Test green!\n";
                    led = LED::BLUE;
                    break;
                case LED::BLUE:
                    cout << "Test blue!\n";
                    led = LED::RED;
                    break;
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    void destroy() {
        cout << name << " test finished\n";
    }
};

int main() {
    ChargerRGBLEDTest test("Charger RGB LED Test", 30);
    test.setUp();
    test.destroy();
    return 0;
}
