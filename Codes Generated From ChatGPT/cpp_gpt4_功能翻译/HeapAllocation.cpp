#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>

class ParsingException : public std::runtime_error {
public:
    explicit ParsingException(const std::string &message) : std::runtime_error(message) {}
};

class InvalidHeapAllocationException : public std::runtime_error {
public:
    explicit InvalidHeapAllocationException(const std::string &message) : std::runtime_error(message) {}
};

class AstNode {
public:
    virtual ~AstNode() = default;

    virtual bool equals(const AstNode &other) const = 0;

    virtual size_t hashCode() const = 0;

    virtual std::string toString() const = 0;
};

class NumericLiteral : public AstNode {
public:
    explicit NumericLiteral(const std::string &literal) : literal(literal) {}

    std::string getLiteral() const {
        return literal;
    }

    bool equals(const AstNode &other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        const NumericLiteral &numericLiteral = static_cast<const NumericLiteral &>(other);
        return literal == numericLiteral.literal;
    }

    size_t hashCode() const override {
        return std::hash<std::string>()(literal);
    }

    std::string toString() const override {
        return "NumericLiteral{literal='" + literal + "'}";
    }

private:
    std::string literal;
};

class Range {
public:
    virtual ~Range() = default;

    virtual std::shared_ptr<AstNode> getFirstValue() const = 0;

    virtual std::shared_ptr<AstNode> getLastValue() const = 0;

    virtual std::string toString() const = 0;
};

class ExclusiveRange : public Range {
    // Implement ExclusiveRange class here
};

class InclusiveRange : public Range {
    // Implement InclusiveRange class here
};

class HeapAllocation {
public:
    HeapAllocation(const std::string &name, const std::shared_ptr<Range> &range) {
        if (!(dynamic_cast<NumericLiteral *>(range->getFirstValue().get())) ||
            !(dynamic_cast<NumericLiteral *>(range->getLastValue().get()))) {
            throw InvalidHeapAllocationException(
                "Heap declarations must use numeric literals; received " + range->toString());
        }

        int candidate = std::stoi(static_cast<NumericLiteral *>(range->getLastValue().get())->getLiteral());
        if (dynamic_cast<ExclusiveRange *>(range.get())) {
            candidate -= 1;
        } else if (dynamic_cast<InclusiveRange *>(range.get())) {
            candidate += 0;
        } else {
            throw ParsingException("Received unexpected type of Range: " + range->toString());
        }

        this->name = name;
        this->first = std::stoi(static_cast<NumericLiteral *>(range->getFirstValue().get())->getLiteral());
        this->last = candidate;
    }

    HeapAllocation(const std::string &name, int first, int last) : name(name), first(first), last(last) {}

    std::string getName() const {
        return name;
    }

    int getFirst() const {
        return first;
    }

    int size() const {
        return (last - first) + 1;
    }

    std::shared_ptr<AstNode> addressOf(int location) const {
        return std::make_shared<NumericLiteral>(std::to_string(getFirst() + location));
    }

    bool equals(const HeapAllocation &other) const {
if (this == &other) return true;
return first == other.first && last == other.last && name == other.name;
}
size_t hashCode() const {
    return std::hash<std::string>()(name) ^ std::hash<int>()(first) ^ std::hash<int>()(last);
}

std::string toString() const {
    return "HeapAllocation{name='" + name + "', first=" + std::to_string(first) + ", last=" + std::to_string(last) + "}";
}
private:
std::string name;
int first;
int last;
};

int main() {
try {
std::shared_ptr<AstNode> first = std::make_shared<NumericLiteral>("0");
std::shared_ptr<AstNode> last = std::make_shared<NumericLiteral>("9");
std::shared_ptr<Range> range = std::make_shared<InclusiveRange>(first, last);
HeapAllocation heapAllocation("myHeap", range);
    std::cout << "HeapAllocation: " << heapAllocation.toString() << std::endl;
    std::cout << "Size: " << heapAllocation.size() << std::endl;
    std::cout << "Address at 3: " << heapAllocation.addressOf(3)->toString() << std::endl;

} catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
}

return 0;
}