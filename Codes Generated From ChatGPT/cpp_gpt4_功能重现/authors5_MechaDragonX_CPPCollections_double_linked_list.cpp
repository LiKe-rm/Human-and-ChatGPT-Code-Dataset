#include <iostream>
#include <string>
#include <memory>

class Student {
public:
    std::string name;
    int age;

    Student(const std::string &name, int age) : name(name), age(age) {}
    friend std::ostream &operator<<(std::ostream &os, const Student &student) {
        os << "Student{name: " << student.name << ", age: " << student.age << "}";
        return os;
    }
};

template<typename T>
class DoubleListNode {
public:
    T data;
    std::shared_ptr<DoubleListNode<T>> prev;
    std::shared_ptr<DoubleListNode<T>> next;

    DoubleListNode(T data) : data(data), prev(nullptr), next(nullptr) {}
};

template<typename T>
class DoubleLinkedList {
private:
    std::shared_ptr<DoubleListNode<T>> head;
    std::shared_ptr<DoubleListNode<T>> tail;
    size_t size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        while (head != nullptr) {
            head = head->next;
        }
    }

    std::shared_ptr<DoubleListNode<T>> get_head() const {
        return head;
    }

    std::shared_ptr<DoubleListNode<T>> get_tail() const {
        return tail;
    }

    size_t get_size() const {
        return size;
    }

    bool contains(const T &value) {
        std::shared_ptr<DoubleListNode<T>> current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void add(const T &value) {
        std::shared_ptr<DoubleListNode<T>> new_node = std::make_shared<DoubleListNode<T>>(value);
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void remove_tail() {
        if (size == 0) {
            return;
        }

        if (size == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        size--;
    }

    void remove(const T &value) {
        std::shared_ptr<DoubleListNode<T>> current = head;
        while (current != nullptr) {
            if (current->data == value) {
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
                size--;
                break;
            }
            current = current->next;
        }
    }

    void display() const {
        std::shared_ptr<DoubleListNode<T>> current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoubleLinkedList<int> int_list;
    int_list.add(1);
    int_list.add(2);
    int_list.add(3);
    int_list.display();

    DoubleLinkedList<char> char_list;
    char_list.add('a');
    char_list.add('b');
    char_list.add('c');
    char_list.display();

    DoubleLinkedList<bool> bool_list;
    bool_list.add(true);
    bool_list.add(false);
    bool_list.add(true);
    bool_list.display();

    DoubleLinkedList<float> float_list;
    float_list.add(1.1f);
    float_list.add(2.2f);
    float_list.add(3.3f);
    float_list.display();

    DoubleLinkedList<double> double_list;
    double_list.add(1.1);
    double_list.add(2.2);
    double_list.add(3.3);
    double_list.display();

    DoubleLinkedList<wchar_t> wchar_list;
    wchar_list.add(L'A');
    wchar_list.add(L'B');
    wchar_list.add(L'C');
    wchar_list.display();

    DoubleLinkedList<std::string> string_list;
    string_list.add("Hello");
    string_list.add("World");
    string_list.add("!");
    string_list.display();

    DoubleLinkedList<Student> student_list;
    student_list.add(Student("Alice", 20));
    student_list.add(Student("Bob", 22));
    student_list.add(Student("Cathy", 19));
    student_list.display();

    return 0;
}
