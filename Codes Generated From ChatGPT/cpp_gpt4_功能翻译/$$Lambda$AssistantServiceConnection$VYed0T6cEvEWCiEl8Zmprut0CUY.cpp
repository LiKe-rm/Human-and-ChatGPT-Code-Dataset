#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <map>
#include <memory>

enum class AssistantErrorType {
    INCOMPATIBLE_DEVICE,
    UNKNOWN_ERROR
};

class OculusAssistantAttentionListener {
public:
    virtual bool onError(AssistantErrorType errorType) = 0;
};

class AssistantServiceConnection {
public:
    void registerAttentionListener(std::shared_ptr<OculusAssistantAttentionListener> listener) {
        attentionListeners.push_back(listener);
    }

    void notifyError(AssistantErrorType errorType) {
        for (const auto& listener : attentionListeners) {
            listener->onError(errorType);
        }
    }

private:
    std::vector<std::shared_ptr<OculusAssistantAttentionListener>> attentionListeners;
};

class IncompatibleDeviceErrorListener : public OculusAssistantAttentionListener {
public:
    bool onError(AssistantErrorType errorType) override {
        if (errorType == AssistantErrorType::INCOMPATIBLE_DEVICE) {
            std::cout << "Incompatible device error occurred" << std::endl;
            return true;
        }
        return false;
    }
};

class UnknownErrorListener : public OculusAssistantAttentionListener {
public:
    bool onError(AssistantErrorType errorType) override {
        if (errorType == AssistantErrorType::UNKNOWN_ERROR) {
            std::cout << "Unknown error occurred" << std::endl;
            return true;
        }
        return false;
    }
};

int main() {
    AssistantServiceConnection assistantServiceConnection;
    std::shared_ptr<OculusAssistantAttentionListener> incompatibleDeviceErrorListener =
        std::make_shared<IncompatibleDeviceErrorListener>();
    std::shared_ptr<OculusAssistantAttentionListener> unknownErrorListener =
        std::make_shared<UnknownErrorListener>();

    assistantServiceConnection.registerAttentionListener(incompatibleDeviceErrorListener);
    assistantServiceConnection.registerAttentionListener(unknownErrorListener);

    // Simulate an error event
    assistantServiceConnection.notifyError(AssistantErrorType::INCOMPATIBLE_DEVICE);

    return 0;
}
