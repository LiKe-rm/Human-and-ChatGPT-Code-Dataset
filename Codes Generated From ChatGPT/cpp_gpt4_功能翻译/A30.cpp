#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <functional>

class Zj0 {
public:
    virtual ~Zj0() = default;
    virtual void close() = 0;
};

class CoreImpl {
    // Implementation details...
};

class A30 {
public:
    static std::shared_ptr<A30> f0(std::shared_ptr<Zj0> zj0);

    void addService(const std::string& name, std::function<void(std::shared_ptr<Zj0>)> callback);
    void removeService(const std::string& name);
    void close();

    void onServiceRequested(const std::string& str, std::shared_ptr<Zj0> zj0);

private:
    std::map<std::string, std::function<void(std::shared_ptr<Zj0>)>> services;
};

std::shared_ptr<A30> A30::f0(std::shared_ptr<Zj0> zj0) {
    auto a30 = std::make_shared<A30>();
    // Replace PN0 with your own implementation, as well as QW and C4680s30.
    // For simplicity, we ignore these classes here.
    return a30;
}

void A30::addService(const std::string& name, std::function<void(std::shared_ptr<Zj0>)> callback) {
    services[name] = callback;
}

void A30::removeService(const std::string& name) {
    services.erase(name);
}

void A30::close() {
    services.clear();
}

void A30::onServiceRequested(const std::string& str, std::shared_ptr<Zj0> zj0) {
    auto it = services.find(str);
    if (it != services.end()) {
        it->second(zj0);
    } else {
        zj0->close();
    }
}

class ExampleZj0 : public Zj0 {
public:
    void close() override {
        std::cout << "Closing Zj0" << std::endl;
    }
};

int main() {
    auto a30 = A30::f0(std::make_shared<ExampleZj0>());

    a30->addService("service1", [](std::shared_ptr<Zj0> zj0) {
        std::cout << "Service1 called" << std::endl;
    });

    a30->addService("service2", [](std::shared_ptr<Zj0> zj0) {
        std::cout << "Service2 called" << std::endl;
    });

    a30->onServiceRequested("service1", std::make_shared<ExampleZj0>());
    a30->onServiceRequested("service2", std::make_shared<ExampleZj0>());
    a30->onServiceRequested("unknown", std::make_shared<ExampleZj0>());

    a30->close();

    return 0;
}
