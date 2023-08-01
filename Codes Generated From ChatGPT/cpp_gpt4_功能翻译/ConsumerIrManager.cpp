#include <iostream>
#include <vector>
#include <memory>
#include <exception>

class Tool {
public:
    static void log(const std::string& tag, const std::string& message) {
        std::cout << tag << ": " << message << std::endl;
    }
};

class IConsumerIrService {
public:
    virtual bool hasIrEmitter() = 0;
    virtual void transmit(const std::string& packageName, int carrierFrequency, const std::vector<int>& pattern) = 0;
    virtual std::vector<int> getCarrierFrequencies() = 0;
};

class ConsumerIrService : public IConsumerIrService {
public:
    bool hasIrEmitter() override {
        // Implement actual code here
        return true;
    }

    void transmit(const std::string& packageName, int carrierFrequency, const std::vector<int>& pattern) override {
        // Implement actual code here
    }

    std::vector<int> getCarrierFrequencies() override {
        // Implement actual code here
        return std::vector<int>{};
    }
};

class CarrierFrequencyRange {
    int mMinFrequency;
    int mMaxFrequency;

public:
    CarrierFrequencyRange(int min, int max) : mMinFrequency(min), mMaxFrequency(max) {}

    int getMinFrequency() {
        return mMinFrequency;
    }

    int getMaxFrequency() {
        return mMaxFrequency;
    }
};

class ConsumerIrManager {
    const std::string mPackageName;
    std::shared_ptr<IConsumerIrService> mService;
    const std::string TAG = "ConsumerIr";

public:
    ConsumerIrManager(const std::string& packageName, std::shared_ptr<IConsumerIrService> service)
        : mPackageName(packageName), mService(service) {}

    bool hasIrEmitter() {
        if (mService == nullptr) {
            Tool::log(TAG, "no consumer ir service.");
            return false;
        }

        try {
            return mService->hasIrEmitter();
        } catch (std::exception& e) {
            Tool::log(TAG, std::string("exception: ") + e.what());
            return false;
        }
    }

    void transmit(int carrierFrequency, std::vector<int> pattern) {
        if (mService == nullptr) {
            Tool::log(TAG, "no consumer ir service.");
            return;
        }

        try {
            mService->transmit(mPackageName, carrierFrequency, pattern);
        } catch (std::exception& e) {
            Tool::log(TAG, std::string("exception: ") + e.what());
        }
    }

    std::vector<CarrierFrequencyRange> getCarrierFrequencies() {
        if (mService == nullptr) {
            Tool::log(TAG, "no consumer ir service.");
            return std::vector<CarrierFrequencyRange>{};
        }

        try {
            std::vector<int> freqs = mService->getCarrierFrequencies();
            std::vector<CarrierFrequencyRange> range;
            for (size_t i = 0; i < freqs.size(); i += 2) {
                range.push_back(CarrierFrequencyRange(freqs[i], freqs[i + 1]));
            }

            return range;
        } catch (std::exception& e) {
            Tool::log(TAG, std::string("exception: ") + e.what());
            return std::vector<CarrierFrequencyRange>{};
        }
    }
};

// Main function to test the above classes
int main() {
    // Create a service
    std::shared_ptr<IConsumerIrService> service = std::make_shared<ConsumerIrService>();

    // Create a manager with package name and service
    ConsumerIrManager manager("com.example.package", service);

    // Check if IR emitter exists
    bool hasIrEmitter = manager.hasIrEmitter();
    std::cout << "Has IR Emitter: " << (hasIrEmitter ? "Yes" : "No") << std::endl;

    // Transmit a pattern
    std::vector<int> pattern{1, 2, 3, 4, 5};
    manager.transmit(100, pattern);

    // Get carrier frequencies
    std::vector<CarrierFrequencyRange> frequencies = manager.getCarrierFrequencies();
    for (const auto& frequency : frequencies) {
        std::cout << "Min Frequency: " << frequency.getMinFrequency()
                  << ", Max Frequency: " << frequency.getMaxFrequency() << std::endl;
    }

    return 0;
}

