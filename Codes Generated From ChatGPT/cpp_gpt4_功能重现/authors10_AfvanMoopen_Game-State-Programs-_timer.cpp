#include <iostream>
#include <Windows.h>

class Timer {
public:
    Timer() {
        // 获取时钟频率
        QueryPerformanceFrequency(&frequency);
        startCount.QuadPart = 0;
        endCount.QuadPart = 0;
    }

    void start() {
        // 获取开始时刻的时钟周期数
        QueryPerformanceCounter(&startCount);
    }

    void stop() {
        // 获取结束时刻的时钟周期数
        QueryPerformanceCounter(&endCount);
    }

    double getElapsedTimeInMilliseconds() const {
        return getElapsedTime() * 1000.0;
    }

    double getElapsedTimeInSeconds() const {
        return getElapsedTime();
    }

    double getElapsedTimeInMicroseconds() const {
        return getElapsedTime() * 1000000.0;
    }

private:
    double getElapsedTime() const {
        LARGE_INTEGER elapsed;
        elapsed.QuadPart = endCount.QuadPart - startCount.QuadPart;

        // 计算经过的时间（单位：秒）
        return static_cast<double>(elapsed.QuadPart) / static_cast<double>(frequency.QuadPart);
    }

    LARGE_INTEGER frequency;
    LARGE_INTEGER startCount;
    LARGE_INTEGER endCount;
};

int main() {
    Timer timer;

    // 开始计时
    timer.start();

    // 你想要测量的代码
    for (int i = 0; i < 1000000; ++i) {
        std::cout << ".";
    }
    std::cout << std::endl;

    // 结束计时
    timer.stop();

    // 输出经过的时间
    std::cout << "Elapsed time in seconds: " << timer.getElapsedTimeInSeconds() << std::endl;
    std::cout << "Elapsed time in milliseconds: " << timer.getElapsedTimeInMilliseconds() << std::endl;
    std::cout << "Elapsed time in microseconds: " << timer.getElapsedTimeInMicroseconds() << std::endl;

    return 0;
}
