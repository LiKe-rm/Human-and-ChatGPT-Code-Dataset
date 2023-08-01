#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Task {
public:
    std::string name;
    bool isPass;

    Task(std::string task_name) : name(task_name), isPass(false) {}
};

class AutoAdapter {
private:
    std::vector<std::unique_ptr<Task>> taskList;

public:
    AutoAdapter(std::vector<std::string> tasks) {
        for(const auto& task : tasks) {
            taskList.push_back(std::make_unique<Task>(task));
        }
    }

    int getCount() {
        return taskList.size();
    }

    std::string getItem(int position) {
        if(position < taskList.size()) {
            return taskList[position]->name;
        }
        return "";
    }

    void setPass(int position) {
        if(position < taskList.size()) {
            taskList[position]->isPass = true;
        }
    }

    void setFail(int position) {
        if(position < taskList.size()) {
            taskList[position]->isPass = false;
        }
    }

    void displayTasks() {
        for(const auto& task : taskList) {
            std::cout << "Task: " << task->name;
            std::cout << " - Status: " << (task->isPass ? "PASS" : "FAIL") << std::endl;
        }
    }
};

int main() {
    std::vector<std::string> tasks = {"Task1", "Task2", "Task3", "Task4"};
    AutoAdapter autoAdapter(tasks);

    autoAdapter.setPass(1);
    autoAdapter.setFail(2);

    autoAdapter.displayTasks();

    return 0;
}
