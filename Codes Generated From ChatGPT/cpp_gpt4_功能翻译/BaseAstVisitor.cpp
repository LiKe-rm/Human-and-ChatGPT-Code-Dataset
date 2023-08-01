#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>

class AstNode;
class BinaryOp;
class BooleanLiteral;
class CaseExpression;
class Control;
class FunctionCall;
class FunctionDeclaration;
class HeapAccess;
class IfExpression;
class NoOp;
class NullLiteral;
class NumericLiteral;
class Ref;
class PropertyAccess;
class Seq;
class StackAllocation;
class StringLiteral;
class UnaryOp;
class Assignment;
class VarRef;
class WhileExpression;

template<typename T>
class BaseAstVisitor {
public:
    virtual T visit(std::shared_ptr<AstNode> node) {
        if (auto binaryOpNode = std::dynamic_pointer_cast<BinaryOp>(node)) {
            return visitBinaryOp(binaryOpNode);
        } else if (auto booleanLiteralNode = std::dynamic_pointer_cast<BooleanLiteral>(node)) {
            return visitBooleanLiteral(booleanLiteralNode);
        } else if (auto caseExpressionNode = std::dynamic_pointer_cast<CaseExpression>(node)) {
            return visitCaseExpression(caseExpressionNode);
        } else if (auto controlNode = std::dynamic_pointer_cast<Control>(node)) {
            return visitControl(controlNode);
        } else if (auto functionCallNode = std::dynamic_pointer_cast<FunctionCall>(node)) {
            return visitFunctionCall(functionCallNode);
        } else if (auto functionDeclarationNode = std::dynamic_pointer_cast<FunctionDeclaration>(node)) {
            return visitFunctionDeclaration(functionDeclarationNode);
        } else if (auto heapAccessNode = std::dynamic_pointer_cast<HeapAccess>(node)) {
            return visitHeapAccess(heapAccessNode);
        } else if (auto ifExpressionNode = std::dynamic_pointer_cast<IfExpression>(node)) {
            return visitIfExpression(ifExpressionNode);
        } else if (auto noOpNode = std::dynamic_pointer_cast<NoOp>(node)) {
            return visitNoOp(noOpNode);
        } else if (auto nullLiteralNode = std::dynamic_pointer_cast<NullLiteral>(node)) {
            return visitNullLiteral(nullLiteralNode);
        } else if (auto numericLiteralNode = std::dynamic_pointer_cast<NumericLiteral>(node)) {
            return visitNumericLiteral(numericLiteralNode);
        } else if (auto refNode = std::dynamic_pointer_cast<Ref>(node)) {
            return visitRef(refNode);
        } else if (auto propertyAccessNode = std::dynamic_pointer_cast<PropertyAccess>(node)) {
            return visitPropertyAccess(propertyAccessNode);
        } else if (auto seqNode = std::dynamic_pointer_cast<Seq>(node)) {
            return visitSeq(seqNode);
        } else if (auto stackAllocationNode = std::dynamic_pointer_cast<StackAllocation>(node)) {
            return visitStackAllocation(stackAllocationNode);
        } else if (auto stringLiteralNode = std::dynamic_pointer_cast<StringLiteral>(node)) {
            return visitStringLiteral(stringLiteralNode);
        } else if (auto unaryOpNode = std::dynamic_pointer_cast<UnaryOp>(node)) {
            return visitUnaryOp(unaryOpNode);
        } else if (auto assignmentNode = std::dynamic_pointer_cast<Assignment>(node)) {
            return visitAssignment(assignmentNode);
        } else if (auto varRefNode = std::dynamic_pointer_cast<VarRef>(node)) {
            return visitVarRef(varRefNode);
        } else if (auto whileExpressionNode = std::dynamic_pointer_cast<WhileExpression>(node)) {
            return visitWhileStatement(whileExpressionNode);
        } else {
            throw std::runtime_error("Unrecognized node type " + std::stringtypeid(*node).name() + ": " + node->toString());
        }
    }
    virtual T visitBinaryOp(std::shared_ptr<BinaryOp> node) = 0;
    virtual T visitBooleanLiteral(std::shared_ptr<BooleanLiteral> node) = 0;
    virtual T visitCaseExpression(std::shared_ptr<CaseExpression> node) = 0;
    virtual T visitControl(std::shared_ptr<Control> node) = 0;
    virtual T visitFunctionCall(std::shared_ptr<FunctionCall> node) = 0;
    virtual T visitFunctionDeclaration(std::shared_ptr<FunctionDeclaration> node) = 0;
    virtual T visitHeapAccess(std::shared_ptr<HeapAccess> node) = 0;
    virtual T visitIfExpression(std::shared_ptr<IfExpression> node) = 0;
    virtual T visitNoOp(std::shared_ptr<NoOp> node) = 0;
    virtual T visitNullLiteral(std::shared_ptr<NullLiteral> node) = 0;
    virtual T visitNumericLiteral(std::shared_ptr<NumericLiteral> node) = 0;
    virtual T visitRef(std::shared_ptr<Ref> node) = 0;
    virtual T visitPropertyAccess(std::shared_ptr<PropertyAccess> node) = 0;
    virtual T visitSeq(std::shared_ptr<Seq> node) = 0;
    virtual T visitStackAllocation(std::shared_ptr<StackAllocation> node) = 0;
    virtual T visitStringLiteral(std::shared_ptr<StringLiteral> node) = 0;
    virtual T visitUnaryOp(std::shared_ptr<UnaryOp> node) = 0;
    virtual T visitAssignment(std::shared_ptr<Assignment> node) = 0;
    virtual T visitVarRef(std::shared_ptr<VarRef> node) = 0;
    virtual T visitWhileStatement(std::shared_ptr<WhileExpression> node) = 0;
};

// The following are example class declarations for each AST node type
class AstNode {
public:
virtual std::string toString() const = 0;
};

class BinaryOp : public AstNode {
public:
std::string toString() const override {
// Implement the toString method
return "";
}
};

// Add similar class declarations for the remaining AST node types...

int main() {
// Example usage of the BaseAstVisitor with an example visitor implementation
class ExampleVisitor : public BaseAstVisitor<int> {
public:
int visitBinaryOp(std::shared_ptr<BinaryOp> node) override {
// Implement the visitor's behavior for BinaryOp nodes
return 0;
}
    // Add similar visit* methods for the remaining AST node types...
};

std::shared_ptr<AstNode> astRoot = std::make_shared<BinaryOp>();  // Just an example
ExampleVisitor visitor;
int result = visitor.visit(astRoot);

return 0;
}