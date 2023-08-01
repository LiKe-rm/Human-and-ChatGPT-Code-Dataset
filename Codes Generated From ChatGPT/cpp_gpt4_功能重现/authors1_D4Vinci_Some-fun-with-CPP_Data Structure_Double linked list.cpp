#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert_begin(int data) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        size++;
    }

    void insert_end(int data) {
        if (size == 0) {
            insert_begin(data);
            return;
        }

        Node* newNode = new Node;
        newNode->data = data;
        newNode->prev = tail;
        newNode->next = nullptr;

        tail->next = newNode;
        tail = newNode;
        size++;
    }

    void insert_at(int data, int index) {
        if (index < 0 || index > size) {
            cout << "Error: Invalid index" << endl;
            return;
        }

        if (index == 0) {
            insert_begin(data);
            return;
        }

        if (index == size) {
            insert_end(data);
            return;
        }

        Node* newNode = new Node;
        newNode->data = data;
        Node* current = head;

        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        size++;
    }

    void delete_element(int data) {
        Node* current = head;

        while (current != nullptr) {
            if (current->data == data) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                Node* temp = current;
                current = current->next;
                delete temp;
                size--;
            } else {
                current = current->next;
            }
        }
    }

    void delete_at(int index) {
        if (index < 0 || index >= size) {
            cout << "Error: Invalid index" << endl;
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        delete current;
        size--;
    }

    void replace(int index, int data) {
        if (index < 0 || index >= size) {
            cout << "Error: Invalid index" << endl;
            return;
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->data = data;
    }

    void swap_elements(int index1, int index2) {
        if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size) {
            cout << "Error: Invalid index" << endl;
            return;
        }

        if (index1 == index2) {
            return;
        }

        Node* current1 = head;
        for (int i = 0; i < index1; i++) {
            current1 = current1->next;
        }

        Node* current2 = head;
        for (int i = 0; i < index2; i++) {
            current2 = current2->next;
        }

        int temp = current1->data;
        current1->data = current2->data;
        current2->data = temp;
    }

    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void display_reverse() {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    int get_size() {
        return size;
    }

private:
    Node* head;
    Node* tail;
    int size;
};

int main() {
    DoublyLinkedList dll;

    int choice, data, index;

    while (true) {
        cout << "1. Insert at beginning\n2. Insert at end\n3. Insert at index\n4. Delete element\n5. Delete at index\n6. Replace\n7. Swap elements\n8. Display\n9. Display in reverse\n10. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data: ";
                cin >> data;
                dll.insert_begin(data);
                break;
            case 2:
                cout << "Enter data: ";
                cin >> data;
                dll.insert_end(data);
                break;
            case 3:
                cout << "Enter index and data: ";
                cin >> index >> data;
                dll.insert_at(data, index);
                break;
            case 4:
                cout << "Enter data: ";
                cin >> data;
                dll.delete_element(data);
                break;
            case 5:
                cout << "Enter index: ";
                cin >> index;
                dll.delete_at(index);
                break;
            case 6:
                cout << "Enter index and new data: ";
                cin >> index >> data;
                dll.replace(index, data);
                break;
            case 7:
                int index2;
                cout << "Enter two indices: ";
                cin >> index >> index2;
                dll.swap_elements(index, index2);
                break;
            case 8:
                dll.display();
                break;
            case 9:
                dll.display_reverse();
                break;
            case 10:
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

