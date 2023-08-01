#include <iostream>
#include <chrono>
#include <vector>
#include <functional>

class BenchRunner {
    public:
    static void AddBenchmark(std::string name, std::function<void(State&)> func) {
        benchmarks_.push_back(std::make_pair(name, func));
    }

    static void RunAll(int iterations, int warmup_iterations, bool output_to_console = true, bool output_to_plotly = false) {
        std::vector<State> results;

        for (auto& benchmark : benchmarks_) {
            State state(iterations, warmup_iterations);
            benchmark.second(state);
            results.push_back(state);

            if (output_to_console) {
                ConsolePrinter::Print(state);
            }

            if (output_to_plotly) {
                PlotlyPrinter::Print(state);
            }
        }
    }

    private:
    static std::vector<std::pair<std::string, std::function<void(State&)>>> benchmarks_;
};

std::vector<std::pair<std::string, std::function<void(State&)>>> BenchRunner::benchmarks_;

class State {
    public:
    State(int iterations, int warmup_iterations)
        : iterations_(iterations), warmup_iterations_(warmup_iterations) {}

    void SetItemsProcessed(int items) {
        items_processed_ = items;
    }

    void SetElapsedTime(std::chrono::nanoseconds time) {
        elapsed_time_ = time;
    }

    int GetIterations() const {
        return iterations_;
    }

    int GetWarmupIterations() const {
        return warmup_iterations_;
    }

    int GetItemsProcessed() const {
        return items_processed_;
    }

    std::chrono::nanoseconds GetElapsedTime() const {
        return elapsed_time_;
    }

    private:
    int iterations_;
    int warmup_iterations_;
    int items_processed_ = 0;
    std::chrono::nanoseconds elapsed_time_ = std::chrono::nanoseconds(0);
};

class ConsolePrinter {
    public:
    static void Print(const State& state) {
        std::cout << "Benchmark: " << state.GetIterations() << " iterations, " << state.GetWarmupIterations() << " warmup iterations" << std::endl;
        std::cout << "Items processed: " << state.GetItemsProcessed() << std::endl;
        std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(state.GetElapsedTime()).count() << " ms" << std::endl;
        std::cout << std::endl;
    }
};

class PlotlyPrinter {
    public:
    static void Print(const State& state) {
        // TODO: implement
    }
};

// 示例测试函数
void MyTestFunction(State& state) {
    int sum = 0;
    for (int i = 0; i < state.GetIterations(); i++) {
        auto start_time = std::chrono::high_resolution_clock::now();

        // 在此处调用需要测试的函数或代码段
        for (int j = 0; j < 100000; j++) {
            sum += j;
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        if (i >= state.GetWarmupIterations()) {
            state.SetItemsProcessed(state.GetItemsProcessed() + 1);
            state.SetElapsedTime(state.GetElapsedTime() + std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time));
        }
    }
}

int main() {
// 将测试函数添加到 BenchRunner 中
    BenchRunner::AddBenchmark("MyTestFunction", MyTestFunction);
    // 运行所有基准测试，输出到控制台
    BenchRunner::RunAll(100, 10);

    return 0;
}