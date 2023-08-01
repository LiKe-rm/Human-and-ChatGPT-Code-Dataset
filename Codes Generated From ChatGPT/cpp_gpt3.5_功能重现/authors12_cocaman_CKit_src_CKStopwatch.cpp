#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// 辅助函数msleep()和mmsleep()，用于在Solaris系统上替代sleep()和usleep()函数。
void msleep(unsigned int milliseconds) {
	struct timeval tv;
	tv.tv_sec = milliseconds / 1000;
	tv.tv_usec = (milliseconds % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
}

void mmsleep(unsigned int microseconds) {
	struct timeval tv;
	tv.tv_sec = microseconds / 1000000;
	tv.tv_usec = microseconds % 1000000;
	select(0, NULL, NULL, NULL, &tv);
}

class CKStopwatch {
public:
	// 默认构造函数
	CKStopwatch() {
		reset();
	}

	// 开始计时
	void start() {
		if (running) {
			throw std::logic_error("CKStopwatch is already running.");
		}
		gettimeofday(&realStart, NULL);
		getrusage(RUSAGE_SELF, &usageStart);
		running = true;
	}

	// 停止计时
	void stop() {
		if (!running) {
			throw std::logic_error("CKStopwatch is not running.");
		}
		gettimeofday(&realStop, NULL);
		getrusage(RUSAGE_SELF, &usageStop);
		running = false;
		elapsedRealTime = (realStop.tv_sec - realStart.tv_sec) + (realStop.tv_usec - realStart.tv_usec) / 1000000.0;
		elapsedUserTime = (usageStop.ru_utime.tv_sec - usageStart.ru_utime.tv_sec) + (usageStop.ru_utime.tv_usec - usageStart.ru_utime.tv_usec) / 1000000.0;
		elapsedSysTime = (usageStop.ru_stime.tv_sec - usageStart.ru_stime.tv_sec) + (usageStop.ru_stime.tv_usec - usageStart.ru_stime.tv_usec) / 1000000.0;
	}

	// 记录当前时间为拆分时间
	void split() {
		if (!running) {
			throw std::logic_error("CKStopwatch is not running.");
		}
		splits.push_back(getElapsedRealTime());
	}

	// 获取已过时间
	double getRealTimeInSec() const {
		if (running) {
			throw std::logic_error("CKStopwatch is still running.");
		}
		return elapsedRealTime;
	}

	double getUserTimeInSec() const {
		if (running) {
			throw std::logic_error("CKStopwatch is still running.");
		}
		return elapsedUserTime;
	}

	double getSysTimeInSec() const {
		if (running) {
			throw std::logic_error("CKStopwatch is still running.");
		}
		return elapsedSysTime;
	}

	// 重置计时器
	void reset() {
		running = false;
		elapsedRealTime = 0;
		elapsedUserTime = 0;
		elapsedSysTime = 0;
		splits.clear();
	}

	// 转换为字符串
	std::string toString() const {
		std::ostringstream oss;
		oss << std::fixed << std::setprecision(6)
			<< "Real time: " << getRealTimeInSec() << " sec, "
			<< "User time: " << getUserTimeInSec() << " sec, "
			<< "Sys time: " << getSysTimeInSec() << " sec, "
			<< "Splits: ";
		if (splits.empty()) {
			oss << "none";
		}
		else {
			for (std::size_t i = 0; i < splits.size(); ++i) {
				oss << splits[i];
				if (i != splits.size() - 1) {
					oss << ", ";
				}
			}
		}
		return oss.str();
	}

	// 比较操作符
	bool operator==(const CKStopwatch& other) const {
		return (elapsedRealTime == other.elapsedRealTime &&
			elapsedUserTime == other.elapsedUserTime &&
			elapsedSysTime == other.elapsedSysTime &&
			splits == other.splits);
	}

	bool operator!=(const CKStopwatch& other) const {
		return !(*this == other);
	}
private:
	bool running;
	double elapsedRealTime; // 真实时间
	double elapsedUserTime; // 用户时间
	double elapsedSysTime; // 系统时间
	struct timeval realStart, realStop; // 真实时间的开始和结束时间
	struct rusage usageStart, usageStop; // 用户时间和系统时间的开始和结束时间
	std::vector<double> splits; // 拆分时间
	// 获取已过时间
	double getElapsedRealTime() const {
		struct timeval now;
		gettimeofday(&now, NULL);
		return (now.tv_sec - realStart.tv_sec) + (now.tv_usec - realStart.tv_usec) / 1000000.0;
	}
};