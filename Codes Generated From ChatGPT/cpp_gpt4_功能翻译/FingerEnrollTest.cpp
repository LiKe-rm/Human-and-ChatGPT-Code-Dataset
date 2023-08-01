#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>
#include <atomic>

class Test {
public:
    virtual void onFinish() = 0;
    virtual void onTick() = 0;
    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual void finish() = 0;
    virtual std::string getContextTag() = 0;
    virtual void destroy() = 0;
};

class TestCountDownTimer {
    std::atomic<bool> runTimer;
    int duration;
    int tickRate;
    Test* callback;
public:
    TestCountDownTimer(int duration, int tickRate, Test* callback)
        : duration(duration), tickRate(tickRate), callback(callback), runTimer(false) {}

    void start() {
        runTimer = true;
        std::thread([this]() {
            for (int i = 0; i < duration && runTimer; i += tickRate) {
                std::this_thread::sleep_for(std::chrono::seconds(tickRate));
                if (runTimer) callback->onTick();
            }
            if (runTimer) callback->onFinish();
        }).detach();
    }

    void cancel() {
        runTimer = false;
    }
};

class FingerEnrollTest : public Test {
    static const std::string TAG;
    static const std::string FP_PATH;
    static const std::string GOODIX;
    static const std::string SYNA;
    static const std::string FOCAL;

    TestCountDownTimer* testCountDownTimer = nullptr;
public:
    FingerEnrollTest() {
        testCountDownTimer = new TestCountDownTimer(10, 1, this);
    }

    ~FingerEnrollTest() {
        delete testCountDownTimer;
    }

    void onFinish() override {
        std::cout << "Test finished.\n";
    }

    void onTick() override {
        std::cout << "Tick.\n";
    }

    void setUp() override {
        testCountDownTimer->start();
    }

    void initView() override {
        std::cout << "Init view.\n";
    }

    void finish() override {
        std::cout << "Finish.\n";
    }

    std::string getContextTag() override {
        return TAG;
    }

    void destroy() override {
        if (testCountDownTimer) {
            testCountDownTimer->cancel();
        }
    }

    std::string readFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return "";
        }
        std::string line;
        std::getline(file, line);
        return line;
    }

    void onActivityResult(int requestCode, int resultCode) {
        if (resultCode == 1) { // pass
            std::cout << "Pass.\n";
        } else if (resultCode == 0) { // fail
            std::cout << "Fail.\n";
        }
    }
};

const std::string FingerEnrollTest::TAG = "FingerprintTest";
const std::string FingerEnrollTest::FP_PATH = "/sys/class/deviceinfo/device_info/fp";
const std::string FingerEnrollTest::GOODIX = "goodix";
const std::string FingerEnrollTest::SYNA = "syna";
const std::string FingerEnrollTest::FOCAL = "FocalTech";

int main() {
    FingerEnrollTest test;
    test.setUp();
    test.initView();

    // Simulate the test
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::string fp = test.readFile(FingerEnrollTest::FP_PATH);
    if (fp.empty()) {
        std::cout << "Failed.\n";
        return 1;
    }
    if (fp.find(FingerEnrollTest::GOODIX) != std::string::npos) {
        std::cout << "Starting Goodix activity.\n";
    } else if (fp.find(FingerEnrollTest::SYNA) != std::string::npos) {
        std::cout << "Starting Syna activity.\n";
    } else if (fp.find(FingerEnrollTest::FOCAL) != std::string::npos) {
        std::cout << "Starting Focal activity.\n";
    } else {
        std::cout << "The wrong fingerprint ic information.\n";
        std::cout << "Failed.\n";
    }

    // Simulate result
    test.onActivityResult(0, 1); // pass

    test.finish();
    test.destroy();

    return 0;
}

