#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>

class LogicInstruction {
public:
    std::string opcode;
    std::vector<std::string> args;

    LogicInstruction(const std::string& opcode, const std::vector<std::string>& args)
        : opcode(opcode), args(args) {}
};

class LogicInstructionPipeline {
public:
    virtual void emit(const LogicInstruction& instruction) = 0;
    virtual void flush() = 0;
};

class DeadCodeEliminator : public LogicInstructionPipeline {
    LogicInstructionPipeline* next;

    std::vector<LogicInstruction> program;
    std::unordered_set<std::string> reads;
    std::unordered_map<std::string, std::vector<LogicInstruction>> writes;

public:
    DeadCodeEliminator(LogicInstructionPipeline* next) : next(next) {}

    void emit(const LogicInstruction& instruction) override {
        program.push_back(instruction);
    }

    void flush() override {
        while (analyzeDataflow(), removeUselessWrites()) {}

        for (const auto& instruction : program) {
            next->emit(instruction);
        }
        program.clear();
    }

private:
    void analyzeDataflow() {
        reads.clear();
        writes.clear();
        reads.insert("@counter");

        for (const auto& instruction : program) {
            examineInstruction(instruction);
        }
    }

    bool removeUselessWrites() {
        std::unordered_set<std::string> uselessWrites(writes.begin(), writes.end());
        for (const auto& key : reads) {
            uselessWrites.erase(key);
        }
        for (const auto& key : uselessWrites) {
            const auto& deadInstructions = writes[key];
            program.erase(std::remove_if(program.begin(), program.end(),
                                         [&](const LogicInstruction& inst) {
                                             return std::find(deadInstructions.begin(), deadInstructions.end(), inst) != deadInstructions.end();
                                         }),
                          program.end());
        }

        return !uselessWrites.empty();
    }

    void addWrite(const LogicInstruction& instruction, int index) {
        const std::string& varName = instruction.args[index];
        writes[varName].push_back(instruction);
    }

    void examineInstruction(const LogicInstruction& instruction) {
        if (instruction.opcode == "set") {
            visitSet(instruction);
        } else if (instruction.opcode == "write") {
            visitWrite(instruction);
        } else if (instruction.opcode == "read") {
            visitRead(instruction);
        } else if (instruction.opcode == "jump") {
            visitJump(instruction);
        } else if (instruction.opcode == "op") {
            visitOp(instruction);
        } else {
            // Add cases for all the other opcodes as done in the original Java code
            throw std::runtime_error("Unvisited opcode [" + instruction.opcode + "]");
        }
    }

    // Implement the visit* methods for each opcode as done in the original Java code
    // Example:

    void visitSet(const LogicInstruction& instruction) {
        addWrite(instruction, 0);
        reads.insert(instruction.args[1]);
    }

    void visitWrite(const LogicInstruction& instruction) {
        reads.insert(instruction.args[0]);
        reads.insert(instruction.args[1]);
        reads.insert(instruction.args[2]);
    }

    void visitRead(const LogicInstruction& instruction) {
        addWrite(instruction, 0);
        reads.insert(instruction.args[1]);
        reads.insert(instruction.args[2]);
    }

}