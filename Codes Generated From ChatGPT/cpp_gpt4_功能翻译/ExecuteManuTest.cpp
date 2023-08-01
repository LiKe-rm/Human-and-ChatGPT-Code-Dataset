#include <iostream>
#include <string>

class Test {
public:
    virtual void updateView() = 0;
    virtual void setUp() = 0;
    virtual void initView() = 0;
    virtual bool onKeyDown(int keyCode) = 0;
    virtual bool onKeyUp(int keyCode) = 0;
    virtual void destroy() = 0;
};

class ExecuteManuTest {
private:
    const std::string TAG = "ExecuteManuTest";
    Test* currentTest = nullptr;
    int position;

    void init() {
        currentTest->setUp();
        currentTest->initView();
    }

public:
    ExecuteManuTest(int position, Test* test) : position(position), currentTest(test) {
        init();
    }

    void onCreate() {
        // some code
    }

    void onResume() {
        currentTest->updateView();
    }

    void onPause() {
        // some code
    }

    void onDestroy() {
        currentTest->destroy();
    }

    bool onKeyDown(int keyCode) {
        return currentTest->onKeyDown(keyCode);
    }

    bool onKeyUp(int keyCode) {
        return currentTest->onKeyUp(keyCode);
    }

    void onBackPressed() {
        // some code
    }

    bool dispatchKeyEvent(int keyCode) {
        return currentTest->onKeyUp(keyCode);
    }

    void onActivityResult(int requestCode, int resultCode) {
        // some code
    }
};

class MyTest : public Test {
public:
    void updateView() override {
        std::cout << "Updating view" << std::endl;
    }

    void setUp() override {
        std::cout << "Setting up" << std::endl;
    }

    void initView() override {
        std::cout << "Initializing view" << std::endl;
    }

    bool onKeyDown(int keyCode) override {
        std::cout << "Key down: " << keyCode << std::endl;
        return true;
    }

    bool onKeyUp(int keyCode) override {
        std::cout << "Key up: " << keyCode << std::endl;
        return true;
    }

    void destroy() override {
        std::cout << "Destroying test" << std::endl;
    }
};

int main() {
    MyTest test;
    ExecuteManuTest executeTest(0, &test);

    executeTest.onCreate();
    executeTest.onResume();
    executeTest.onPause();
    executeTest.onDestroy();

    return 0;
}
