#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class Test {
public:
    Test(std::string id, std::string name) : id(id), name(name) {}
    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual void destroy() = 0;
    virtual std::string getContextTag() = 0;
protected:
    std::string id;
    std::string name;
};

class CompassTest : public Test {
public:
    CompassTest(std::string id, std::string name) : Test(id, name) {}

    void setUp() override {
        std::cout << "CompassTest setup\n";
        // Simulation of sensor setup
        srand(time(0));
        mCompass = rand() % 360;
        // Simulation of timer setup
        testCountDownTimer = 10;
    }

    void initView() override {
        std::cout << "CompassTest initView\n";
        // Simulation of view setup
        mView = "SampleView";
    }

    void destroy() override {
        std::cout << "CompassTest destroy\n";
        // Simulation of sensor and timer destroy
        mCompass = 0;
        testCountDownTimer = 0;
        mView.clear();
    }

    std::string getContextTag() override {
        return "CompassTest";
    }

    void startTest() {
        std::cout << "Starting compass test\n";
        setUp();
        initView();
        std::thread timer_thread(&CompassTest::startTimer, this);
        std::thread sensor_thread(&CompassTest::simulateSensor, this);
        timer_thread.join();
        sensor_thread.join();
        destroy();
    }

private:
    int mCompass;
    int testCountDownTimer;
    std::string mView;

    void startTimer() {
        while (testCountDownTimer-- > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void simulateSensor() {
        while (testCountDownTimer > 0) {
            mCompass = rand() % 360;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
};

int main() {
    CompassTest test("id1", "CompassTest");
    test.startTest();
    return 0;
}
