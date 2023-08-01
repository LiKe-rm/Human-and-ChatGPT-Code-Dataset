// Evaluator.cpp
#include <algorithm>
#include <stdexcept>
#include "Evaluator.h"

Evaluator::Evaluator(std::ostream* output) : isExit(false), output(output) {}

void Evaluator::evaluate(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(command);

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty()) {
        return;
    }

    if (tokens[0] == "push") {
        if (tokens.size() != 2) {
            throw std::runtime_error("Invalid number of arguments for push");
        }
        push(std::stoi(tokens[1]));
    } else if (tokens[0] == "pop") {
        pop();
    } else if (tokens[0] == "dump") {
        dump();
    } else if (tokens[0] == "add") {
        add();
    } else if (tokens[0] == "sub") {
        sub();
    } else if (tokens[0] == "mul") {
        mul();
    } else if (tokens[0] == "div") {
        div();
    } else if (tokens[0] == "mod") {
        mod();
    } else if (tokens[0] == "assert") {
        if (tokens.size() != 2) {
            throw std::runtime_error("Invalid number of arguments for assert");
        }
        assert(std::stoi(tokens[1]));
    } else if (tokens[0] == "print") {
        print();
    } else if (tokens[0] == "exit") {
        exit();
    } else if (tokens[0] == "sort") {
        sort();
    } else if (tokens[0] == "sumall") {
        sumall();
    } else if (tokens[0] == "dumpex") {
        dumpex();
    } else {
        throw std::runtime_error("Unknown command: " + tokens[0]);
    }
}

bool Evaluator::hasExited() const {
    return isExit;
}

void Evaluator::push(int value) {
    stack.push(value);
}

int Evaluator::pop() {
    if (stack.empty()) {
        throw std::runtime_error("Cannot pop from an empty stack");
    }
    int value = stack.top();
    stack.pop();
    return value;
}

void Evaluator::dump() {
    std::stack<int> tmp;
    while (!stack.empty()) {
        *output << stack.top() << " ";
        tmp.push(stack.top());
        stack.pop();
    }
    *output << std::endl;

    while (!tmp.empty()) {
        stack.push(tmp.top());
        tmp.pop();
    }
}

void Evaluator::add() {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough values on the stack for addition");
    }
    int a = pop();
    int b = pop();
    push(a + b);
}

void Evaluator::sub() {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough values on the stack for subtraction");
    }
    int a = pop();
    int b = pop();
    push(a - b);
}

void Evaluator::mul() {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough values on the stack for multiplication");
    }
    int a = pop();
    int b = pop();
    push(a * b);
}

void Evaluator::div() {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough values on the stack for division");
    }
    int a = pop();
    int b = pop();
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    push(a / b);
}

void Evaluator::mod() {
    if (stack.size() < 2) {
        throw std::runtime_error("Not enough values on the stack for modulo");
    }
    int a = pop();
    int b = pop();
    if (b == 0) {
        throw std::runtime_error("Modulo by zero");
    }
    push(a % b);
}

void Evaluator::assert(int value) {
    if (stack.empty()) {
        throw std::runtime_error("Cannot assert an empty stack");
    }
    if (stack.top() != value) {
        throw std::runtime_error("Assertion failed");
    }
}

void Evaluator::print() {
    if (stack.empty()) {
        throw std::runtime_error("Cannot print from an empty stack");
    }
    *output << static_cast<char>(stack.top() & 0xFF) << std::endl;
}

void Evaluator::exit() {
    isExit = true;
}

void Evaluator::sort() {
    std::vector<int> values;
    while (!stack.empty()) {
        values.push_back(pop());
    }
    std::sort(values.begin(), values.end());
    for (int value : values) {
        push(value);
    }
}

void Evaluator::sumall() {
    int sum = 0;
    while (!stack.empty()) {
        sum += pop();
    }
    push(sum);
}

void Evaluator::dumpex() {
    std::stack<int> tmp;
    while (!stack.empty()) {
        *output << stack.top() << " (int) ";
        tmp.push(stack.top());
        stack.pop();
    }
    *output << std::endl;

    while (!tmp.empty()) {
        stack.push(tmp.top());
        tmp.pop();
    }
}

