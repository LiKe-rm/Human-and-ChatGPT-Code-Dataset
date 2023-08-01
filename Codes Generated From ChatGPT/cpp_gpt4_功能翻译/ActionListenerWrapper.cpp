#include <iostream>
#include <memory>
#include <functional>

class ActionListener {
public:
    virtual ~ActionListener() = default;

    virtual void onSuccess() = 0;
    virtual void onFailure(int reason) = 0;
};

class ActionListenerWrapper {
public:
    ActionListenerWrapper(std::shared_ptr<ActionListener> listener)
        : mListener(listener) {}

    void sendFailure(int reason) {
        if (mListener) {
            try {
                mListener->onFailure(reason);
            } catch (...) {
                // no-op (client may be dead, nothing to be done)
            }
        }
    }

    void sendSuccess() {
        if (mListener) {
            try {
                mListener->onSuccess();
            } catch (...) {
                // no-op (client may be dead, nothing to be done)
            }
        }
    }

private:
    std::shared_ptr<ActionListener> mListener;
};

class ExampleActionListener : public ActionListener {
public:
    void onSuccess() override {
        std::cout << "Success!" << std::endl;
    }

    void onFailure(int reason) override {
        std::cout << "Failure! Reason: " << reason << std::endl;
    }
};

int main() {
    std::shared_ptr<ActionListener> listener = std::make_shared<ExampleActionListener>();
    ActionListenerWrapper wrapper(listener);

    wrapper.sendSuccess();
    wrapper.sendFailure(42);

    return 0;
}
