#include <iostream>
#include <string>
#include <map>
#include <discord.h>

class ActivityManager {
public:
    void registerCommand(const std::string& command);
    void registerSteamGameID(int32_t gameID);
    void updateActivity(const discord::Activity& activity);
    void clearActivity();
    void sendJoinRequestReply(discord::User user, discord::ActivityJoinRequestReply reply);
    void sendInvite(discord::User user, discord::ActivityActionType type, std::string targetID);
    void acceptInvite(std::string ticket);

private:
    discord::Core* core;
};

void ActivityManager::registerCommand(const std::string& command) {
    // TODO: 实现注册自定义命令的逻辑
}

void ActivityManager::registerSteamGameID(int32_t gameID) {
    discord::Activity activity{};
    activity.SetType(discord::ActivityType::Playing);
    activity.SetPlatform(discord::ActivityPlatform::Steam);
    activity.SetApplicationID(gameID);
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " updating activity." << std::endl;
    });
}

void ActivityManager::updateActivity(const discord::Activity& activity) {
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " updating activity." << std::endl;
    });
}

void ActivityManager::clearActivity() {
    core->ActivityManager().ClearActivity([](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " clearing activity." << std::endl;
    });
}

void ActivityManager::sendJoinRequestReply(discord::User user, discord::ActivityJoinRequestReply reply) {
    core->ActivityManager().SendJoinRequestReply(user.GetId(), reply, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " sending join request reply." << std::endl;
    });
}

void ActivityManager::sendInvite(discord::User user, discord::ActivityActionType type, std::string targetID) {
    core->ActivityManager().SendInvite(user.GetId(), type, targetID, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " sending invite." << std::endl;
    });
}

void ActivityManager::acceptInvite(std::string ticket) {
    core->ActivityManager().AcceptInvite(ticket.c_str(), [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Success" : "Failed") << " accepting invite." << std::endl;
    });
}

class ActivityEvents {
public:
    static void onActivityJoin(std::string secret);
    static void onActivitySpectate(std::string secret);
    static void onActivityJoinRequest(discord::User user);
    static void onActivityInvite(discord::ActivityActionType type, discord::User user, discord::Activity activity);
};

void ActivityEvents::onActivityJoin(std::stringsecret) {
// TODO: 实现加入活动事件的处理逻辑
    std::cout << "Joining activity with secret: " << secret << std::endl;
}

void ActivityEvents::onActivitySpectate(std::string secret) {
// TODO: 实现观看活动事件的处理逻辑
    std::cout << "Spectating activity with secret: " << secret << std::endl;
}

void ActivityEvents::onActivityJoinRequest(discord::User user) {
// TODO: 实现加入请求事件的处理逻辑
    std::cout << "User " << user.GetUsername() << " requested to join the activity" << std::endl;
}

void ActivityEvents::onActivityInvite(discord::ActivityActionType type, discord::User user, discord::Activity activity) {
// TODO: 实现活动邀请事件的处理逻辑
    std::cout << "User " << user.GetUsername() << " invited you to join the activity" << std::endl;
}

int main() {
    discord::Core* core{};
    auto result = discord::Core::Create(YourClientID, DiscordCreateFlags_Default, &core);
    if (result != discord::Result::Ok) {
        std::cerr << "Failed to instantiate discord core! (err " << static_cast<int>(result) << ")\n";
        return 1;
    }

    ActivityManager activityManager;
    activityManager.registerCommand("your_custom_command");
    activityManager.registerSteamGameID(YourSteamGameID);

    core->ActivityManager().OnActivityJoin.Connect(&ActivityEvents::onActivityJoin);
    core->ActivityManager().OnActivitySpectate.Connect(&ActivityEvents::onActivitySpectate);
    core->ActivityManager().OnActivityJoinRequest.Connect(&ActivityEvents::onActivityJoinRequest);
    core->ActivityManager().OnActivityInvite.Connect(&ActivityEvents::onActivityInvite);

    while (true) {
        core->RunCallbacks();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    core->~Core();
    return 0;
}
