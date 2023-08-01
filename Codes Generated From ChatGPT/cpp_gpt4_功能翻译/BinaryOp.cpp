#include <iostream>
#include <memory>
#include <string>
#include <functional>

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual bool equals(const AstNode &other) const = 0;
    virtual std::size_t hashCode() const = 0;
    virtual std::string toString() const = 0;
};

class BinaryOp : public AstNode {
private:
    std::shared_ptr<AstNode> left;
    std::string op;
    std::shared_ptr<AstNode> right;

public:
    BinaryOp(std::shared_ptr<AstNode> left, const std::string &op, std::shared_ptr<AstNode> right)
        : left(left), op(op), right(right) {}

    std::shared_ptr<AstNode> getLeft() const {
        return left;
    }

    std::string getOp() const {
        return op;
    }

    std::shared_ptr<AstNode> getRight() const {
        return right;
    }

    bool equals(const AstNode &other) const override {
        if (const auto binaryOp = dynamic_cast<const BinaryOp*>(&other)) {
            return *left == *binaryOp->left &&
                   op == binaryOp->op &&
                   *right == *binaryOp->right;
        }
        return false;
    }

    std::size_t hashCode() const override {
        std::hash<std::string> stringHasher;
        std::size_t result = 17;
        result = 31 * result + left->hashCode();
        result = 31 * result + stringHasher(op);
        result = 31 * result + right->hashCode();
        return result;
    }

    std::string toString() const override {
        return "BinaryOp{" +
               "left=" + left->toString() +
               ", op='" + op + '\'' +
               ", right=" + right->toString() +
               '}';
    }
};

bool operator==(const AstNode &lhs, const AstNode &rhs) {
    return lhs.equals(rhs);
}

bool operator!=(const AstNode &lhs, const AstNode &rhs) {
    return !(lhs == rhs);
}

// Example usage of the BinaryOp class
int main() {
    std::shared_ptr<AstNode> left = std::make_shared<BinaryOp>(nullptr, "+", nullptr); // Replace with proper nodes
    std::shared_ptr<AstNode> right = std::make_shared<BinaryOp>(nullptr, "*", nullptr); // Replace with proper nodes

    BinaryOp binaryOp1(left, "-", right);
    BinaryOp binaryOp2(left, "-", right);

    std::cout << "BinaryOp 1: " << binaryOp1.toString() << std::endl;
    std::cout << "BinaryOp 2: " << binaryOp2.toString() << std::endl;
    std::cout << "BinaryOp 1 equals BinaryOp 2: " << (binaryOp1 == binaryOp2) << std::endl;
    std::cout << "BinaryOp 1 hash code: " << binaryOp1.hashCode() << std::endl;
    std::cout << "BinaryOp 2 hash code: " << binaryOp2.hashCode() << std::endl;

    return 0;
}
