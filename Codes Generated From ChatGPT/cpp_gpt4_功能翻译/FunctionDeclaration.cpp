#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <typeinfo>

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual bool equals(const AstNode& other) const = 0;
    virtual size_t hashCode() const = 0;
    virtual std::string toString() const = 0;
};

class FunctionDeclaration : public AstNode {
public:
    FunctionDeclaration(const std::string& name,
                        const std::vector<std::shared_ptr<AstNode>>& params,
                        const std::shared_ptr<AstNode>& body)
        : name(name), params(params), body(body) {}

    std::string getName() const {
        return name;
    }

    std::vector<std::shared_ptr<AstNode>> getParams() const {
        return params;
    }

    std::shared_ptr<AstNode> getBody() const {
        return body;
    }

    bool equals(const AstNode& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        const FunctionDeclaration& that = static_cast<const FunctionDeclaration&>(other);
        if (name != that.name) return false;
        if (params.size() != that.params.size()) return false;
        for (size_t i = 0; i < params.size(); i++) {
            if (!params[i]->equals(*that.params[i])) return false;
        }
        return body->equals(*that.body);
    }

    size_t hashCode() const override {
        size_t result = std::hash<std::string>()(name);
        for (const auto& param : params) {
            result = result * 31 + param->hashCode();
        }
        result = result * 31 + body->hashCode();
        return result;
    }

    std::string toString() const override {
        std::string result = "FunctionDeclaration{name='" + name + "', params=";
        for (size_t i = 0; i < params.size(); i++) {
            result += params[i]->toString();
            if (i < params.size() - 1) {
                result += ", ";
            }
        }
        result += ", body=" + body->toString() + "}";
        return result;
    }

private:
    std::string name;
    std::vector<std::shared_ptr<AstNode>> params;
    std::shared_ptr<AstNode> body;
};

// Example usage of the FunctionDeclaration class:
int main() {
    auto param1 = std::make_shared<FunctionDeclaration>("param1", std::vector<std::shared_ptr<AstNode>>{}, nullptr);
    auto param2 = std::make_shared<FunctionDeclaration>("param2", std::vector<std::shared_ptr<AstNode>>{}, nullptr);

    auto body = std::make_shared<FunctionDeclaration>("body", std::vector<std::shared_ptr<AstNode>>{}, nullptr);
    FunctionDeclaration functionDeclaration("testFunction", {param1, param2}, body);
    std::cout << functionDeclaration.toString() << std::endl;

    return 0;
}
