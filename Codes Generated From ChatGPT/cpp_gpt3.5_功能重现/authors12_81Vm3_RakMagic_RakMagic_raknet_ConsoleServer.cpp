#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// CommandParserInterface 接口类
class CommandParserInterface {
    public:
    virtual ~CommandParserInterface() {}
    virtual bool Parse(const std::string& cmd_str) = 0;
};

// TransportInterface 接口类
class TransportInterface {
    public:
    virtual ~TransportInterface() {}
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual bool Send(const std::string& data) = 0;
};

// ConsoleServer 类
class ConsoleServer {
    public:
    ConsoleServer(): transport_provider_(nullptr) {}
    virtual ~ConsoleServer() {}

    bool SetTransportProvider(std::shared_ptr<TransportInterface> transport_provider) {
        if (transport_provider == nullptr) {
            return false;
        }

        transport_provider_ = transport_provider;

        // 注册命令解析器到解析器列表中
        if (!AddCommandParser(transport_provider_->GetName(), transport_provider_)) {
            std::cerr << "Failed to register command parser for transport provider." << std::endl;
            return false;
        }

        return true;
    }

    bool AddCommandParser(const std::string& name, std::shared_ptr<CommandParserInterface> parser) {
        if (parser == nullptr || name.empty()) {
            return false;
        }

        auto it = parsers_.find(name);
        if (it != parsers_.end()) {
            return false;
        }

        parsers_[name] = parser;
        return true;
    }

    bool RemoveCommandParser(const std::string& name) {
        auto it = parsers_.find(name);
        if (it == parsers_.end()) {
            return false;
        }

        parsers_.erase(it);
        return true;
    }

    bool Update() {
        if (transport_provider_ == nullptr) {
            return false;
        }

        // 处理新连接和断开连接事件
        if (transport_provider_->IsConnected()) {
            std::cout << "New client connected." << std::endl;
        } else {
            std::cout << "Client disconnected." << std::endl;
        }

        // 接收传输接口接收到的数据，并进行命令解析和执行
        std::string data;
        while (transport_provider_->Receive(data)) {
            std::cout << "Received data: " << data << std::endl;

            // 解析命令
            for (const auto& parser_pair : parsers_) {
                auto parser = parser_pair.second;
                if (parser->Parse(data)) {
                    break;
                }
            }
        }

        return true;
    }

    void Run() {
        if (transport_provider_ == nullptr) {
            std::cerr << "Transport provider not set." << std::endl;
            return;
        }

        // 启动传输接口
        if (!transport_provider_->Start()) {
            std::cerr << "Failed to start transport provider." << std::endl;
            return;
        }

        std::string input;
        while (true) {
            // 读取控制台输入
            std::cout << ">> ";
            std::getline(std::cin, input);

            if (input == "help") {
                // 帮助命令
                std::cout << "Available commands:" << std::endl;
                std::cout << "  help: Show available commands." << std::
                    std::cout << "  exit: Stop the server and exit." << std::endl;
                for (const auto& parser_pair : parsers_) {
                    auto parser = parser_pair.second;
                    std::cout << "  " << parser_pair.first << ": " << parser->GetHelp() << std::endl;
                }
            } else if (input == "exit") {
                // 退出命令
                break;
            } else {
                // 解析并执行命令
                bool found_parser = false;
                for (const auto& parser_pair : parsers_) {
                    auto parser = parser_pair.second;
                    if (parser->Parse(input)) {
                        found_parser = true;
                        break;
                    }
                }
                if (!found_parser) {
                    std::cout << "Command not recognized." << std::endl;
                }
            }
        }

        // 停止传输接口
        transport_provider_->Stop();
    }
    private:
    std::shared_ptr<TransportInterface> transport_provider_;
    std::unordered_map<std::string, std::shared_ptr<CommandParserInterface>> parsers_;
};

// 示例 TransportInterface 实现类
class ExampleTransport: public TransportInterface {
    public:
    ExampleTransport(): connected_(false) {}
    std::string GetName() const override {
        return "example";
    }

    bool IsConnected() const override {
        return connected_;
    }

    bool Start() override {
        connected_ = true;
        return true;
    }

    bool Stop() override {
        connected_ = false;
        return true;
    }

    bool Send(const std::string& data) override {
        if (!connected_) {
            return false;
        }

        std::cout << "ExampleTransport sent data: " << data << std::endl;
        return true;
    }

    bool Receive(std::string& data) override {
        if (!connected_) {
            return false;
        }

        std::cout << "ExampleTransport waiting for data..." << std::endl;
        std::getline(std::cin, data);
        return true;
    }
    private:
    bool connected_;
};

// 示例 CommandParserInterface 实现类
class ExampleParser: public CommandParserInterface {
    public:
    bool Parse(const std::string& cmd_str) override {
        if (cmd_str == "example") {
            std::cout << "ExampleParser executed." << std::endl;
            return true;
        }
        return false;
    }
    std::string GetHelp() const override {
        return "Execute the example command.";
    }
};

// 示例使用
int main() {
// 创建 ConsoleServer 实例
    ConsoleServer console_server;
    // 创建 ExampleTransport 实例
    std::shared_ptr<TransportInterface> example_transport = std::make_shared<ExampleTransport>();

    // 创建 ExampleParser 实例
    std::shared_ptr<CommandParserInterface> example_parser = std::make_shared<ExampleParser>();

    // 设置传输接口，启动传输并注册命令解析器
    console_server.SetTransportProvider(example_transport);
    console_server.AddCommandParser(example_transport->GetName(), example_parser);

    // 运行 ConsoleServer
    console_server.Run();

    return 0;
}
