#include <iostream>
#include <memory>
#include <string>

class AstNode {
public:
    virtual ~AstNode() = default;
};

class IfExpression : public AstNode {
public:
    IfExpression(
        std::shared_ptr<AstNode> condition,
        std::shared_ptr<AstNode> true_branch,
        std::shared_ptr<AstNode> false_branch
    ) :
        condition_(condition),
        true_branch_(true_branch),
        false_branch_(false_branch) {}

    std::shared_ptr<AstNode> getCondition() const {
        return condition_;
    }

    std::shared_ptr<AstNode> getTrueBranch() const {
        return true_branch_;
    }

    std::shared_ptr<AstNode> getFalseBranch() const {
        return false_branch_;
    }

    bool equals(const IfExpression &other) const {
        return *condition_ == *other.condition_ &&
               *true_branch_ == *other.true_branch_ &&
               *false_branch_ == *other.false_branch_;
    }

    std::string toString() const {
        return "IfExpression{" +
               "condition=" + std::to_string(reinterpret_cast<uintptr_t>(condition_.get())) +
               ", trueBranch=" + std::to_string(reinterpret_cast<uintptr_t>(true_branch_.get())) +
               ", falseBranch=" + std::to_string(reinterpret_cast<uintptr_t>(false_branch_.get())) +
               '}';
    }

private:
    std::shared_ptr<AstNode> condition_;
    std::shared_ptr<AstNode> true_branch_;
    std::shared_ptr<AstNode> false_branch_;
};

int main() {
    auto condition = std::make_shared<AstNode>();
    auto true_branch = std::make_shared<AstNode>();
    auto false_branch = std::make_shared<AstNode>();

    IfExpression if_expr(condition, true_branch, false_branch);

    std::cout << "Condition: " << if_expr.getCondition() << std::endl;
    std::cout << "True Branch: " << if_expr.getTrueBranch() << std::endl;
    std::cout << "False Branch: " << if_expr.getFalseBranch() << std::endl;

    IfExpression another_if_expr(condition, true_branch, false_branch);
    std::cout << "Equals: " << if_expr.equals(another_if_expr) << std::endl;

    std::cout << "ToString: " << if_expr.toString() << std::endl;

    return 0;
}
