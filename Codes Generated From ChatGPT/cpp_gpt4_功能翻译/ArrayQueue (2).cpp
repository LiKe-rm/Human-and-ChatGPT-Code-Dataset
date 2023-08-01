#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class ArrayQueue {
private:
    string* q;
    int rear;
    int front;
    int size;
    int capacity;

public:
    ArrayQueue(int s) : q(new string[s]), rear(0), front(0), size(0), capacity(s) {}

    ~ArrayQueue() {
        delete[] q;
    }

    void enqueue(const string& s) {
        if (size == capacity) {
            throw runtime_error("Queue is full");
        }
        else {
            // Add to rear
            size++;
            q[rear] = s;
            rear++;
            // If at end of array, wrap around
            if (rear == capacity) rear = 0;
        }
    }

    bool empty() const {
        return size == 0;
    }

    string dequeue() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        else {
            size--;
            // Remove from front
            string value = q[front];

            // Facilitate garbage collection
            q[front] = "";

            // Update front
            front++;
            if (front == capacity) front = 0;

            return value;
        }
    }

    int get_size() const {
        return size;
    }
};
