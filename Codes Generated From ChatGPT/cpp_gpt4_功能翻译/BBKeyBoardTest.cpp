#include <iostream>
#include <map>
#include <string>

class Test {
public:
    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual void finish() = 0;
    virtual bool onKeyTouch(int event) = 0;
    virtual bool onKeyDown(int keyCode, int event) = 0;
    virtual bool onKeyUp(int keyCode, int event) = 0;
    virtual void destroy() = 0;
};

class BBKeyBoardTest : public Test {
private:
    const std::string TAG = "BBKeyBoardTest";
    int testKey = 0;
    std::map<int, bool> keys;

public:
    BBKeyBoardTest() {
        for (int i = 0; i < 26; i++) {
            keys.insert(std::pair<int, bool>('A' + i, false));
        }
    }

    void setUp() override {
        std::cout << TAG + "_start_test\n";
    }

    void initView() override {
        // Since we don't have a graphical interface in C++, we'll just initialize our keys here.
        for (auto &key : keys) {
            key.second = true;
        }
    }

    void finish() override {
        // No equivalent in C++
    }

    bool onKeyTouch(int event) override {
        if (keys.count(event) > 0) {
            keys[event] = false;
            testKey++;
            std::cout << TAG + " " + std::to_string(event) + "\n";
            return true;
        }
        return false;
    }

    bool onKeyDown(int keyCode, int event) override {
        std::cout << TAG + " onKeyDown 88888888:" + std::to_string(keyCode) + "\n";
        return true;
    }

    bool onKeyUp(int keyCode, int event) override {
        return true;
    }

    void dispatchMessage(int msg) {
        if (keys.count(msg) > 0 && keys[msg]) {
            std::cout << TAG + " msg.what " + std::to_string(msg) + "\n";
            onKeyTouch(msg);
        }

        if (testKey > 15) {
            std::cout << TAG + " key finish\n";
        }
    }

    void destroy() override {
        // No equivalent in C++
    }
};

int main() {
    BBKeyBoardTest test;
    test.setUp();
    test.initView();
    for (int i = 0; i < 26; i++) {
        test.dispatchMessage('A' + i);
    }
    test.finish();
    return 0;
}
