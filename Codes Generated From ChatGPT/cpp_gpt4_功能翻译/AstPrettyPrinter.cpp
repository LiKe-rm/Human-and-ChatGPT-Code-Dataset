#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <memory>

class MindcodeException : public std::exception {
public:
    MindcodeException(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class AstNode;
class Ref;
class IfExpression;
class HeapAccess;
class Control;
class WhileExpression;
class VarRef;
class Assignment;
class UnaryOp;
class StringLiteral;
class NumericLiteral;
class NullLiteral;
class NoOp;
class FunctionCall;
class BooleanLiteral;
class BinaryOp;
class Seq;
class PropertyAccess;
class CaseExpression;
class FunctionDeclaration;
class StackAllocation;

class AstVisitor {
public:
    virtual ~AstVisitor() = default;

    virtual void visit(std::shared_ptr<Ref> node) = 0;
    virtual void visit(std::shared_ptr<IfExpression> node) = 0;
    virtual void visit(std::shared_ptr<HeapAccess> node) = 0;
    virtual void visit(std::shared_ptr<Control> node) = 0;
    virtual void visit(std::shared_ptr<WhileExpression> node) = 0;
    virtual void visit(std::shared_ptr<VarRef> node) = 0;
    virtual void visit(std::shared_ptr<Assignment> node) = 0;
    virtual void visit(std::shared_ptr<UnaryOp> node) = 0;
    virtual void visit(std::shared_ptr<StringLiteral> node) = 0;
    virtual void visit(std::shared_ptr<NumericLiteral> node) = 0;
    virtual void visit(std::shared_ptr<NullLiteral> node) = 0;
    virtual void visit(std::shared_ptr<NoOp> node) = 0;
    virtual void visit(std::shared_ptr<FunctionCall> node) = 0;
    virtual void visit(std::shared_ptr<BooleanLiteral> node) = 0;
    virtual void visit(std::shared_ptr<BinaryOp> node) = 0;
    virtual void visit(std::shared_ptr<Seq> node) = 0;
    virtual void visit(std::shared_ptr<PropertyAccess> node) = 0;
    virtual void visit(std::shared_ptr<CaseExpression> node) = 0;
    virtual void visit(std::shared_ptr<FunctionDeclaration> node) = 0;
    virtual void visit(std::shared_ptr<StackAllocation> node) = 0;
};

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual void accept(AstVisitor& visitor) = 0;
};

// Declare classes for each AST node type here.
// ...

class AstPrettyPrinter : public AstVisitor {
public:
    std::string prettyPrint(std::shared_ptr<AstNode> node) {
        node->accept(*this);
        return buffer_;
    }

    void visit(std::shared_ptr<Ref> node) override {
        buffer_ += "@";
        buffer_ += node->getName();
    }

    // Implement other visit methods for each AST node type here.
    // ...

private:
    std::string buffer_;
};

// Implement classes for each AST node type here.
// ...
