#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <map>

class Tool {
public:
    static void toolLog(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

class AutoAdapter {
private:
    std::vector<std::string> data;
public:
    AutoAdapter(std::vector<std::string>& data) : data(data) {}
    // other functions...
};

class MyAdapter {
private:
    std::vector<std::string> data;
public:
    MyAdapter(std::vector<std::string>& data) : data(data) {}
    // other functions...
};

class AutotestMainActivityFirst {
private:
    std::vector<std::string> autolist;
    std::vector<std::string> list;
    AutoAdapter* aAdapter;
    MyAdapter* mAdapter;
    std::map<int, bool> flags;
    std::function<void(int)> callback;

    void initList(const std::string& tag) {
        if (tag == "tab1") {
            autolist.push_back("BlueTooth");
        } else {
            list.push_back("Some other tag");
        }
    }

    void initData(const std::string& tag, std::vector<std::string>& al) {
        initList(tag);
        if (tag == "tab1") {
            aAdapter = new AutoAdapter(al);
        } else {
            mAdapter = new MyAdapter(al);
        }
    }

    void runCase(int caseIndex) {
        Tool::toolLog("start test position: " + std::to_string(caseIndex));
        callback(caseIndex);
    }

public:
    AutotestMainActivityFirst(const std::function<void(int)>& callback) : callback(callback) {}

    void StartAutoActivity() {
        std::thread([this]() {
            for (int i = 0; i < autolist.size(); i++) {
                runCase(i);
                // wait for finish...
            }
            Tool::toolLog("finish all the test!");
        }).detach();
    }

    // other functions...

    void selectAll(bool flag) {
        for (int i = 0; i < list.size(); i++) {
            flags[i] = true;
        }
    }

    void clearAll(bool flag) {
        for (int i = 0; i < list.size(); i++) {
            flags[i] = false;
        }
    }

    void dataChanged() {
        // Update data in mAdapter
    }
};

int main() {
    AutotestMainActivityFirst activity([](int caseIndex) {
        // simulate test activity
        std::cout << "Running test case: " << caseIndex << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    activity.StartAutoActivity();

    // Simulate user input to select all and clear all
    activity.selectAll(true);
    activity.dataChanged();
    activity.clearAll(true);
    activity.dataChanged();

    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
