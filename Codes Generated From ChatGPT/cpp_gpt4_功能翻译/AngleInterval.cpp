#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Interval {
public:
    double low, high;

    Interval(double low, double high) : low(low), high(high) {}

    bool contains(const Interval& other) const {
        return low <= other.low && high >= other.high;
    }

    double getSize() const {
        return high - low;
    }

    bool isEmpty() const {
        return getSize() <= 0.001;
    }

    bool intersects(const Interval& other) const {
        return (low <= other.high && high >= other.low);
    }
};

class AngleInterval {
public:
    std::vector<Interval> subIntervals;

    AngleInterval(double startAngle, double endAngle) {
        if (endAngle < startAngle) {
            throw std::runtime_error("End angle should be greater than start angle.");
        } else if (endAngle - startAngle >= 2 * M_PI) {
            subIntervals.push_back(Interval(0, 2 * M_PI));
        } else {
            while (startAngle < 0) startAngle += 2 * M_PI;
            while (endAngle < 0) endAngle += 2 * M_PI;
            startAngle = fmod(startAngle, 2 * M_PI);
            endAngle = fmod(endAngle, 2 * M_PI);

            if (startAngle < endAngle) {
                Interval tempInterval(startAngle, endAngle);
                if (!tempInterval.isEmpty()) {
                    subIntervals.push_back(tempInterval);
                }
            } else {
                Interval tempInterval(startAngle, 2 * M_PI);
                if (!tempInterval.isEmpty()) {
                    subIntervals.push_back(tempInterval);
                }
                tempInterval = Interval(0, endAngle);
                if (!tempInterval.isEmpty()) {
                    subIntervals.push_back(tempInterval);
                }
            }
        }
    }

    std::vector<AngleInterval> subtract(const AngleInterval& intervalToSubtract) {
        std::vector<Interval> afterSubtractionIntervals = subIntervals;

        if (intervalToSubtract.subIntervals.empty()) {
            return { *this };
        }

        for (const auto& subIntervalToSubtract : intervalToSubtract.subIntervals) {
            std::vector<Interval> newAfterSubtractionIntervals;

            for (const auto& afterSubtractionInterval : afterSubtractionIntervals) {
                // Interval subtraction logic here
            }

            afterSubtractionIntervals = newAfterSubtractionIntervals;
        }

        std::vector<AngleInterval> newAngleIntervals;
        for (const auto& afterSubtractionInterval : afterSubtractionIntervals) {
            if (!afterSubtractionInterval.isEmpty()) {
                newAngleIntervals.emplace_back(afterSubtractionInterval.low, afterSubtractionInterval.high);
            }
        }

        return newAngleIntervals;
    }

    // Add other methods similar to the provided Java code
    // ...
};

int main() {
    AngleInterval angleInterval(0, M_PI);
    // Use angleInterval as needed

    return 0;
}
