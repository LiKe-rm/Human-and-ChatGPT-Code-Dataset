#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <sstream>

class FirstPhase {
public:
    using output_t = int; // 您可以根据需要自定义output_t的类型

    static std::vector<output_t> assemble(const std::vector<std::string>& input) {
        std::vector<output_t> result;
        for (const auto& line : input) {
            std::string cleanedLine = removeComments(line);
            std::string label = getLabel(cleanedLine);
            if (!label.empty()) {
                codeInfo[label] = result.size();
            }

            std::string mnemonic = getMnemonic(cleanedLine);
            if (!mnemonic.empty()) {
                if (validate(mnemonic)) {
                    result.push_back(translateToOutput(mnemonic));
                } else {
                    errors += "Error: Invalid instruction \"" + mnemonic + "\" at line " + std::to_string(result.size() + 1) + "\n";
                }
            }
        }
        return result;
    }

    static bool validate(const std::string& mnemonic) {
        // 在此处实现您的验证逻辑
        return true; // 返回true表示验证通过，返回false表示验证失败
    }

private:
    static std::string removeComments(const std::string& line) {
        auto commentPosition = line.find(';');
        if (commentPosition != std::string::npos) {
            return line.substr(0, commentPosition);
        }
        return line;
    }

    static std::string getLabel(const std::string& line) {
        auto labelEnd = line.find(':');
        if (labelEnd != std::string::npos) {
            return line.substr(0, labelEnd);
        }
        return "";
    }

    static std::string getMnemonic(const std::string& line) {
        std::string cleanedLine = line;
        auto labelEnd = line.find(':');
        if (labelEnd != std::string::npos) {
            cleanedLine = line.substr(labelEnd + 1);
        }

        std::stringstream ss(cleanedLine);
        std::string mnemonic;
        ss >> mnemonic;
        return mnemonic;
    }

    static output_t translateToOutput(const std::string& mnemonic) {
        // 在此处实现您的翻译逻辑
        return 0; // 返回翻译后的output_t
    }

    static std::string errors;
    static std::unordered_map<std::string, size_t> codeInfo;
};

std::string FirstPhase::errors = "";
std::unordered_map<std::string, size_t> FirstPhase::codeInfo;

int main() {
    std::vector<std::string> input = {
        "LABEL1: ADD R1, R2, R3",
        "MOV R4, R5",
        "LABEL2: SUB R1, R2, R3 ; Here is a comment",
        "; Another comment line",
        "JMP LABEL1"
    };

    std::vector<FirstPhase::output_t> output = FirstPhase::assemble(input);

    if (FirstPhase::errors.empty()) {
        std::cout << "Assembled output:\n";
        for (const auto& value : output) {
            std::cout << value << '\n';
        }
    } else {
        std::cerr << "Errors found:\n" << FirstPhase::errors;
    }

    return 0;
}
