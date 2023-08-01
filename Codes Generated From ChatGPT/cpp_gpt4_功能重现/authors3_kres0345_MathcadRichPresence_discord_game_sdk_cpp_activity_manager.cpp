#include <iostream>
#include <string>
#include <vector>

class ActivityManager {
public:
    ActivityManager();
    ~ActivityManager();

    // Event callbacks
    void OnActivityJoin(const std::string& secret);
    void OnActivitySpectate(const std::string& secret);
    void OnActivityJoinRequest(const std::string& userId);
    void OnActivityInvite(const std::string& userId, const std::string& secret);

    // Member functions
    void RegisterCommand(const std::string& command);
    void RegisterSteam(const std::string& steamId);
    void UpdateActivity(const std::string& activity);
    void ClearActivity();
    void SendRequestReply(const std::string& userId, bool accept);
    void SendInvite(const std::string& userId);
    void AcceptInvite(const std::string& secret);

private:
    std::vector<std::string> registeredCommands;
    std::string currentActivity;
    std::string steamId;
};

ActivityManager::ActivityManager() {
}

ActivityManager::~ActivityManager() {
}

void ActivityManager::OnActivityJoin(const std::string& secret) {
    std::cout << "OnActivityJoin: " << secret << std::endl;
}

void ActivityManager::OnActivitySpectate(const std::string& secret) {
    std::cout << "OnActivitySpectate: " << secret << std::endl;
}

void ActivityManager::OnActivityJoinRequest(const std::string& userId) {
    std::cout << "OnActivityJoinRequest: " << userId << std::endl;
}

void ActivityManager::OnActivityInvite(const std::string& userId, const std::string& secret) {
    std::cout << "OnActivityInvite: " << userId << ", " << secret << std::endl;
}

void ActivityManager::RegisterCommand(const std::string& command) {
    registeredCommands.push_back(command);
}

void ActivityManager::RegisterSteam(const std::string& steamId) {
    this->steamId = steamId;
}

void ActivityManager::UpdateActivity(const std::string& activity) {
    currentActivity = activity;
}

void ActivityManager::ClearActivity() {
    currentActivity.clear();
}

void ActivityManager::SendRequestReply(const std::string& userId, bool accept) {
    std::cout << "SendRequestReply: " << userId << ", " << (accept ? "Accepted" : "Declined") << std::endl;
}

void ActivityManager::SendInvite(const std::string& userId) {
    std::cout << "SendInvite: " << userId << std::endl;
}

void ActivityManager::AcceptInvite(const std::string& secret) {
    std::cout << "AcceptInvite: " << secret << std::endl;
}

int main() {
    ActivityManager manager;
    manager.RegisterCommand("my_custom_command");
    manager.RegisterSteam("123456789");
    manager.UpdateActivity("Playing my game");
    manager.ClearActivity();
    manager.SendRequestReply("user123", true);
    manager.SendInvite("user456");
    manager.AcceptInvite("invite_secret");

    return 0;
}
