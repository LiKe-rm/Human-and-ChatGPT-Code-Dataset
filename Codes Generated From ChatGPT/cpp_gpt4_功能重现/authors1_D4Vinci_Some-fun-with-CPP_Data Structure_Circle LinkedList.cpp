#include <iostream>

struct Node {
    int data;
    Node *next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList() {
        Node *current = head;
        while (current) {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void add(int value) {
        Node *newNode = new Node {value, nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            Node *current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool find(int value) {
        Node *current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(int value) {
        if (head == nullptr) {
            return false;
        }
        if (head->data == value) {
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node *current = head;
        while (current->next) {
            if (current->next->data == value) {
                Node *temp = current->next;
                current->next = current->next->next;
                delete temp;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool replace(int oldValue, int newValue) {
        Node *current = head;
        while (current) {
            if (current->data == oldValue) {
                current->data = newValue;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display() {
        Node *current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "null" << std::endl;
    }

    void reverseDisplay() {
        reverseDisplayHelper(head);
        std::cout << "null" << std::endl;
    }

private:
    void reverseDisplayHelper(Node *node) {
        if (node == nullptr) {
            return;
        }
        reverseDisplayHelper(node->next);
        std::cout << node->data << " -> ";
    }

    Node *head;
};

int main() {
    LinkedList list;
    int choice, value, oldValue, newValue;

    do {
        std::cout << "\n1. Add element" << std::endl;
        std::cout << "2. Find element" << std::endl;
        std::cout << "3. Remove element" << std::endl;
        std::cout << "4. Replace element" << std::endl;
        std::cout << "5. Display elements" << std::endl;
        std::cout << "6. Reverse display elements" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the value to add: ";
                std::cin >> value;
                list.add(value);
                break;
            case 2:
                std::cout << "Enter the value to find: ";
                std::cin >> value;
                if (list.find(value)) {
                    std::cout << "Element found" << std::endl;
                } else {
                    std::cout << "Elementnot found" << std::endl;
                }
                break;
            case 3:
                std::cout << "Enter the value to remove: ";
                std::cin >> value;
                if (list.remove(value)) {
                    std::cout << "Element removed" << std::endl;
                } else {
                    std::cout << "Element not found" << std::endl;
                }
                break;
            case 4:
                std::cout << "Enter the old value: ";
                std::cin >> oldValue;
                std::cout << "Enter the new value: ";
                std::cin >> newValue;
                if (list.replace(oldValue, newValue)) {
                    std::cout << "Element replaced" << std::endl;
                } else {
                    std::cout << "Element not found" << std::endl;
                }
                break;
            case 5:
                std::cout << "Displaying elements: ";
                list.display();
                break;
            case 6:
                std::cout << "Reverse displaying elements: ";
                list.reverseDisplay();
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 0);
    return 0;
}
