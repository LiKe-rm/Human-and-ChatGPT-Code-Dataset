#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// 定义命令枚举
enum Command {
    CMD_HELLO,
    CMD_ADD,
    CMD_SUBTRACT,
    CMD_MULTIPLY,
    CMD_EXIT
};

// 定义命令参数类型
typedef vector<string> CommandArgs;

// 定义命令处理函数类型
typedef function<void(const CommandArgs&)> CommandHandler;

// 定义命令处理函数
void cmdHelloWorld(const CommandArgs& args) {
    cout << "Hello World!" << endl;
}

void cmdAdd(const CommandArgs& args) {
    if (args.size() != 2) {
        cout << "Usage: add <num1> <num2>" << endl;
        return;
    }
    double num1 = stod(args[0]);
    double num2 = stod(args[1]);
    cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
}

void cmdSubtract(const CommandArgs& args) {
    if (args.size() != 2) {
        cout << "Usage: subtract <num1> <num2>" << endl;
        return;
    }
    double num1 = stod(args[0]);
    double num2 = stod(args[1]);
    cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
}

void cmdMultiply(const CommandArgs& args) {
    if (args.size() != 2) {
        cout << "Usage: multiply <num1> <num2>" << endl;
        return;
    }
    double num1 = stod(args[0]);
    double num2 = stod(args[1]);
    cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
}

void cmdExit(const CommandArgs& args) {
    exit(0);
}

// 命令处理函数表
map<Command, CommandHandler> commandTable ={
    { CMD_HELLO, cmdHelloWorld },
    { CMD_ADD, cmdAdd },
    { CMD_SUBTRACT, cmdSubtract },
    { CMD_MULTIPLY, cmdMultiply },
    { CMD_EXIT, cmdExit }
};

// 注册所有命令
void registerAllCommands() {
    // TODO: 注册更多命令
}

// 解析命令行输入
void parseCommandLine(const string& input) {
    // 解析命令名称和参数
    size_t spaceIndex = input.find(" ");
    string commandName = input.substr(0, spaceIndex);
    string argsString = input.substr(spaceIndex + 1);
    CommandArgs args;

    // 分割参数字符串
    size_t argIndex = 0;
    while (argIndex < argsString.size()) {
        size_t nextArgIndex = argsString.find(" ", argIndex);
        if (nextArgIndex == string::npos) {
            nextArgIndex
                = argsString.size();
        }
        string arg = argsString.substr(argIndex, nextArgIndex - argIndex);
        args.push_back(arg);
        argIndex = nextArgIndex + 1;
    }
    // 查找并调用命令处理函数
    Command command = static_cast<Command>(-1);
    for (auto& item : commandTable) {
        if (item.first == commandName) {
            command = item.first;
            item.second(args);
            break;
        }
    }
    if (command == static_cast<Command>(-1)) {
        cout << "Unknown command: " << commandName << endl;
    }
}

int main() {
// 注册所有命令
    registerAllCommands();
    // 进入命令行循环
    while (true) {
        string input;
        getline(cin, input);
        parseCommandLine(input);
    }

    return 0;
}