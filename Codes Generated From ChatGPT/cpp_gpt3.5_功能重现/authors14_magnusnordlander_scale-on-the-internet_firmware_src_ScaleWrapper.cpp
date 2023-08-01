#include <cmath>
#include <cstdint>
#include <algorithm>

// 定义一些常量
const int MAX_DATA_COUNT = 1000; // 最大数据存储数量
const int SHORT_AVG_COUNT = 10; // 短时间内数据的数量
const int LONG_AVG_COUNT = 100; // 长时间内数据的数量
const float WEIGHT_SCALE = 0.01; // 重量的比例因子

// 定义一个时间类型，用于计算时间差
typedef uint32_t microtime_t;

class ScaleWrapper {
private:
	// 私有成员变量
	unsigned int dataCount; // 数据数量
	uint16_t allData[MAX_DATA_COUNT]; // 存储所有读取到的数据
	uint16_t shortAvgData[SHORT_AVG_COUNT]; // 存储短时间内的数据
	uint16_t longAvgData[LONG_AVG_COUNT]; // 存储长时间内的数据
	float shortAvgWeight; // 短时间内的平均重量
	float longAvgWeight; // 长时间内的平均重量
	float latestWeight; // 最新的重量
	float latestShortAvgWeight; // 最新的短时间内的平均重量
	float latestLongAvgWeight; // 最新的长时间内的平均重量
	microtime_t lastUpdateTime; // 上一次更新的时间

	// 私有成员函数
	float calcStandardDeviation(uint16_t* data, int count); // 计算标准差
	float calcAverage(uint16_t* data, int count); // 计算平均值

public:
	ScaleWrapper();

	void dataReadyISR(uint16_t data); // 读取原始数据并存储到数组中
	void refresh(); // 刷新最新的重量数据，计算平均值、速率变化等信息
	float averageLast(microtime_t relMicros); // 计算给定时间段内称重值的平均值
	bool isValueStable(microtime_t relMicros, unsigned short minValues, float sigma); // 判断给定时间段内称重值的标准差是否小于给定阈值，以判断重量数据是否趋于稳定
	float getLatestWeight(); // 获取最新的称重值
	float getLatestWeightShortAverage(); // 获取最新的短时间内的平均值
	float getLatestWeightLongAverage(); // 获取最新的长时间内的平均值
};

// 构造函数
ScaleWrapper::ScaleWrapper() {
	dataCount = 0;
	shortAvgWeight = 0;
	longAvgWeight = 0;
	latestWeight = 0;
	latestShortAvgWeight = 0;
	latestLongAvgWeight = 0;
	lastUpdateTime = 0;
}

// 中断服务函数，读取原始数据并存储到数组中
void ScaleWrapper::dataReadyISR(uint16_t data) {
	if (dataCount >= MAX_DATA_COUNT) {
		return;
	}

	allData[dataCount++] = data;
}

// 刷新最新的重量数据，计算平均值、速率变化等信息
void ScaleWrapper::refresh() {
	// 计算时间差
	microtime_t currentTime = millis(); // 这里用millis()模拟获取当前时间
	if (lastUpdateTime == 0) {
		lastUpdateTime = currentTime;
		return;
	}
	microtime_t deltaTime = currentTime - lastUpdateTime;
	lastUpdateTime = currentTime;
	// 更新最新的重量
	latestWeight = allData[dataCount - 1] * WEIGHT_SCALE;

	// 计算短时间内的平均重量
	float sum = 0;
	int count = std::min(dataCount, SHORT_AVG_COUNT);
	for (int i = 0; i < count; i++) {
		sum += allData[dataCount - 1 - i];
	}
	shortAvgWeight = sum / count;
	latestShortAvgWeight = shortAvgWeight * WEIGHT_SCALE;

	// 计算长时间内的平均重量
	sum = 0;
	count = std::min(dataCount, LONG_AVG_COUNT);
	for (int i = 0; i < count; i++) {
		sum += allData[dataCount - 1 - i];
	}
	longAvgWeight = sum / count;
	latestLongAvgWeight = longAvgWeight * WEIGHT_SCALE;
}

// 计算给定时间段内称重值的平均值
float ScaleWrapper::averageLast(microtime_t relMicros) {
	// 计算起始时间
	microtime_t startTime = millis() - relMicros;
	// 查找数据范围
	int startIndex = dataCount - 1;
	while (startIndex >= 0 && (startTime - millis() + (startIndex - dataCount + 1) * 1000) < 0) {
		startIndex--;
	}
	if (startIndex < 0) {
		return 0;
	}
	int count = dataCount - startIndex;

	// 计算平均值
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum += allData[startIndex + i];
	}
	return sum / count * WEIGHT_SCALE;
}

// 判断给定时间段内称重值的标准差是否小于给定阈值，以判断重量数据是否趋于稳定
bool ScaleWrapper::isValueStable(microtime_t relMicros, unsigned short minValues, float sigma) {
	// 计算起始时间
	microtime_t startTime = millis() - relMicros;
	// 查找数据范围
	int startIndex = dataCount - 1;
	while (startIndex >= 0 && (startTime - millis() + (startIndex - dataCount + 1) * 1000) < 0) {
		startIndex--;
	}
	if (startIndex < 0) {
		return false;
	}
	int count = dataCount - startIndex;

	// 计算标准差
	float avg = calcAverage(allData + startIndex, count);
	float sd = calcStandardDeviation(allData + startIndex, count);

	return count >= minValues && sd <= sigma * WEIGHT_SCALE;
}

// 获取最新的称重值
float ScaleWrapper::getLatestWeight() {
	return latestWeight;
}

// 获取最新的短时间内的平均值
float ScaleWrapper::getLatestWeightShortAverage() {
	return latestShortAvgWeight;
}

// 获取最新的长时间内的平均值
float ScaleWrapper::getLatestWeightLongAverage() {
	return latestLongAvgWeight;
}

// 计算标准差
float ScaleWrapper::calcStandardDeviation(uint16_t* data, int count) {
	if (count <= 1) {
		return 0;
	}
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum += data[i];
	}
	float avg = sum / count;
	float variance = 0;
	for (int i = 0; i < count; i++) {
		variance += (data[i] - avg) * (data[i] - avg);
	}
	variance /= count - 1;
	return sqrt(variance);
}

// 计算平均值
float ScaleWrapper::calcAverage(uint16_t* data, int count) {
	float sum = 0;
	for (int i = 0; i < count; i++) {
		sum += data[i];
	}
	return sum / count;
}