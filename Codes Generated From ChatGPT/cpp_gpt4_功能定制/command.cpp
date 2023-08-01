#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Command {
public:
    std::string name;
    std::vector<std::string> arguments;

    Command(const std::string& name, const std::vector<std::string>& arguments)
        : name(name), arguments(arguments) {}

    void display() {
        std::cout << "Command: " << name << std::endl;
        std::cout << "Arguments: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
};

class CommandLineParser {
public:
    static Command parse(const std::string& input) {
        std::istringstream iss(input);
        std::string token;
        std::string command;
        std::vector<std::string> arguments;

        if (std::getline(iss, token, ' ')) {
            command = token;
        }

        while (std::getline(iss, token, ' ')) {
            arguments.push_back(token);
        }

        return Command(command, arguments);
    }
};

int main(int argc, char** argv) {
    std::string input;
    std::cout << "Enter a command followed by arguments: ";
    std::getline(std::cin, input);

    Command cmd = CommandLineParser::parse(input);
    cmd.display();

    return 0;
}
