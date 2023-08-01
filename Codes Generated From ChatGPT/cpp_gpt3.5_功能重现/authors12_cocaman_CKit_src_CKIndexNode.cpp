#include <iostream>
#include <map>

class CKIndexNode : public CKDataNode {
public:
    CKIndexNode() : reference(nullptr) {}
    CKIndexNode(const CKIndexNode& other) : CKDataNode(other), reference(other.reference) {}
    CKIndexNode& operator=(const CKIndexNode& other) {
        if (this != &other) {
            CKDataNode::operator=(other);
            reference = other.reference;
        }
        return *this;
    }
    ~CKIndexNode() {}

    CKDataNode* getReference() const {
        return reference;
    }

    CKDataNode* getReferenceAtPath(const std::string& path) const {
        std::vector<std::string> keys = split(path, "/");
        CKDataNode* currentNode = const_cast<CKIndexNode*>(this);
        for (const auto& key : keys) {
            if (!currentNode->hasKey(key)) {
                return nullptr;
            }
            currentNode = dynamic_cast<CKIndexNode*>(currentNode->getValue(key));
        }
        return currentNode->getReference();
    }

    void putReference(CKDataNode* node) {
        reference = node;
    }

    void putReferenceAtPath(const std::string& path, CKDataNode* node) {
        std::vector<std::string> keys = split(path, "/");
        CKIndexNode* currentNode = this;
        for (const auto& key : keys) {
            if (!currentNode->hasKey(key)) {
                currentNode->putValue(key, new CKIndexNode());
            }
            currentNode = dynamic_cast<CKIndexNode*>(currentNode->getValue(key));
        }
        currentNode->putReference(node);
    }

    CKIndexNode* newNodeByShallowCopy() const {
        return new CKIndexNode(*this);
    }

    CKIndexNode* newNodeByDeepCopy() const {
        CKIndexNode* newNode = new CKIndexNode();
        for (const auto& key : keys()) {
            newNode->putValue(key, getValue(key)->newNodeByDeepCopy());
        }
        newNode->putReference(reference->newNodeByDeepCopy());
        return newNode;
    }

    bool operator==(const CKIndexNode& other) const {
        if (reference != other.reference) {
            return false;
        }
        return CKDataNode::operator==(other);
    }

    bool operator!=(const CKIndexNode& other) const {
        return !(*this == other);
    }

    std::string toString() const {
        std::string result = "{";
        for (const auto& key : keys()) {
            result += key + ": " + getValue(key)->toString() + ", ";
        }
        result += "reference: ";
        if (reference) {
            result += reference->toString();
        } else {
            result += "null";
        }
        result += "}";
        return result;
    }

private:
    CKDataNode* reference;
};
