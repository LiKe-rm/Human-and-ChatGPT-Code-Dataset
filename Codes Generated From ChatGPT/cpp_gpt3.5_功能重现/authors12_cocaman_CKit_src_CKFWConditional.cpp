#include <sys/time.h>
#include "CKFWConditional.h"
#include "CKErrNoException.h"

// 定义一个条件变量的基类
class ICKFWConditionalSpuriousTest {
public:
    virtual ~ICKFWConditionalSpuriousTest() {}
    virtual int test() = 0;
};

// 默认条件变量测试
class CKFWConditionalDefaultTest : public ICKFWConditionalSpuriousTest {
public:
    virtual int test() {
        return 1;
    }
};

// 条件变量类
class CKFWConditional {
private:
    CKFWMutex mutex_;
    pthread_cond_t cond_;

public:
    // 构造函数
    CKFWConditional() {
        int ret = pthread_cond_init(&cond_, NULL);
        if (ret != 0) {
            throw CKErrNoException("Failed to initialize conditional variable");
        }
    }

    // 析构函数
    ~CKFWConditional() {
        int ret = pthread_cond_destroy(&cond_);
        if (ret != 0) {
            throw CKErrNoException("Failed to destroy conditional variable");
        }
    }

    // 等待条件变量被通知
    int lockAndTest(ICKFWConditionalSpuriousTest& test, long timeoutMs) {
        int ret = FWCOND_LOCK_SUCCESS;
        timespec ts;
        timeval tv;

        gettimeofday(&tv, NULL);
        ts.tv_sec = tv.tv_sec + timeoutMs / 1000;
        ts.tv_nsec = tv.tv_usec * 1000 + (timeoutMs % 1000) * 1000000;
        if (ts.tv_nsec > 1000000000) {
            ts.tv_sec++;
            ts.tv_nsec -= 1000000000;
        }

        mutex_.lock();
        while (test.test() != 0) {
            ret = pthread_cond_timedwait(&cond_, mutex_.getMutex(), &ts);
            if (ret == ETIMEDOUT) {
                ret = FWCOND_LOCK_ERROR;
                break;
            }
            if (ret != 0) {
                mutex_.unlock();
                throw CKErrNoException("Failed to wait on conditional variable");
            }
        }
        mutex_.unlock();

        return ret;
    }

    // 获取锁并等待条件变量被通知
    void lockAndWait() {
        mutex_.lock();
        pthread_cond_wait(&cond_, mutex_.getMutex());
        mutex_.unlock();
    }

    // 唤醒一个等待条件变量的线程
    void wakeWaiter() {
        int ret = pthread_cond_signal(&cond_);
        if (ret != 0) {
            throw CKErrNoException("Failed to signal conditional variable");
        }
    }

    // 唤醒所有等待条件变量的线程
    void wakeWaiters() {
        int ret = pthread_cond_broadcast(&cond_);
        if (ret != 0) {
            throw CKErrNoException("Failed to broadcast conditional variable");
        }
    }

    // 解锁
    void unlock() {
        mutex_.unlock();
    }
};
