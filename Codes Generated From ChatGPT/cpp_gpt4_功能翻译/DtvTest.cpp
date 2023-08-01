#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include <chrono>

class Test {
public:
    typedef std::function<void()> FinishCallback;

private:
    std::map<std::string, FinishCallback> callbacks;

public:
    void addCallback(const std::string& tag, FinishCallback callback) {
        callbacks[tag] = callback;
    }

    void removeCallback(const std::string& tag) {
        callbacks.erase(tag);
    }

    void finishTest(const std::string& tag) {
        if (callbacks.count(tag) > 0) {
            callbacks[tag]();
        }
    }

    void startTest(const std::string& tag, int durationInSeconds) {
        std::cout << "Starting test " << tag << " for " << durationInSeconds << " seconds." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(durationInSeconds));
        finishTest(tag);
    }
};

int main() {
    Test test;

    test.addCallback("DTVTest", []() {
        std::cout << "DTVTest finished." << std::endl;
    });

    test.startTest("DTVTest", 10);

    // Do other stuff...

    return 0;
}
