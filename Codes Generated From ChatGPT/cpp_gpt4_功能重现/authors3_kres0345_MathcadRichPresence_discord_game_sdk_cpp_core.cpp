#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <map>
#include "discord_internal_api.hpp"

namespace DiscordCPP {

// Forward declarations
class UserManager;
class ActivityManager;
class RelationshipManager;
class RoomManager;
class NetworkManager;
class OverlayManager;
class StorageManager;
class VoiceManager;
class AchievementManager;

class Core {
public:
    Core(const std::string& token);
    ~Core();

    UserManager& get_user_manager() const;
    ActivityManager& get_activity_manager() const;
    RelationshipManager& get_relationship_manager() const;
    RoomManager& get_room_manager() const;
    NetworkManager& get_network_manager() const;
    OverlayManager& get_overlay_manager() const;
    StorageManager& get_storage_manager() const;
    VoiceManager& get_voice_manager() const;
    AchievementManager& get_achievement_manager() const;

    void set_log_hook(std::function<void(const std::string&)> log_hook);
    void set_callback(std::function<void()> callback);

private:
    std::unique_ptr<UserManager> _user_manager;
    std::unique_ptr<ActivityManager> _activity_manager;
    std::unique_ptr<RelationshipManager> _relationship_manager;
    std::unique_ptr<RoomManager> _room_manager;
    std::unique_ptr<NetworkManager> _network_manager;
    std::unique_ptr<OverlayManager> _overlay_manager;
    std::unique_ptr<StorageManager> _storage_manager;
    std::unique_ptr<VoiceManager> _voice_manager;
    std::unique_ptr<AchievementManager> _achievement_manager;

    std::function<void(const std::string&)> _log_hook;
    std::function<void()> _callback;

    std::unique_ptr<DiscordInternalAPI> _internal_api;
};

// UserManager, ActivityManager, RelationshipManager, RoomManager, NetworkManager, OverlayManager, StorageManager, VoiceManager, and AchievementManager classes should be implemented separately, but they will follow a similar structure.

Core::Core(const std::string& token) {
    _internal_api = std::make_unique<DiscordInternalAPI>(token);

    // Initialize all the managers
    _user_manager = std::make_unique<UserManager>(_internal_api.get());
    _activity_manager = std::make_unique<ActivityManager>(_internal_api.get());
    _relationship_manager = std::make_unique<RelationshipManager>(_internal_api.get());
    _room_manager = std::make_unique<RoomManager>(_internal_api.get());
    _network_manager = std::make_unique<NetworkManager>(_internal_api.get());
    _overlay_manager = std::make_unique<OverlayManager>(_internal_api.get());
    _storage_manager = std::make_unique<StorageManager>(_internal_api.get());
    _voice_manager = std::make_unique<VoiceManager>(_internal_api.get());
    _achievement_manager = std::make_unique<AchievementManager>(_internal_api.get());
}

Core::~Core() = default;

UserManager& Core::get_user_manager() const {
    return *_user_manager;
}

ActivityManager& Core::get_activity_manager() const {
    return *_activity_manager;
}

RelationshipManager& Core::get_relationship_manager() const {
    return *_relationship_manager;
}

RoomManager& Core::get_room_manager() const {
    return *_room_manager;
}

NetworkManager& Core::get_network_manager() const {
    return *_network_manager;
}

OverlayManager& Core::get_overlay_manager() const {
    return *_overlay_manager;
}

StorageManager& Core::get_storage_manager() const {
    return *_storage_manager;
}

VoiceManager& Core::get_voice_manager() const {
    return *_voice_manager;
}

AchievementManager& Core::get_achievement_manager() const {
    return *_achievement
    _manager;
}

void Core::set_log_hook(std::function<void(const std::string&)> log_hook) {
    _log_hook = std::move(log_hook);
    _internal_api->set_log_hook(_log_hook);
}

void Core::set_callback(std::function<void()> callback) {
    _callback = std::move(callback);
    _internal_api->set_callback(_callback);
}

} // namespace DiscordCPP

int main() {
    // Example usage of the Core class
    const std::string token = "your_bot_token";
    DiscordCPP::Core discord_core(token);
    // Get UserManager and fetch user information
    auto& user_manager = discord_core.get_user_manager();
    auto user = user_manager.get_user("user_id");
    std::cout << "User: " << user.name << std::endl;

    // Set log hook
    discord_core.set_log_hook([](const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    });

    // Set callback
    discord_core.set_callback([]() {
        std::cout << "Callback triggered" << std::endl;
    });

    // Add your event handling, etc. here
    // ...

    return 0;
}
