#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>

template <typename T>
class ArrayQueue {
private:
    std::vector<T> queueData;
    int first = 0;
    int last = 0;
    int size = 0;

    void ensureCapacity(int minCapacity) {
        int capacity = queueData.capacity();
        if (capacity < minCapacity) {
            queueData.reserve(capacity * 2);
        }
    }

    int getPos(int index) {
        if (index >= 0 && index < size) {
            return (first + index) % queueData.capacity();
        }
        throw std::out_of_range("Index: " + std::to_string(index) + ", Size: " + std::to_string(size));
    }

public:
    ArrayQueue() {
        queueData.reserve(16);
    }

    ArrayQueue(int initialCapacity) {
        if (initialCapacity < 0) {
            throw std::invalid_argument("illegal capacity: " + std::to_string(initialCapacity));
        }
        queueData.reserve(initialCapacity);
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    T get(int index) {
        return queueData[getPos(index)];
    }

    void add(int index, T element) {
        ensureCapacity(size + 1);
        if (index == size) {
            queueData.insert(queueData.begin() + last, element);
            last = (last + 1) % queueData.capacity();
            size++;
        } else {
            index = getPos(index);

            if (index == first) {
                queueData.insert(queueData.begin() + first, element);
                first = (first - 1 + queueData.capacity()) % queueData.capacity();
            } else {
                queueData.insert(queueData.begin() + index, element);
                size++;
                last = (last + 1) % queueData.capacity();
            }
        }
    }

    T remove(int index) {
        T value;
        index = getPos(index);

        value = queueData[index];
        queueData.erase(queueData.begin() + index);

        if (index == first) {
            first = (first + 1) % queueData.capacity();
        } else if (index < last) {
            last = (last - 1 + queueData.capacity()) % queueData.capacity();
        } else {
            first = (first + 1) % queueData.capacity();
        }

        size--;
        return value;
    }

    void clear() {
        queueData.clear();
        first = last = size = 0;
    }
};

int main() {
    ArrayQueue<int> queue(10);

    for (int i = 0; i < 10; i++) {
        queue.add(i, i + 1);
    }

    std::cout << "Initial queue: ";
    for (int i = 0; i < queue.getSize(); i++) {
        std::cout << queue.get(i) << " ";
    }
    std::cout << std::endl;

    queue.remove(4);
    std::cout << "After removing element at index 4: ";
    for (int i = 0; i < queue.getSize(); i++) {
        std::cout << queue.get(i) << " ";
    }
    std::cout << std::endl;

    queue.clear();
    std::cout << "After clearing the queue: ";
    for (int i = 0; i < queue.getSize(); i++) {
        std::cout << queue.get(i) << " ";
}
std::cout << std::endl;
return 0;
}