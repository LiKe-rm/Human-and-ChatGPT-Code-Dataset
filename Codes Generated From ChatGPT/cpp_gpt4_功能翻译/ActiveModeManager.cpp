#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <chrono>
#include <functional>

class Role {
public:
    virtual std::string toString() const = 0;
};

class SoftApRole : public Role {};

class ClientRole : public Role {};

class ClientConnectivityRole : public ClientRole {};

class ClientInternetConnectivityRole : public ClientConnectivityRole {};

class ActiveModeManager {
public:
    using Listener = std::function<void(ActiveModeManager&)>;

    virtual ~ActiveModeManager() = default;

    virtual void stop() = 0;

    virtual const Role* getRole() const = 0;

    virtual const Role* getPreviousRole() const = 0;

    virtual std::chrono::milliseconds getLastRoleChangeSinceBootMs() const = 0;

    virtual std::string getInterfaceName() const = 0;

    virtual void dump() const = 0;

    virtual void enableVerboseLogging(bool verbose) = 0;

    virtual long getId() const = 0;
};

class RoleManager {
public:
    static SoftApRole ROLE_SOFTAP_TETHERED;
    static SoftApRole ROLE_SOFTAP_LOCAL_ONLY;
    static ClientRole ROLE_CLIENT_SCAN_ONLY;
    static ClientConnectivityRole ROLE_CLIENT_SECONDARY_TRANSIENT;
    static ClientConnectivityRole ROLE_CLIENT_LOCAL_ONLY;
    static ClientInternetConnectivityRole ROLE_CLIENT_PRIMARY;
    static ClientInternetConnectivityRole ROLE_CLIENT_SECONDARY_LONG_LIVED;
};

SoftApRole RoleManager::ROLE_SOFTAP_TETHERED;
SoftApRole RoleManager::ROLE_SOFTAP_LOCAL_ONLY;
ClientRole RoleManager::ROLE_CLIENT_SCAN_ONLY;
ClientConnectivityRole RoleManager::ROLE_CLIENT_SECONDARY_TRANSIENT;
ClientConnectivityRole RoleManager::ROLE_CLIENT_LOCAL_ONLY;
ClientInternetConnectivityRole RoleManager::ROLE_CLIENT_PRIMARY;
ClientInternetConnectivityRole RoleManager::ROLE_CLIENT_SECONDARY_LONG_LIVED;

// Example implementation of an ActiveModeManager

class ExampleActiveModeManager : public ActiveModeManager {
public:
    ExampleActiveModeManager() : mId(++sNextId) {}

    void stop() override {
        // Implement stop functionality
    }

    const Role* getRole() const override {
        return &RoleManager::ROLE_CLIENT_PRIMARY;
    }

    const Role* getPreviousRole() const override {
        return nullptr;
    }

    std::chrono::milliseconds getLastRoleChangeSinceBootMs() const override {
        return std::chrono::milliseconds(0);
    }

    std::string getInterfaceName() const override {
        return "wlan0";
    }

    void dump() const override {
        // Implement dump functionality
    }

    void enableVerboseLogging(bool verbose) override {
        // Implement verbose logging functionality
    }

    long getId() const override {
        return mId;
    }

private:
    static long sNextId;
    long mId;
};

long ExampleActiveModeManager::sNextId = 0;

int main() {
    std::vector<std::unique_ptr<ActiveModeManager>> modeManagers;

    auto manager = std::make_unique<ExampleActiveModeManager>();
    modeManagers.push_back(std::move(manager));

    for (const auto& modeManager : modeManagers) {
        std::cout << "ActiveModeManager ID: " << modeManager->getId() << std::endl;
    }

    return 0;
}
