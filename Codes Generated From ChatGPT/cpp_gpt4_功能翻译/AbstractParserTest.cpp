#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "antlr4-runtime.h"
#include "MindcodeLexer.h"
#include "MindcodeParser.h"

class CustomErrorListener : public antlr4::BaseErrorListener {
public:
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                     size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
        errors.push_back("Syntax error: " + offendingSymbol->getText() + " on line " + std::to_string(line) + ":" +
                         std::to_string(charPositionInLine) + ": " + msg);
    }

    const std::vector<std::string> &getErrors() const {
        return errors;
    }

private:
    std::vector<std::string> errors;
};

class AbstractParserTest {
public:
    MindcodeParser::ProgramContext *parse(const std::string &program) {
        antlr4::ANTLRInputStream input(program);
        MindcodeLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        MindcodeParser parser(&tokens);

        auto errorListener = std::make_shared<CustomErrorListener>();
        parser.addErrorListener(errorListener);

        auto context = parser.program();
        if (!errorListener->getErrors().empty()) {
            throw std::runtime_error(mergeErrors(errorListener->getErrors()));
        }
        return context;
    }

    std::pair<MindcodeParser::ProgramContext *, std::vector<std::string>> parseWithErrors(const std::string &program) {
        antlr4::ANTLRInputStream input(program);
        MindcodeLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        MindcodeParser parser(&tokens);

        auto errorListener = std::make_shared<CustomErrorListener>();
        parser.addErrorListener(errorListener);

        auto context = parser.program();
        return std::make_pair(context, errorListener->getErrors());
    }

private:
    std::string mergeErrors(const std::vector<std::string> &errors) {
        std::string result;
        for (const auto &error : errors) {
            result += error + "\n";
        }
        return result;
    }
};

int main() {
    AbstractParserTest parserTest;

    std::string program = "your_program_string_here";

    try {
        auto context = parserTest.parse(program);
        // Do something with the context
    } catch (const std::runtime_error &e) {
        std::cerr << "Error parsing program: " << e.what() << std::endl;
    }

    auto contextWithErrors = parserTest.parseWithErrors(program);
    auto context = contextWithErrors.first;
    auto errors = contextWithErrors.second;

    if (!errors.empty()) {
        for (const auto &error : errors) {
            std::cerr << "Error: " << error << std::endl;
        }
    }

    return 0;
}
