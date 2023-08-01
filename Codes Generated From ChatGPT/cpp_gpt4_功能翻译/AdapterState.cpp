#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef NDEBUG
constexpr bool DBG = false;
#else
constexpr bool DBG = true;
#endif

class AdapterService;

enum AdapterStateValue {
    STATE_OFF,
    STATE_BLE_TURNING_ON,
    STATE_BLE_ON,
    STATE_TURNING_ON,
    STATE_ON,
    STATE_TURNING_OFF,
    STATE_BLE_TURNING_OFF
};

class BaseAdapterState {
public:
    virtual ~BaseAdapterState() = default;
    virtual AdapterStateValue getStateValue() const = 0;
    virtual void enter(AdapterService* service) {}
    virtual void exit(AdapterService* service) {}
    virtual AdapterStateValue processMessage(AdapterService* service, int message) { return getStateValue(); }
};

class AdapterService {
public:
    AdapterService() : mCurrentState(std::make_shared<OffState>()) {}

    void postMessage(int message) {
        std::unique_lock<std::mutex> lock(mMutex);
        mCurrentState->exit(this);
        AdapterStateValue nextStateValue = mCurrentState->processMessage(this, message);
        mCurrentState = mStateMap[nextStateValue];
        mCurrentState->enter(this);
        mCondition.notify_all();
    }

    void wait(AdapterStateValue stateValue) {
        std::unique_lock<std::mutex> lock(mMutex);
        mCondition.wait(lock, [&] { return mCurrentState->getStateValue() == stateValue; });
    }

    void bringUpBle() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        postMessage(BLE_STARTED);
    }

    void bringDownBle() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        postMessage(BLE_STOPPED);
    }

    void startProfileServices() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        postMessage(BREDR_STARTED);
    }

    void stopProfileServices() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        postMessage(BREDR_STOPPED);
    }

private:
    std::shared_ptr<BaseAdapterState> mCurrentState;
    std::map<AdapterStateValue, std::shared_ptr<BaseAdapterState>> mStateMap;

    std::mutex mMutex;
    std::condition_variable mCondition;

    enum {
        BLE_TURN_ON = 1,
        USER_TURN_ON = 2,
        BREDR_STARTED = 3,
        BLE_STARTED = 4,
        USER_TURN_OFF = 5,
        BLE_TURN_OFF = 6,
        BLE_STOPPED = 7,
        BREDR_STOPPED = 8
    };

    class OffState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_OFF; }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == BLE_TURN_ON) {
                return STATE_BLE_TURNING_ON;
            }
            return getStateValue();
        }
    };

    class BleOnState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_BLE_ON; }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == USER_TURN_ON) {
                return STATE_TURNING_ON;
            } else if (message == BLE_TURN_OFF) {
                return STATE_BLE_TURNING_OFF;
            }
            return getStateValue();
        }
    };

    class OnState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override {
        return STATE_ON; }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == USER_TURN_OFF) {
                return STATE_TURNING_OFF;
            }
            return getStateValue();
        }
    };

    class TurningBleOnState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_BLE_TURNING_ON; }
        void enter(AdapterService* service) override {
            std::thread([service] { service->bringUpBle(); }).detach();
        }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == BLE_STARTED) {
                return STATE_BLE_ON;
            }
            return getStateValue();
        }
    };

    class TurningOnState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_TURNING_ON; }
        void enter(AdapterService* service) override {
            std::thread([service] { service->startProfileServices(); }).detach();
        }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == BREDR_STARTED) {
                return STATE_ON;
            }
            return getStateValue();
        }
    };

    class TurningOffState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_TURNING_OFF; }
        void enter(AdapterService* service) override {
            std::thread([service] { service->stopProfileServices(); }).detach();
        }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == BREDR_STOPPED) {
                return STATE_BLE_ON;
            }
            return getStateValue();
        }
    };

    class TurningBleOffState : public BaseAdapterState {
    public:
        AdapterStateValue getStateValue() const override { return STATE_BLE_TURNING_OFF; }
        void enter(AdapterService* service) override {
            std::thread([service] { service->bringDownBle(); }).detach();
        }
        AdapterStateValue processMessage(AdapterService* service, int message) override {
            if (message == BLE_STOPPED) {
                return STATE_OFF;
            }
            return getStateValue();
        }
    };
};

int main() {
    AdapterService service;
    service.postMessage(AdapterService::BLE_TURN_ON);
    service.wait(AdapterService::STATE_BLE_ON);
    service.postMessage(AdapterService::USER_TURN_ON);
    service.wait(AdapterService::STATE_ON);
    service.postMessage(AdapterService::USER_TURN_OFF);
    service.wait(AdapterService::STATE_BLE_ON);
    service.postMessage(AdapterService::BLE_TURN_OFF);
    service.wait(AdapterService::STATE_OFF);

    return 0;
}