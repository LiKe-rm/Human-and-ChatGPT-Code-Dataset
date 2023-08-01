#include <mutex>
#include <shared_mutex>
#include <semaphore.h>

enum CKLockType {
    CKFWMutex,
    CKFWRWMutex,
    CKFWSemaphore
};

class CKStackLocker {
public:
    CKStackLocker(CKLockType lockType) {
        switch (lockType) {
            case CKFWMutex:
                m_mutex = new std::mutex();
                m_mutex->lock();
                break;
            case CKFWRWMutex:
                m_mutex = new std::shared_mutex();
                m_mutex->lock_shared();
                break;
            case CKFWSemaphore:
                sem_init(&m_semaphore, 0, 1);
                sem_wait(&m_semaphore);
                break;
            default:
                break;
        }
    }

    ~CKStackLocker() {
        switch (m_lockType) {
            case CKFWMutex:
                m_mutex->unlock();
                delete m_mutex;
                break;
            case CKFWRWMutex:
                m_mutex->unlock_shared();
                delete m_mutex;
                break;
            case CKFWSemaphore:
                sem_post(&m_semaphore);
                sem_destroy(&m_semaphore);
                break;
            default:
                break;
        }
    }

private:
    CKLockType m_lockType;
    union {
        std::mutex* m_mutex;
        std::shared_mutex* m_sharedMutex;
        sem_t m_semaphore;
    };
};

// 使用示例
int main() {
    {
        CKStackLocker lock(CKFWMutex);
        // 代码块1，使用互斥锁
    }
    {
        CKStackLocker lock(CKFWRWMutex);
        // 代码块2，使用读写锁
    }
    {
        CKStackLocker lock(CKFWSemaphore);
        // 代码块3，使用信号量
    }
    return 0;
}
