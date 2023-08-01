#include <iostream>
#include <vector>
#include <algorithm>

class NetworkID {
    public:
    NetworkID(): id_(0) {}

    NetworkID(int id): id_(id) {}

    void SetID(int id) { id_ = id; }

    int GetID() const { return id_; }

    void SetPlayerID(int id) { player_id_ = id; }

    int GetPlayerID() const { return player_id_; }

    void SetParent(NetworkID* parent) { parent_ = parent; }

    NetworkID* GetParent() const { return parent_; }

    void AddChild(NetworkID* child) { children_.push_back(child); }

    std::vector<NetworkID*> GetChildren() const { return children_; }

    private:
    int id_;
    int player_id_;
    NetworkID* parent_;
    std::vector<NetworkID*> children_;
};

class AVLTree {
    public:
    AVLTree(): root_(nullptr) {}

    ~AVLTree() { DeleteTree(root_); }

    void Insert(NetworkID* id) { root_ = Insert(root_, id); }

    void Delete(int id) { root_ = Delete(root_, id); }

    NetworkID* Search(int id) const { return Search(root_, id); }

    NetworkID* GetMin() const { return GetMin(root_); }

    NetworkID* GetMax() const { return GetMax(root_); }

    private:
    struct Node {
        NetworkID* id;
        int height;
        Node* left;
        Node* right;
    };

    Node* root_;

    int Height(Node* node) const {
        if (node == nullptr) {
            return -1;
        } else {
            return node->height;
        }
    }

    int BalanceFactor(Node* node) const {
        if (node == nullptr) {
            return 0;
        } else {
            return Height(node->left) - Height(node->right);
        }
    }

    Node* RotateLeft(Node* node) {
        Node* new_root = node->right;
        node->right = new_root->left;
        new_root->left = node;
        node->height = std::max(Height(node->left), Height(node->right)) + 1;
        new_root->height = std::max(Height(new_root->left), Height(new_root->right)) + 1;
        return new_root;
    }

    Node* RotateRight(Node* node) {
        Node* new_root = node->left;
        node->left = new_root->right;
        new_root->right = node;
        node->height = std::max(Height(node->left), Height(node->right)) + 1;
        new_root->height = std::max(Height(new_root->left), Height(new_root->right)) + 1;
        return new_root;
    }

    Node* RotateLeftRight(Node* node) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }

    Node* RotateRightLeft(Node* node) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    Node* Insert(Node* node, NetworkID* id) {
        if (node == nullptr) {
            node = new Node;
            node->id = id;
            node->height = 0;
            node->left = nullptr;
            node->right = nullptr;
        } else if (id->GetID() < node->id) {
            node->left = Insert(node->left, id);
            if (BalanceFactor(node) == 2) {
                if (id->GetID() < node->left->id->GetID()) {
                    node = RotateRight(node);
                } else {
                    node = RotateLeftRight(node);
                }
            }
        } else if (id->GetID() > node->id->GetID()) {
            node->right = Insert(node->right, id);
            if (BalanceFactor(node) == -2) {
                if (id->GetID() > node->right->id->GetID()) {
                    node = RotateLeft(node);
                } else {
                    node = RotateRightLeft(node);
                }
            }
        }
        node->height = std::max(Height(node->left), Height(node->right)) + 1;
        return node;
    }

    Node* Delete(Node* node, int id) {
        if (node == nullptr) {
            return nullptr;
        } else if (id < node->id->GetID()) {
            node->left = Delete(node->left, id);
        } else if (id > node->id->GetID()) {
            node->right = Delete(node->right, id);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node->id;
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp->id;
                delete temp;
            } else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp->id;
                delete temp;
            } else {
                Node* temp = GetMin(node->right);
                node->id->SetID(temp->id->GetID());
                node->right = Delete(node->right, temp->id->GetID());
            }
        }
        if (node == nullptr) {
            return node;
        }
        node->height = std::max(Height(node->left), Height(node->right)) + 1;
        if (BalanceFactor(node) == 2) {
            if (BalanceFactor(node->left) >= 0) {
                node = RotateRight(node);
            } else {
                node = RotateLeftRight(node);
            }
        } else if (BalanceFactor(node) == -2) {
            if (BalanceFactor(node->right) <= 0) {
                node = RotateLeft(node);
            } else {
                node = RotateRightLeft(node);
            }
        }
        return node;
    }

    NetworkID* Search(Node* node, int id) const {
        if (node == nullptr) {
            return nullptr;
        } else if (id == node->id->GetID()) {
            return node->id;
        } else if (id < node->id->GetID()) {
            return Search(node->left, id);
        } else {
            return Search(node->right, id);
        }
    }

    NetworkID* GetMin(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        } else if (node->left == nullptr) {
            return node->id;
        } else {
            return GetMin(node->left);
        }
    }

    NetworkID* GetMax(Node* node) const {
        if (node == nullptr) {
            return nullptr;
        } else if (node->right == nullptr) {
            return node->id;
        } else {
            return GetMax(node->right);
        }
    }

    void DeleteTree(Node* node) {
        if (node != nullptr) {
            DeleteTree(node->left);
            DeleteTree(node->right);
            delete node->id;
            delete node;
        }
    }
};

class NetworkIDGenerator {
    public:
    NetworkIDGenerator(): next_id_(1) {}
    ~NetworkIDGenerator() {
        for (auto& entry : network_ids_) {
            delete entry.second;
        }
    }

    NetworkID* Allocate() {
        int id = next_id_++;
        NetworkID* network_id = new NetworkID(id);
        network_ids_[id] = network_id;
        return network_id;
    }

    void Deallocate(NetworkID* network_id) {
        int id = network_id->GetID();
        auto it = network_ids_.find(id);
        if (it != network_ids_.end()) {
            network_ids_.erase(it);
            delete network_id;
        }
    }

    NetworkID* Find(int id) const {
        auto it = network_ids_.find(id);
        if (it != network_ids_.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    NetworkID* GetRoot() const { return avl_tree_.GetMin(); }

    void SetRoot(NetworkID* network_id) {
        avl_tree_.Delete(network_id->GetID());
        avl_tree_.Insert(network_id);
    }
    private:
    int next_id_;
    std::unordered_map<int, NetworkID*> network_ids_;
    AVLTree avl_tree_;
};

int main() {
    NetworkIDGenerator generator;
    // Allocate some NetworkIDs.
    NetworkID* network_id1 = generator.Allocate();
    NetworkID* network_id2 = generator.Allocate();
    NetworkID* network_id3 = generator.Allocate();
    network_id1->SetPlayerID(1);
    network_id2->SetPlayerID(2);
    network_id3->SetPlayerID(3);

    // Set network_id2 as the parent of network_id1.
    network_id1->SetParent(network_id2);
    network_id2->AddChild(network_id1);

    // Set network_id2 as the root of the AVL tree.
    generator.SetRoot(network_id2);

    // Delete network_id1 and reallocate it.
    generator.Deallocate(network_id1);
    network_id1 = generator.Allocate();

    // Search for network_id2 and print its children.
    NetworkID* search_result = generator.Find(network_id2->GetID());
    if (search_result != nullptr) {
        std::cout << "NetworkID " << search_result->GetID() << " has children: ";
        for (auto child : search_result->GetChildren()) {
            std::cout << child->GetID() << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "NetworkID not found." << std::endl;
    }

    // Print the root of the AVL tree.
    NetworkID* root = generator.GetRoot();
    std::cout << "Root of AVL tree: " << root->GetID() << std::endl;

    return 0;
}