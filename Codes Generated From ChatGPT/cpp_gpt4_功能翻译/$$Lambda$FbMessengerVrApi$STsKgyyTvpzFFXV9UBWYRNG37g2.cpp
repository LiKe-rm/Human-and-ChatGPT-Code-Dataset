#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <functional>

class FbMessengerVrApi {
public:
    class Contact {
    public:
        int id;
        std::string name;

        Contact(int id, const std::string& name) : id(id), name(name) {}
    };

    using ContactList = std::vector<Contact>;

    class MessengerVrCallback {
    public:
        virtual void onContactListReceived(const ContactList& contacts) = 0;
        virtual ~MessengerVrCallback() = default;
    };

    void getContactListAsync(MessengerVrCallback* callback) {
        // Simulate async operation
        ContactList contacts = {
            {1, "Alice"},
            {2, "Bob"},
            {3, "Carol"},
        };
        callback->onContactListReceived(contacts);
    }
};

class MyMessengerVrCallback : public FbMessengerVrApi::MessengerVrCallback {
public:
    void onContactListReceived(const FbMessengerVrApi::ContactList& contacts) override {
        for (const auto& contact : contacts) {
            std::cout << "Contact ID: " << contact.id << ", Name: " << contact.name << std::endl;
        }
    }
};

int main() {
    FbMessengerVrApi api;
    MyMessengerVrCallback callback;

    api.getContactListAsync(&callback);

    return 0;
}
