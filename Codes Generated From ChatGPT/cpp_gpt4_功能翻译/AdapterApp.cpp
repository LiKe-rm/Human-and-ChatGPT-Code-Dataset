#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <atomic>
#include <vector>

#ifdef NDEBUG
constexpr bool DBG = false;
#else
constexpr bool DBG = true;
#endif

class Config {
public:
    static void init(AdapterApp* app) {
        // Initialize configuration
        if (DBG) {
            std::cout << "Config initialized" << std::endl;
        }
    }
};

class AdapterApp {
public:
    AdapterApp() {
        if (DBG) {
            sRefCount.fetch_add(1);
            std::cout << "REFCOUNT: Constructed " << this << " Instance Count = " << sRefCount << std::endl;
        }
    }

    void onCreate() {
        if (DBG) {
            std::cout << "onCreate" << std::endl;
        }
        Config::init(this);
    }

    ~AdapterApp() {
        if (DBG) {
            sRefCount.fetch_sub(1);
            std::cout << "REFCOUNT: Finalized: " << this << ", Instance Count = " << sRefCount << std::endl;
        }
    }

private:
    static std::atomic<int> sRefCount;
};

std::atomic<int> AdapterApp::sRefCount{0};

int main() {
    std::vector<std::unique_ptr<AdapterApp>> appInstances;

    auto app = std::make_unique<AdapterApp>();
    app->onCreate();
    appInstances.push_back(std::move(app));

    return 0;
}
