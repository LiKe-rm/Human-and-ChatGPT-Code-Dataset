#include <deque>
#include <mutex>
#include <chrono>

// A struct to represent a measuring point
struct MeasuringPoint {
    double weight; // The weight value
    std::chrono::time_point<std::chrono::system_clock> time; // The time at which the weight was measured
};

class ScaleWrapper {
public:
    // Returns the singleton instance of the ScaleWrapper class
    static ScaleWrapper& GetInstance() {
        static ScaleWrapper instance;
        return instance;
    }

    // Initializes the class with a given weight offset
    void Initialize(double offset) {
        std::lock_guard<std::mutex> lock(mutex_);
        offset_ = offset;
    }

    // Adds a new measuring point to the deque
    void AddMeasuringPoint(MeasuringPoint point) {
        std::lock_guard<std::mutex> lock(mutex_);
        measuring_points_.push_back(point);
    }

    // Removes all measuring points from the deque
    void ClearMeasuringPoints() {
        std::lock_guard<std::mutex> lock(mutex_);
        measuring_points_.clear();
    }

    // Returns the latest weight value
    double GetLatestWeight() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (measuring_points_.empty()) {
            return 0.0;
        }
        return measuring_points_.back().weight - offset_;
    }

    // Sets the current weight value to zero
    void Tare() {
        std::lock_guard<std::mutex> lock(mutex_);
        offset_ += GetLatestWeight();
    }

    // Computes the average weight value
    double ComputeAverageWeight() {
        std::lock_guard<std::mutex> lock(mutex_);
        double sum = 0.0;
        for (const auto& point : measuring_points_) {
            sum += point.weight;
        }
        return (sum / measuring_points_.size()) - offset_;
    }

    // Computes the weighted average weight value
    double ComputeWeightedAverageWeight() {
        std::lock_guard<std::mutex> lock(mutex_);
        double sum = 0.0;
        double total_weight = 0.0;
        for (const auto& point : measuring_points_) {
            sum += point.weight * point.weight;
            total_weight += point.weight;
        }
        return ((sum / total_weight) - offset_);
    }

    // Computes the rate of change in weight over a given time period
    double ComputeWeightChangeRate(std::chrono::seconds time_period) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (measuring_points_.size() < 2) {
            return 0.0;
        }
        double delta_weight = measuring_points_.back().weight - measuring_points_.front().weight;
        double delta_time = std::chrono::duration_cast<std::chrono::duration<double>>(measuring_points_.back().time - measuring_points_.front().time).count();
        return (delta_weight / delta_time) / time_period.count();
    }

private:
    // Private constructor to enforce singleton pattern
    ScaleWrapper() {}

    // Private copy constructor and assignment operator to prevent copies
    ScaleWrapper(const ScaleWrapper&) = delete;
    ScaleWrapper& operator=(const ScaleWrapper&) = delete;

    std::deque<MeasuringPoint> measuring_points_; // The deque of measuring points
    double offset_ = 0.0; // The weight offset
    std::mutex mutex_; // Mutex to protect access to the measuring points deque
};
