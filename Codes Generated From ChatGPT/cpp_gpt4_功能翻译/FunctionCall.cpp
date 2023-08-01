#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual bool equals(const AstNode& other) const = 0;
    virtual size_t hashCode() const = 0;
    virtual std::string toString() const = 0;
};

class FunctionCall : public AstNode {
public:
    FunctionCall(const std::string& functionName, const std::vector<std::shared_ptr<AstNode>>& params)
        : functionName(functionName), params(params) {}

    FunctionCall(const std::string& functionName, const std::initializer_list<std::shared_ptr<AstNode>>& params)
        : functionName(functionName), params(params) {}

    std::string getFunctionName() const {
        return functionName;
    }

    std::vector<std::shared_ptr<AstNode>> getParams() const {
        return params;
    }

    bool equals(const AstNode& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        const FunctionCall& functionCall = static_cast<const FunctionCall&>(other);
        if (functionName != functionCall.functionName) return false;
        if (params.size() != functionCall.params.size()) return false;
        for (size_t i = 0; i < params.size(); i++) {
            if (!params[i]->equals(*functionCall.params[i])) return false;
        }
        return true;
    }

    size_t hashCode() const override {
        size_t result = std::hash<std::string>()(functionName);
        for (const auto& param : params) {
            result = result * 31 + param->hashCode();
        }
        return result;
    }

    std::string toString() const override {
        std::string result = "FunctionCall{functionName='" + functionName + "', params=";
        for (size_t i = 0; i < params.size(); i++) {
            result += params[i]->toString();
            if (i < params.size() - 1) {
                result += ", ";
            }
        }
        result += "}";
        return result;
    }

private:
    std::string functionName;
    std::vector<std::shared_ptr<AstNode>> params;
};

// Example usage of the FunctionCall class:
int main() {
    auto param1 = std::make_shared<FunctionCall>("param1");
    auto param2 = std::make_shared<FunctionCall>("param2");

    FunctionCall functionCall("testFunction", {param1, param2});
    std::cout << functionCall.toString() << std::endl;

    return 0;
}
