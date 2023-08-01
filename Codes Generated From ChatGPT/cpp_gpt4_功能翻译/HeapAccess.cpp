#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>
#include <unordered_set>
#include <stdexcept>

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual bool equals(const AstNode& other) const = 0;
    virtual size_t hashCode() const = 0;
    virtual std::string toString() const = 0;
};

class ParsingException : public std::runtime_error {
public:
    explicit ParsingException(const std::string& message) : std::runtime_error(message) {}
};

class HeapAccess : public AstNode {
public:
    HeapAccess(const std::string& cellName, const std::shared_ptr<AstNode>& address)
        : cellName(cellName), address(address) {
        if (RESERVED_KEYWORDS.find(cellName) != RESERVED_KEYWORDS.end()) {
            throw ParsingException(cellName + " is a reserved keyword, please use a different word");
        }
    }

    std::string getCellName() const {
        return cellName;
    }

    std::shared_ptr<AstNode> getAddress() const {
        return address;
    }

    bool equals(const AstNode& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        const HeapAccess& heapAccess = static_cast<const HeapAccess&>(other);
        return cellName == heapAccess.cellName && address->equals(*heapAccess.address);
    }

    size_t hashCode() const override {
        return std::hash<std::string>()(cellName) * 31 + address->hashCode();
    }

    std::string toString() const override {
        return "HeapAccess{cellName='" + cellName + "', address='" + address->toString() + "'}";
    }

private:
    const std::unordered_set<std::string> RESERVED_KEYWORDS{"if", "else", "while", "return"};
    std::string cellName;
    std::shared_ptr<AstNode> address;
};

// Example usage of the HeapAccess class:
int main() {
    // Dummy AstNode subclass for demonstration purposes only
    class DummyNode : public AstNode {
    public:
        bool equals(const AstNode& other) const override {
            return typeid(*this) == typeid(other);
        }
        size_t hashCode() const override {
            return 0;
        }
        std::string toString() const override {
            return "DummyNode";
        }
    };

    auto address = std::make_shared<DummyNode>();
    HeapAccess heapAccess("exampleCell", address);
    std::cout << heapAccess.toString() << std::endl;

    return 0;
}
