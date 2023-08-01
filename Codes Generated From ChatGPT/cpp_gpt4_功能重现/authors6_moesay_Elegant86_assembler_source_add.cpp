#include <iostream>
#include <vector>
#include <string>
#include <map>

class InstRet_T {
public:
    std::vector<uint8_t> machine_code;
    bool success;
    std::string error_message;

    InstRet_T() : success(true) {}
};

class Add {
private:
    std::map<std::string, uint8_t> reg_codes = {
        {"al", 0}, {"cl", 1}, {"dl", 2}, {"bl", 3},
        {"ah", 4}, {"ch", 5}, {"dh", 6}, {"bh", 7},
        {"eax", 0}, {"ecx", 1}, {"edx", 2}, {"ebx", 3},
        {"esp", 4}, {"ebp", 5}, {"esi", 6}, {"edi", 7}
    };

    uint8_t getOperandType(const std::string &operand) {
        if (reg_codes.find(operand) != reg_codes.end()) {
            return 0; // register
        }
        return 1; // memory
    }

    uint8_t getOpcode(const std::string &operand1, const std::string &operand2) {
        uint8_t opcode_base = 0x00; // ADD opcode base
        uint8_t operand1_type = getOperandType(operand1);
        uint8_t operand2_type = getOperandType(operand2);

        if (operand1_type == 0 && operand2_type == 0) {
            return opcode_base; // register to register
        } else if (operand1_type == 0 && operand2_type == 1) {
            return opcode_base + 1; // memory to register
        } else if (operand1_type == 1 && operand2_type == 0) {
            return opcode_base + 2; // register to memory
        } else {
            return 0xFF; // invalid combination
        }
    }

    uint8_t modRegRmGenerator(const std::string &operand1, const std::string &operand2) {
        uint8_t mod = 0;
        uint8_t reg = reg_codes[operand1];
        uint8_t rm = reg_codes[operand2];

        mod = 0xC0; // 11 for register to register
        return mod | (reg << 3) | rm;
    }

public:
    InstRet_T process(const std::string &operand1, const std::string &operand2) {
        InstRet_T result;
        uint8_t opcode = getOpcode(operand1, operand2);

        if (opcode == 0xFF) {
            result.success = false;
            result.error_message = "Invalid operand combination.";
            return result;
        }

        uint8_t mod_reg_rm = modRegRmGenerator(operand1, operand2);
        result.machine_code.push_back(opcode);
        result.machine_code.push_back(mod_reg_rm);
        return result;
    }
};

int main() {
    Add add;
    std::string operand1 = "eax";
    std::string operand2 = "ebx";
    InstRet_T result = add.process(operand1, operand2);

    if (result.success) {
        std::cout << "Machine code: ";
        for (auto byte : result.machine_code) {
            std::cout << "0x" << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: " << result.error_message << std::endl;
    }

    return 0;
}
