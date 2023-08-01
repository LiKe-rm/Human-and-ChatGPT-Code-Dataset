#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    TreeNode *root;

    Tree() : root(nullptr) {}

    bool isEmpty() {
        return root == nullptr;
    }

    void insert(int val) {
        root = insertHelper(root, val);
    }

    bool search(int val) {
        return searchHelper(root, val);
    }

    void remove(int val) {
        root = removeHelper(root, val);
    }

    void inOrderTraversal() {
        inOrderHelper(root);
        std::cout << std::endl;
    }

    void preOrderTraversal() {
        preOrderHelper(root);
        std::cout << std::endl;
    }

    void postOrderTraversal() {
        postOrderHelper(root);
        std::cout << std::endl;
    }

    void levelOrderTraversal() {
        levelOrderHelper(root);
    }

private:
    TreeNode *insertHelper(TreeNode *node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else {
            node->right = insertHelper(node->right, val);
        }

        return node;
    }

    bool searchHelper(TreeNode *node, int val) {
        if (node == nullptr) {
            return false;
        }

        if (val == node->val) {
            return true;
        } else if (val < node->val) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }

    TreeNode *removeHelper(TreeNode *node, int val) {
        if (node == nullptr) {
            return node;
        }

        if (val < node->val) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = removeHelper(node->right, val);
        } else {
            if (node->left == nullptr) {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }

            node->val = minValue(node->right);
            node->right = removeHelper(node->right, node->val);
        }

        return node;
    }

    int minValue(TreeNode *node) {
        int minVal = node->val;
        while (node->left != nullptr) {
            minVal = node->left->val;
            node = node->left;
        }
        return minVal;
    }

    void inOrderHelper(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        inOrderHelper(node->left);
        std::cout << node->val << " ";
        inOrderHelper(node->right);
    }

    void preOrderHelper(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        std::cout << node->val << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void postOrderHelper(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout << node->val << " ";
    }

    void levelOrderHelper(TreeNode *node) {
        if (node == nullptr) {
            return;
        }

        std::queue<TreeNode *> q;
        q.push(node);

        while (!q.empty()) {
            TreeNode *temp = q.front();
            q.pop();
            std::cout << temp->val << " ";

            if (temp->left != nullptr) {
                q.push(temp->left);
            }
            if (temp->right != nullptr) {
                q.push(temp->right);
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    Tree tree;
    int n, val;
    std::cout << "Enter the number of elements in the tree: ";
    std::cin >> n;

    std::cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        tree.insert(val);
    }

    int choice;
    do {
        std::cout << "\nMenu:\n"
            "1. Insert\n"
            "2. Search\n"
            "3. Remove\n"
            "4. In-order Traversal\n"
            "5. Pre-order Traversal\n"
            "6. Post-order Traversal\n"
            "7. Level-order Traversal\n"
            "8. Exit\n"
            "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to insert: ";
                std::cin >> val;
                tree.insert(val);
                break;
            case 2:
                std::cout << "Enter the value to search: ";
                std::cin >> val;
                if (tree.search(val)) {
                    std::cout << "Value found.\n";
                } else {
                    std::cout << "Value not found.\n";
                }
                break;
            case 3:
                std::cout << "Enter the value to remove: ";
                std::cin >> val;
                tree.remove(val);
                break;
            case 4:
                std::cout << "In-order Traversal: ";
                tree.inOrderTraversal();
                break;
            case 5:
                std::cout << "Pre-order Traversal: ";
                tree.preOrderTraversal();
                break;
            case 6:
                std::cout << "Post-order Traversal: ";
                tree.postOrderTraversal();
                break;
            case 7:
                std::cout << "Level-order Traversal: ";
                tree.levelOrderTraversal();
                break;
            case 8:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}