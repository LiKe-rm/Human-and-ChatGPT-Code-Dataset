#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual bool equals(const AstNode &other) const = 0;
    virtual std::size_t hashCode() const = 0;
    virtual std::string toString() const = 0;
};

class CaseAlternative {
    // Implement your CaseAlternative class here
};

class CaseExpression : public AstNode {
private:
    std::shared_ptr<AstNode> condition;
    std::vector<std::shared_ptr<CaseAlternative>> alternatives;
    std::shared_ptr<AstNode> elseBranch;

public:
    CaseExpression(std::shared_ptr<AstNode> condition,
                   std::vector<std::shared_ptr<CaseAlternative>> alternatives,
                   std::shared_ptr<AstNode> elseBranch)
        : condition(condition), alternatives(std::move(alternatives)), elseBranch(elseBranch) {}

    std::shared_ptr<AstNode> getCondition() const {
        return condition;
    }

    std::vector<std::shared_ptr<CaseAlternative>> getAlternatives() const {
        return alternatives;
    }

    std::shared_ptr<AstNode> getElseBranch() const {
        return elseBranch;
    }

    bool equals(const AstNode &other) const override {
        if (const auto caseExpression = dynamic_cast<const CaseExpression*>(&other)) {
            return *condition == *caseExpression->condition &&
                   alternatives == caseExpression->alternatives &&
                   *elseBranch == *caseExpression->elseBranch;
        }
        return false;
    }

    std::size_t hashCode() const override {
        std::hash<std::string> stringHasher;
        std::size_t result = 17;
        result = 31 * result + condition->hashCode();
        // Assuming CaseAlternative has a hashCode method
        for (const auto &alternative : alternatives) {
            result = 31 * result + alternative->hashCode();
        }
        result = 31 * result + elseBranch->hashCode();
        return result;
    }

    std::string toString() const override {
        std::string altStr = "alternatives=[";
        for (size_t i = 0; i < alternatives.size(); ++i) {
            altStr += alternatives[i]->toString();
            if (i < alternatives.size() - 1) {
                altStr += ", ";
            }
        }
        altStr += "]";

        return "CaseExpression{" +
               "condition=" + condition->toString() +
               ", " + altStr +
               ", elseBranch=" + elseBranch->toString() +
               '}';
    }
};

bool operator==(const AstNode &lhs, const AstNode &rhs) {
    return lhs.equals(rhs);
}

bool operator!=(const AstNode &lhs, const AstNode &rhs) {
    return !(lhs == rhs);
}

// Example usage of the CaseExpression class
int main() {
    std::shared_ptr<AstNode> condition = std::make_shared<CaseExpression>(nullptr, std::vector<std::shared_ptr<CaseAlternative>>{}, nullptr); // Replace with proper nodes
    std::vector<std::shared_ptr<CaseAlternative>> alternatives; // Populate with proper CaseAlternative instances
    std::shared_ptr<AstNode> elseBranch = std::make_shared<CaseExpression>(nullptr, std::vector<std::shared_ptr<CaseAlternative>>{}, nullptr); // Replace with proper nodes

    CaseExpression caseExpression1(condition, alternatives, elseBranch);
    CaseExpression caseExpression2(condition, alternatives, elseBranch);

    std::cout << "CaseExpression 1: " << caseExpression1.toString() << std::endl;
    std::cout << "CaseExpression 2: " << caseExpression2.toString() << std::endl;
    std::cout << "CaseExpression 1 equals CaseExpression 2: " << (caseExpression1 == caseExpression2) << std::endl;
    std::cout << "CaseExpression 1 hash code: " << caseExpression1.hashCode() << std::endl;
    std::cout << "CaseExpression 2 hash code: " << caseExpression2.hashCode() << std::endl;

    return 0;
}
