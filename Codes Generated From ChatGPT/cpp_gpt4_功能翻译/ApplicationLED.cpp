#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <cstdint>
#include <bitset>
#include <string>
#include <cassert>
#include <algorithm>

class Observable;
class Observer;

class Observer {
public:
    virtual void update(Observable* observable, void* data) = 0;
};

class Observable {
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void deleteObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(void* data) {
        for (Observer* observer : observers) {
            observer->update(this, data);
        }
    }

private:
    std::vector<Observer*> observers;
};

enum class LedColor {
    GREEN,
    YELLOW,
    RED,
};

class Led {
public:
    Led(LedColor color) : color(color), is_on(false) {}

    void turnOn() {
        is_on = true;
    }

    void turnOff() {
        is_on = false;
    }

    bool isOn() const {
        return is_on;
    }

    LedColor getColor() const {
        return color;
    }

private:
    LedColor color;
    bool is_on;
};

class Mote {
public:
    Mote() {
        for (int i = 0; i < 3; ++i) {
            leds.push_back(std::make_shared<Led>(static_cast<LedColor>(i)));
        }
    }

    std::shared_ptr<Led> getLed(LedColor color) {
        for (const auto& led : leds) {
            if (led->getColor() == color) {
                return led;
            }
        }
        return nullptr;
    }

private:
    std::vector<std::shared_ptr<Led>> leds;
};

class LedController : public Observable {
public:
    explicit LedController(Mote* mote) : mote(mote) {}

    void setLed(LedColor color, bool is_on) {
        std::shared_ptr<Led> led = mote->getLed(color);
        if (led) {
            if (is_on) {
                led->turnOn();
            } else {
                led->turnOff();
            }
            notifyObservers(static_cast<void*>(&color));
        }
    }

private:
    Mote* mote;
};

class LedView : public Observer {
public:
    LedView(Mote* mote, LedController* led_controller) : mote(mote), led_controller(led_controller) {
        led_controller->addObserver(this);
    }

    ~LedView() {
        led_controller->deleteObserver(this);
    }

    void update(Observable* observable, void* data) override {
        if (observable == led_controller) {
            LedColor color = *static_cast<LedColor*>(data);
            std::shared_ptr<Led> led = mote->getLed(color);
            if (led) {
                std::string color_str;
                switch (color) {
                case LedColor::GREEN:
                    color_str = "GREEN";
                    break;
                case LedColor::YELLOW:
                    color_str = "YELLOW";
                    break;
                case LedColor::RED:
                    color_str = "RED";
                    break;
                }

                std::cout << "LED " << color_str << ": " << (led->isOn() ? "ON" : "OFF") << std::endl;
            }
        }
    }

private:
    Mote* mote;
    LedController*led_controller;
};

int main() {
    Mote mote;
    LedController led_controller(&mote);
    LedView led_view(&mote, &led_controller);

    led_controller.setLed(LedColor::GREEN, true);
    led_controller.setLed(LedColor::YELLOW, true);
    led_controller.setLed(LedColor::RED, true);

    led_controller.setLed(LedColor::GREEN, false);
    led_controller.setLed(LedColor::YELLOW, false);
    led_controller.setLed(LedColor::RED, false);

    return 0;
}

