#include <iostream>
#include <stdexcept>
#include <cstring>

template <typename T>
class ArrayQueue {
public:
    ArrayQueue();
    ArrayQueue(int initialCapacity);
    ~ArrayQueue();

    void ensureCapacity(int minCapacity);
    void trimToSize();

    int size() const;
    bool isEmpty() const;
    bool contains(const T& element) const;

    int indexOf(const T& element) const;
    int lastIndexOf(const T& element) const;

    T& get(int index);
    void set(int index, const T& element);

    void add(int index, const T& element);
    T remove(int index);
    bool remove(const T& element);
    void clear();

private:
    int getPos(int index) const;
    void copy(T* newData);

    T* queueData;
    int first;
    int last;
    int _size;
    int capacity;
};

template <typename T>
ArrayQueue<T>::ArrayQueue() : ArrayQueue(16) {}

template <typename T>
ArrayQueue<T>::ArrayQueue(int initialCapacity)
    : first(0), last(0), _size(0), capacity(initialCapacity) {
    if (initialCapacity < 0) {
        throw std::invalid_argument("Illegal capacity: " + std::to_string(initialCapacity));
    }
    queueData = new T[capacity];
}

template <typename T>
ArrayQueue<T>::~ArrayQueue() {
    delete[] queueData;
}

template <typename T>
void ArrayQueue<T>::ensureCapacity(int minCapacity) {
    if (capacity < minCapacity) {
        int newCapacity = capacity * 2;
        if (newCapacity < minCapacity) {
            newCapacity = minCapacity;
        }
        T* newData = new T[newCapacity];
        copy(newData);
        delete[] queueData;
        queueData = newData;
        capacity = newCapacity;
        first = 0;
        last = _size;
    }
}

template <typename T>
void ArrayQueue<T>::trimToSize() {
    if (_size < capacity) {
        capacity = _size;
        T* newData = new T[capacity];
        copy(newData);
        delete[] queueData;
        queueData = newData;
        first = 0;
        last = _size;
    }
}

template <typename T>
int ArrayQueue<T>::size() const {
    return _size;
}

template <typename T>
bool ArrayQueue<T>::isEmpty() const {
    return _size == 0;
}

template <typename T>
bool ArrayQueue<T>::contains(const T& element) const {
    return indexOf(element) >= 0;
}

template <typename T>
int ArrayQueue<T>::indexOf(const T& element) const {
    for (int index = 0; index < _size; ++index) {
        if (queueData[(first + index) % capacity] == element) {
            return index;
        }
    }
    return -1;
}

template <typename T>
int ArrayQueue<T>::lastIndexOf(const T& element) const {
    for (int index = _size - 1; index >= 0; --index) {
        if (queueData[(first + index) % capacity] == element) {
            return index;
        }
    }
    return -1;
}

template <typename T>
T& ArrayQueue<T>::get(int index) {
    return queueData[getPos(index)];
}

template <typename T>
void ArrayQueue<T>::set(int index, const T& element) {
    queueData[getPos(index)] = element;
}

