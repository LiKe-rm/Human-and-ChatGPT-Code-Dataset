#include <iostream>
#include <functional>
#include <memory>
#include <vector>

namespace oculus {
namespace messengervr {
namespace oc {

class MessengerManagerJNI {
public:
    MessengerManagerJNI() = default;
    ~MessengerManagerJNI() = default;

    void exampleFunction() {
        std::cout << "Example function in MessengerManagerJNI" << std::endl;
    }
};

class AbstractC13031yl {
public:
    virtual ~AbstractC13031yl() = default;
    virtual std::shared_ptr<MessengerManagerJNI> apply(const std::shared_ptr<MessengerManagerJNI>& obj) = 0;
};

class AbstractC136820a {
public:
    virtual ~AbstractC136820a() = default;

    static std::shared_ptr<MessengerManagerJNI> A01(const std::shared_ptr<MessengerManagerJNI>& obj) {
        obj->exampleFunction();
        return obj;
    }
};

class Hjf81Zy01koTYndUgnXdbUxVtUQ2 : public AbstractC13031yl {
public:
    Hjf81Zy01koTYndUgnXdbUxVtUQ2() = default;
    ~Hjf81Zy01koTYndUgnXdbUxVtUQ2() = default;

    std::shared_ptr<MessengerManagerJNI> apply(const std::shared_ptr<MessengerManagerJNI>& obj) override {
        return AbstractC136820a::A01(obj);
    }
};

class OcMessengerVrApi {
public:
    OcMessengerVrApi() {
        instance = std::make_shared<Hjf81Zy01koTYndUgnXdbUxVtUQ2>();
    }
    ~OcMessengerVrApi() = default;

    std::shared_ptr<MessengerManagerJNI> createMessengerManagerUpdatesObservable(const std::shared_ptr<MessengerManagerJNI>& obj) {
        return instance->apply(obj);
    }

private:
    std::shared_ptr<Hjf81Zy01koTYndUgnXdbUxVtUQ2> instance;
};

} // namespace oc
} // namespace messengervr
} // namespace oculus

int main() {
    using namespace oculus::messengervr::oc;

    std::shared_ptr<MessengerManagerJNI> manager = std::make_shared<MessengerManagerJNI>();
    OcMessengerVrApi api;

    std::shared_ptr<MessengerManagerJNI> updatedManager = api.createMessengerManagerUpdatesObservable(manager);
    return 0;
}
