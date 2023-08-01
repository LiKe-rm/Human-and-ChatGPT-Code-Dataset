#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <memory>
#include <variant>

enum class TokenType {
    START_OBJECT,
    END_OBJECT,
    START_ARRAY,
    END_ARRAY,
    FIELD_NAME,
    VALUE_STRING,
    VALUE_NUMBER_INT,
    VALUE_NUMBER_FLOAT,
    VALUE_TRUE,
    VALUE_FALSE,
    VALUE_NULL,
    VALUE_EMBEDDED_OBJECT
};

class TokenBuffer;

class TokenSegment {
public:
    std::vector<std::variant<TokenType, std::string, int, double, bool>> data;
    std::shared_ptr<TokenSegment> next;

    TokenSegment() : data(16), next(nullptr) {}
};

class TokenStack {
public:
    int type;
    int index;
    std::string name;
    std::shared_ptr<TokenStack> parent;

    TokenStack(int t, const std::shared_ptr<TokenStack>& p)
        : type(t), index(-1), name(), parent(p) {}
};

class TokenBuffer {
private:
    std::shared_ptr<TokenSegment> head;
    std::shared_ptr<TokenSegment> tail;
    int tail_index;
    std::shared_ptr<TokenStack> stack;

public:
    TokenBuffer();

    void writeStartObject();
    void writeEndObject();
    void writeFieldName(const std::string& field_name);
    void writeValueString(const std::string& value);
    void writeValueNumberInt(int value);
    void writeValueNumberFloat(double value);
    void writeValueBool(bool value);
    void writeValueNull();

    // ... other methods
};

TokenBuffer::TokenBuffer() {
    head = std::make_shared<TokenSegment>();
    tail = head;
    tail_index = 0;
    stack = std::make_shared<TokenStack>(0, nullptr);
}

void TokenBuffer::writeStartObject() {
    if (tail_index >= 16) {
        tail->next = std::make_shared<TokenSegment>();
        tail = tail->next;
        tail_index = 0;
    }

    tail->data[tail_index++] = TokenType::START_OBJECT;

    auto new_stack = std::make_shared<TokenStack>(2, stack);
    stack = new_stack;
}

void TokenBuffer::writeEndObject() {
    if (tail_index >= 16) {
        tail->next = std::make_shared<TokenSegment>();
        tail = tail->next;
        tail_index = 0;
    }

    tail->data[tail_index++] = TokenType::END_OBJECT;

    if (stack->parent) {
        stack = stack->parent;
    }
}

void TokenBuffer::writeFieldName(const std::string& field_name) {
    if (tail_index >= 16) {
        tail->next = std::make_shared<TokenSegment>();
        tail = tail->next;
        tail_index = 0;
    }

    tail->data[tail_index++] = TokenType::FIELD_NAME;
    tail->data[tail_index++] = field_name;

    if (stack->type == 2 && stack->name.empty()) {
        stack->name = field_name;
    }
}

void TokenBuffer::writeValueString(const std::string& value) {
    if (tail_index >= 16) {
        tail->next = std::make_shared<TokenSegment>();
        tail = tail->next;
        tail_index = 0;
    }

    tail->data[tail_index++] = TokenType::VALUE_STRING;
    tail->data[tail_index++] = value;
}

void TokenBuffer::writeValueNumberInt(int value) {
    if (tail_index >= 16) {
        tail->next = std::make_shared<TokenSegment>();
        tail = tail->next;
        tail_index = 0;
        }
    tail->data[tail_index++] = TokenType::VALUE_NUMBER_INT;
    tail->data[tail_index++] = value;
}

void TokenBuffer::writeValueNumberFloat(double value) {
if (tail_index >= 16) {
tail->next = std::make_shared<TokenSegment>();
tail = tail->next;
tail_index = 0;
}
tail->data[tail_index++] = TokenType::VALUE_NUMBER_FLOAT;
tail->data[tail_index++] = value;
}

void TokenBuffer::writeValueBool(bool value) {
if (tail_index >= 16) {
tail->next = std::make_shared<TokenSegment>();
tail = tail->next;
tail_index = 0;
}
tail->data[tail_index++] = value ? TokenType::VALUE_TRUE : TokenType::VALUE_FALSE;
}

void TokenBuffer::writeValueNull() {
if (tail_index >= 16) {
tail->next = std::make_shared<TokenSegment>();
tail = tail->next;
tail_index = 0;
}
tail->data[tail_index++] = TokenType::VALUE_NULL;
}

int main() {
TokenBuffer buffer;
buffer.writeStartObject();
buffer.writeFieldName("name");
buffer.writeValueString("John Doe");
buffer.writeFieldName("age");
buffer.writeValueNumberInt(30);
buffer.writeFieldName("isStudent");
buffer.writeValueBool(false);
buffer.writeFieldName("courses");
buffer.writeStartArray();
buffer.writeStartObject();
buffer.writeFieldName("name");
buffer.writeValueString("Math");
buffer.writeEndObject();
buffer.writeStartObject();
buffer.writeFieldName("name");
buffer.writeValueString("Physics");
buffer.writeEndObject();
buffer.writeEndArray();
buffer.writeEndObject();

return 0;
}