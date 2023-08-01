#include <iostream>
#include <memory>
#include <utility>

class Mailbox {
public:
    void some_method() {
        std::cout << "Mailbox method called" << std::endl;
    }
};

class AbstractClass {
public:
    virtual void apply(const std::pair<std::shared_ptr<Mailbox>, bool>&) = 0;
};

class VrMsysMailboxCreator : public AbstractClass {
public:
    static std::shared_ptr<VrMsysMailboxCreator> create_instance() {
        return std::make_shared<VrMsysMailboxCreator>();
    }

    void apply(const std::pair<std::shared_ptr<Mailbox>, bool>& obj) override {
        auto mailbox = obj.first;
        auto flag = obj.second;

        mailbox->some_method();
        std::cout << "Flag value: " << std::boolalpha << flag << std::endl;
    }
};

int main() {
    auto mailbox = std::make_shared<Mailbox>();
    auto instance = VrMsysMailboxCreator::create_instance();

    std::pair<std::shared_ptr<Mailbox>, bool> obj = {mailbox, true};
    instance->apply(obj);

    return 0;
}
