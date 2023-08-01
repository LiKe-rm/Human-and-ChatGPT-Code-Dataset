#include <iostream>
#include <random>
#include <ctime>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <typename T>
class Queue {
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& data) {
        Node<T>* newNode = new Node<T>;
        newNode->data = data;
        newNode->next = nullptr;
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }
        Node<T>* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        size--;
        return data;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

private:
    Node<T>* head;
    Node<T>* tail;
    int size;
};

class RandomGenerator {
public:
    RandomGenerator(int min, int max) : gen(rd()), dis(min, max) {
        std::srand(std::time(0));
    }

    int getRandomNumber() {
        return dis(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

class Event {
public:
    Event(int eventTime) : eventTime(eventTime) {}

    virtual void process() = 0;

    int getEventTime() const {
        return eventTime;
    }

protected:
    int eventTime;
};

class ArrivalEvent : public Event {
public:
    ArrivalEvent(Bank* bank, Customer* customer, int eventTime)
        : Event(eventTime), bank(bank), customer(customer) {}

    void process() override {
        bank->customerArrives(this);
    }

        Customer* getCustomer() const {
        return customer;
    }

private:
    Bank* bank;
    Customer* customer;
};

class DepartureEvent : public Event {
public:
    DepartureEvent(Bank* bank, Customer* customer, int eventTime)
        : Event(eventTime), bank(bank), customer(customer) {}

    void process() override {
        bank->customerDeparts(this);
    }

        Customer* getCustomer() const {
        return customer;
    }

private:
    Bank* bank;
    Customer* customer;
};

class Bank {
public:
    void customerArrives(ArrivalEvent* arrivalEvent) {
        // 处理顾客到达
    }

    void customerDeparts(DepartureEvent* departureEvent) {
        // 处理顾客离开
    }

private:
    Queue<Customer*> queue;
};

class Customer {
public:
    Customer(int arrivalTime, int serviceTime) : arrivalTime(arrivalTime), serviceTime(serviceTime) {}

    int getArrivalTime() const {
        return arrivalTime;
    }

    int getServiceTime() const {
        return serviceTime;
    }

private:
    int arrivalTime;
    int serviceTime;
};


int main() {
    Bank bank;
    RandomGenerator arrivalTimeGenerator(1, 10);
    RandomGenerator serviceTimeGenerator(5, 15);
    // 用于存储待处理事件的队列
    Queue<Event*> eventQueue;

    // 模拟时长（单位：分钟）
    int simulationDuration = 720;

    // 创建第一个顾客对象
    int firstServiceTime = serviceTimeGenerator.getRandomNumber();
    int firstArrivalTime = arrivalTimeGenerator.getRandomNumber();
    Customer* firstCustomer = new Customer(firstArrivalTime, firstServiceTime);

    // 将第一个顾客的到达事件添加到事件队列
    eventQueue.enqueue(new ArrivalEvent(&bank, firstCustomer, firstArrivalTime));

    // 当前模拟时间
    int currentTime = 0;

    while (currentTime < simulationDuration) {
        // 如果事件队列不为空，处理下一个事件
        if (!eventQueue.isEmpty()) {
            Event* nextEvent = eventQueue.dequeue();
            currentTime = nextEvent->getEventTime();

            if (dynamic_cast<ArrivalEvent*>(nextEvent)) {
                ArrivalEvent* arrivalEvent = static_cast<ArrivalEvent*>(nextEvent);
                bank.customerArrives(arrivalEvent);

                // 随机生成下一个顾客到达事件
                int nextArrivalTime = currentTime + arrivalTimeGenerator.getRandomNumber();
                int nextServiceTime = serviceTimeGenerator.getRandomNumber();
                Customer* nextCustomer = new Customer(nextArrivalTime, nextServiceTime);
                if (nextArrivalTime <= simulationDuration) {
                    eventQueue.enqueue(new ArrivalEvent(&bank, nextCustomer, nextArrivalTime));
                }
            } else if (dynamic_cast<DepartureEvent*>(nextEvent)) {
                DepartureEvent* departureEvent = static_cast<DepartureEvent*>(nextEvent);
                bank.customerDeparts(departureEvent);
            }

            // 释放已处理事件的内存
            delete nextEvent;
        } else {
            currentTime++;
        }
    }

    return 0;
}


