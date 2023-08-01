#include <iostream>
#include <thread>

enum class ThreadPolicy { Other, FIFO, RoundRobin };
enum class ThreadScope { System, Process };
enum class ThreadPriority { Low, Normal, High };

class CKFWThread {
public:
    CKFWThread() {}
    virtual ~CKFWThread() {}

    void setPolicy(ThreadPolicy policy) {
        policy_ = policy;
    }

    void setScope(ThreadScope scope) {
        scope_ = scope;
    }

    void setPriority(ThreadPriority priority) {
        priority_ = priority;
    }

    void setDetachable(bool detachable) {
        detachable_ = detachable;
    }

    void setTag(const std::string& tag) {
        tag_ = tag;
    }

    void start() {
        try {
            initialize();
            thread_ = std::thread(&CKFWThread::run, this);
            if (detachable_) {
                thread_.detach();
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught while starting thread: " << e.what() << std::endl;
        }
    }

    void stop() {
        try {
            if (thread_.joinable()) {
                terminate();
                thread_.join();
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught while stopping thread: " << e.what() << std::endl;
        }
    }

    void wait() {
        try {
            if (thread_.joinable()) {
                thread_.join();
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught while waiting for thread: " << e.what() << std::endl;
        }
    }

    void detach() {
        try {
            if (thread_.joinable()) {
                thread_.detach();
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception caught while detaching thread: " << e.what() << std::endl;
        }
    }

protected:
    virtual void initialize() {}
    virtual void process() {}
    virtual void terminate() {}

private:
    void run() {
        try {
            process();
        } catch (const std::exception& e) {
            std::cerr << "Exception caught while running thread: " << e.what() << std::endl;
        }
    }

    std::thread thread_;
    ThreadPolicy policy_ = ThreadPolicy::Other;
    ThreadScope scope_ = ThreadScope::System;
    ThreadPriority priority_ = ThreadPriority::Normal;
    bool detachable_ = false;
    std::string tag_;
};

int main() {
    CKFWThread thread;
    thread.setPolicy(ThreadPolicy::FIFO);
    thread.setScope(ThreadScope::Process);
    thread.setPriority(ThreadPriority::High);
    thread.setDetachable(true);
    thread.setTag("MyThread");

    thread.start();
    thread.wait();

    return 0;
}
