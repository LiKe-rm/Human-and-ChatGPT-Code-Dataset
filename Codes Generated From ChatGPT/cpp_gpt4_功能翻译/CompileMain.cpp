#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>

std::tuple<std::string, std::vector<std::string>> compile(const std::string& contents, bool optimize);

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool compileMindcode(const std::string& contents, bool optimize) {
    auto [compiledCode, syntaxErrors] = compile(contents, optimize);

    if (syntaxErrors.empty()) {
        std::cout << compiledCode << std::endl;
        return true;
    } else {
        for (const auto& err : syntaxErrors) {
            std::cerr << err << std::endl;
        }
        return false;
    }
}

int main(int argc, char* argv[]) {
    bool optimize = false;
    std::string filename;
    std::string contents;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o") {
            optimize = true;
        } else if (filename.empty()) {
            filename = arg;
        }
    }

    if (filename.empty()) {
        std::string line;
        while (std::getline(std::cin, line)) {
            contents += line + "\n";
        }
    } else {
        contents = readFile(filename);
    }

    if (!compileMindcode(contents, optimize)) {
        return 1;
    }

    return 0;
}
