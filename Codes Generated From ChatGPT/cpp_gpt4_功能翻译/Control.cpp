#include <string>
#include <vector>
#include <memory>
#include <iostream>

class AstNode {
public:
    virtual ~AstNode() = default;
};

class Control : public AstNode {
public:
    Control(std::shared_ptr<AstNode> target, const std::string& property, const std::vector<std::shared_ptr<AstNode>>& params)
        : target(target), property(property), params(params) {}

    std::shared_ptr<AstNode> getTarget() const {
        return target;
    }

    std::string getProperty() const {
        return property;
    }

    std::vector<std::shared_ptr<AstNode>> getParams() const {
        return params;
    }

    bool operator==(const Control& other) const {
        return *target == *(other.target) &&
               property == other.property &&
               params == other.params;
    }

    bool operator!=(const Control& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const Control& control) {
        os << "Control{target=" << *(control.target) << ", property='" << control.property << "', params=";
        for (const auto& param : control.params) {
            os << *param << ",";
        }
        os << "}";
        return os;
    }

private:
    std::shared_ptr<AstNode> target;
    std::string property;
    std::vector<std::shared_ptr<AstNode>> params;
};
