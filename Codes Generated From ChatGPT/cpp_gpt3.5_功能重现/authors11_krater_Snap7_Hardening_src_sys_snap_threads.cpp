#include <thread>
#include <chrono>

class TSnapThread {
public:
    TSnapThread() : m_bRunning(false), m_pThread(nullptr) {}
    virtual ~TSnapThread() { Stop(); }

    bool Start() {
        if (m_bRunning) {
            return false;
        }
        m_bRunning = true;
        m_pThread = new std::thread(&TSnapThread::ThreadProc, this);
        return true;
    }

    void Stop() {
        if (m_pThread) {
            m_bRunning = false;
            m_pThread->join();
            delete m_pThread;
            m_pThread = nullptr;
        }
    }

    void Terminate() {
        m_bRunning = false;
    }

    void Join() {
        if (m_pThread) {
            m_pThread->join();
        }
    }

    bool WaitFor(const unsigned int milliseconds) {
        if (m_pThread) {
            m_pThread->join();
            return true;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
            return false;
        }
    }

protected:
    virtual void Execute() = 0;

private:
    void ThreadProc() {
        while (m_bRunning) {
            Execute();
        }
    }

    bool m_bRunning;
    std::thread* m_pThread;
};
