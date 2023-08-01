#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <thread>
#include <chrono>

class Event {
public:
    std::string action;
    Event(const std::string& act) : action(act) {}
};

class Handler {
public:
    virtual void handle(const Event& event) = 0;
};

class AutoCommand : public Handler {
private:
    std::string autoCmd = "com.tcl.autotest.cmd.auto";
    std::string tag = "AutoCommand";

public:
    void handle(const Event& event) override {
        if(event.action == autoCmd) {
            std::cout << tag << ": Auto command received." << std::endl;
            std::thread t(&AutoCommand::startAutoActivity, this);
            t.detach();
        }
    }

    void startAutoActivity() {
        // Simulate some processing
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << tag << ": Starting auto activity..." << std::endl;
    }
};

class EventBus {
private:
    std::map<std::string, Handler*> handlers;

public:
    void registerHandler(const std::string& action, Handler* handler) {
        handlers[action] = handler;
    }

    void triggerEvent(const Event& event) {
        if(handlers.count(event.action) > 0) {
            handlers[event.action]->handle(event);
        }
    }
};

int main() {
    EventBus bus;
    AutoCommand autoCmdHandler;

    bus.registerHandler("com.tcl.autotest.cmd.auto", &autoCmdHandler);

    Event event1("com.tcl.autotest.cmd.auto");
    Event event2("com.tcl.autotest.cmd.non_auto");

    bus.triggerEvent(event1);
    bus.triggerEvent(event2);

    // Sleep main thread for enough time to allow the auto activity to start
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
