#include <iostream>
#include <string>
#include <functional>
#include <map>

class Test {
public:
    enum class ID {
        DEFAULT_ID
    };

    std::string mName;
    ID mId;
    std::function<void()> resetListener;
    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual void finish() = 0;
    virtual std::string getContextTag() = 0;
    virtual void setContextTag() = 0;
    virtual void destroy() = 0;
};

class FactoryresetTest : public Test {
private:
    static constexpr const char* TAG = "FactoryresetTest";
    std::string mMessage;

public:
    FactoryresetTest(ID id, std::string name) {
        mId = id;
        mName = name;
        mMessage = "Factory Reset";
    }

    void setUp() override {
        std::cout << TAG << "_start_test" << std::endl;
    }

    void initView() override {
        std::cout << mName << std::endl;
        resetListener = [this]() {
            std::cout << mMessage << std::endl;
            int choice;
            std::cout << "1. OK\n2. Cancel\n";
            std::cin >> choice;
            switch (choice) {
                case 1:
                    std::cout << "Pass" << std::endl;
                    Factoryreset();
                    break;
                case 2:
                    std::cout << "Fail" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice" << std::endl;
                    break;
            }
        };
    }

    void Factoryreset() {
        std::cout << "Performing Factory Reset..." << std::endl;
        // actual reset operation would go here
    }

    void finish() override {
        // cleanup operations would go here
    }

    std::string getContextTag() override {
        return TAG;
    }

    void setContextTag() override {
        // set context tag operation would go here
    }

    void destroy() override {
        // destruction operations would go here
    }
};

int main() {
    FactoryresetTest test(Test::ID::DEFAULT_ID, "Test1");
    test.setUp();
    test.initView();
    test.resetListener();
    test.finish();
    return 0;
}
