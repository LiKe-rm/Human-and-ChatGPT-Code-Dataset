#include <iostream>
#include <string>
#include <vector>
#include <map>

class Command
{
    public:
    virtual ~Command() {}
    virtual void Execute(const std::vector<std::string>& args) = 0;
};

class CommandParser
{
    public:
    CommandParser() {}
    virtual ~CommandParser() {}

    // 解析命令行字符串
    virtual void ParseConsoleString(const std::string& consoleString) = 0;

    // 发送命令列表
    virtual void SendCommandList(int destination) = 0;

    // 注册新命令
    virtual void RegisterCommand(const std::string& commandName, Command* command) = 0;

    // 获取已注册的命令信息
    virtual std::map<std::string, Command*> GetRegisteredCommands() const = 0;

    // Socket传输相关功能
    virtual void OnTransportChange() = 0;
    virtual void OnNewIncomingConnection(int connectionId) = 0;
    virtual void OnConnectionLost(int connectionId) = 0;

    // 返回命令执行结果
    virtual void ReturnResult(int connectionId, const std::string& result) = 0;
};

class ConsoleCommandParser: public CommandParser
{
    public:
    ConsoleCommandParser() {}
    virtual ~ConsoleCommandParser() {}

    virtual void ParseConsoleString(const std::string& consoleString) override
    {
        std::vector<std::string> args;
        std::istringstream iss(consoleString);
        std::string token;
        while (std::getline(iss, token, ' '))
        {
            args.push_back(token);
        }

        if (args.size() > 0)
        {
            std::string commandName = args[0];
            args.erase(args.begin());
            ExecuteCommand(commandName, args);
        }
    }

    virtual void SendCommandList(int destination) override
    {
        std::map<std::string, Command*> registeredCommands = GetRegisteredCommands();
        for (auto& command : registeredCommands)
        {
            std::cout << command.first << std::endl;
        }
    }

    virtual void RegisterCommand(const std::string& commandName, Command* command) override
    {
        registeredCommands_[commandName] = command;
    }

    virtual std::map<std::string, Command*> GetRegisteredCommands() const override
    {
        return registeredCommands_;
    }

    virtual void OnTransportChange() override {}
    virtual void OnNewIncomingConnection(int connectionId) override {}
    virtual void OnConnectionLost(int connectionId) override {}

    virtual void ReturnResult(int connectionId, const std::string& result) override
    {
        std::cout << result << std::endl;
    }

    private:
    void ExecuteCommand(const std::string& commandName, const std::vector<std::string>& args)
    {
        std::map<std::string, Command*>::iterator it = registeredCommands_.find(commandName);
        if (it != registeredCommands_.end())
        {
            Command* command = it->second;
            command->Execute(args);
        } else
        {
            std::cout << "Unknown command: " << commandName << std::endl;
        }
    }

    private:
    std::map<std::string, Command*> registeredCommands_;
};

class HelloWorldCommand: public Command
{
    public:
    virtual void Execute(const std::vectorstd::string& args) override
    {
        std::cout << "Hello, world!" << std::endl;
    }
};

class AddCommand: public Command
{
    public:
    virtual void Execute(const std::vectorstd::string& args) override
    {
        if (args.size() < 2)
        {
            std::cout << "Usage: add <num1> <num2>" << std::endl;
            return;
        }
        float num1 = std::stof(args[0]);
        float num2 = std::stof(args[1]);
        float result = num1 + num2;

        std::stringstream ss;
        ss << "Result: " << result;
        std::string resultString = ss.str();
        std::cout << resultString << std::endl;

        CommandParser* parser = GetCommandParser();
        if (parser != nullptr)
        {
            parser->ReturnResult(0, resultString);
        }
    }
    private:
    CommandParser* GetCommandParser() const
    {
    // 在实际应用中，你需要根据你的需求来获取命令解析器的指针
    // 这里只是一个示例，返回空指针
        return nullptr;
    }
};

int main()
{
    ConsoleCommandParser parser;
    parser.RegisterCommand("hello", new HelloWorldCommand());
    parser.RegisterCommand("add", new AddCommand());
    std::string input;
    while (std::getline(std::cin, input))
    {
        parser.ParseConsoleString(input);
    }

    return 0;
}