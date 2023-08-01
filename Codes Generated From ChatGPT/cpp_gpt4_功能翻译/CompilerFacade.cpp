#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "MindcodeLexer.h"
#include "MindcodeParser.h"
#include "AstNodeBuilder.h"
#include "LogicInstructionGenerator.h"
#include "LogicInstructionLabelResolver.h"
#include "LogicInstructionPrinter.h"

std::tuple<std::string, std::vector<std::string>> compile(const std::string& sourceCode, bool enableOptimization) {
    std::string instructions = "";
    std::vector<std::string> errors;

    auto lexer = std::make_shared<MindcodeLexer>(sourceCode);
    auto parser = std::make_shared<MindcodeParser>(lexer);
    parser->addErrorListener(/* custom error listener implementation */);

    try {
        auto context = parser->parseProgram();
        auto prog = AstNodeBuilder::generate(context);

        std::vector<LogicInstruction> result;
        if (enableOptimization) {
            result = LogicInstructionGenerator::generateAndOptimize(prog);
        } else {
            result = LogicInstructionGenerator::generateUnoptimized(prog);
        }
        result = LogicInstructionLabelResolver::resolve(result);
        instructions = LogicInstructionPrinter::toString(result);
    } catch (const std::runtime_error& e) {
        errors.push_back(e.what());
    }

    return std::make_tuple(instructions, errors);
}
