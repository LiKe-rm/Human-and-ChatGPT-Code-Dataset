#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// CommandParserInterface �ӿ���
class CommandParserInterface {
    public:
    virtual ~CommandParserInterface() {}
    virtual bool Parse(const std::string& cmd_str) = 0;
};

// TransportInterface �ӿ���
class TransportInterface {
    public:
    virtual ~TransportInterface() {}
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual bool Send(const std::string& data) = 0;
};

// ConsoleServer ��
class ConsoleServer {
    public:
    ConsoleServer(): transport_provider_(nullptr) {}
    virtual ~ConsoleServer() {}

    bool SetTransportProvider(std::shared_ptr<TransportInterface> transport_provider) {
        if (transport_provider == nullptr) {
            return false;
        }

        transport_provider_ = transport_provider;

        // ע��������������������б���
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

        // ���������ӺͶϿ������¼�
        if (transport_provider_->IsConnected()) {
            std::cout << "New client connected." << std::endl;
        } else {
            std::cout << "Client disconnected." << std::endl;
        }

        // ���մ���ӿڽ��յ������ݣ����������������ִ��
        std::string data;
        while (transport_provider_->Receive(data)) {
            std::cout << "Received data: " << data << std::endl;

            // ��������
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

        // ��������ӿ�
        if (!transport_provider_->Start()) {
            std::cerr << "Failed to start transport provider." << std::endl;
            return;
        }

        std::string input;
        while (true) {
            // ��ȡ����̨����
            std::cout << ">> ";
            std::getline(std::cin, input);

            if (input == "help") {
                // ��������
                std::cout << "Available commands:" << std::endl;
                std::cout << "  help: Show available commands." << std::
                    std::cout << "  exit: Stop the server and exit." << std::endl;
                for (const auto& parser_pair : parsers_) {
                    auto parser = parser_pair.second;
                    std::cout << "  " << parser_pair.first << ": " << parser->GetHelp() << std::endl;
                }
            } else if (input == "exit") {
                // �˳�����
                break;
            } else {
                // ������ִ������
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

        // ֹͣ����ӿ�
        transport_provider_->Stop();
    }
    private:
    std::shared_ptr<TransportInterface> transport_provider_;
    std::unordered_map<std::string, std::shared_ptr<CommandParserInterface>> parsers_;
};

// ʾ�� TransportInterface ʵ����
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

// ʾ�� CommandParserInterface ʵ����
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

// ʾ��ʹ��
int main() {
// ���� ConsoleServer ʵ��
    ConsoleServer console_server;
    // ���� ExampleTransport ʵ��
    std::shared_ptr<TransportInterface> example_transport = std::make_shared<ExampleTransport>();

    // ���� ExampleParser ʵ��
    std::shared_ptr<CommandParserInterface> example_parser = std::make_shared<ExampleParser>();

    // ���ô���ӿڣ��������䲢ע�����������
    console_server.SetTransportProvider(example_transport);
    console_server.AddCommandParser(example_transport->GetName(), example_parser);

    // ���� ConsoleServer
    console_server.Run();

    return 0;
}
