#include <map>
#include <mutex>

// Define a struct to hold information about each process or thread being monitored
struct ThreadInfo {
    unsigned long long start_addr;  // The starting address of the instruction interval
    unsigned long long end_addr;    // The ending address of the instruction interval
    unsigned long long count;       // The number of instructions executed in the interval
};

// Define a map to hold information about all processes or threads being monitored
std::map<unsigned long long, ThreadInfo> threads_map;

// Define a mutex to synchronize access to the threads_map
std::mutex threads_map_mutex;

// Define a function to update the thread information when the monitored process or thread changes
void thread_changed_callback(unsigned long long thread_id, unsigned long long start_addr, unsigned long long end_addr, unsigned long long count) {
    std::lock_guard<std::mutex> lock(threads_map_mutex);
    threads_map[thread_id] = { start_addr, end_addr, count };
}

// Define a function to calculate the total instruction count for all threads except the one being monitored
unsigned long long get_total_instruction_count(unsigned long long monitored_thread_id) {
    unsigned long long total_count = 0;
    std::lock_guard<std::mutex> lock(threads_map_mutex);
    for (const auto& pair : threads_map) {
        if (pair.first != monitored_thread_id) {
            total_count += pair.second.count;
        }
    }
    return total_count;
}

// Define a function to get the instruction count for the currently monitored process or thread
unsigned long long get_monitored_instruction_count() {
    unsigned long long monitored_thread_id = /* code to get the ID of the currently monitored thread */;
    std::lock_guard<std::mutex> lock(threads_map_mutex);
    auto it = threads_map.find(monitored_thread_id);
    if (it != threads_map.end()) {
        unsigned long long monitored_count = it->second.count;
        unsigned long long total_count = get_total_instruction_count(monitored_thread_id);
        return monitored_count - total_count;
    } else {
        return 0;
    }
}

// Define a function to get the instruction count for a specified process or thread
unsigned long long get_instruction_count(unsigned long long thread_id) {
    std::lock_guard<std::mutex> lock(threads_map_mutex);
    auto it = threads_map.find(thread_id);
    if (it != threads_map.end()) {
        unsigned long long monitored_count = it->second.count;
        unsigned long long total_count = get_total_instruction_count(thread_id);
        return monitored_count - total_count;
    } else {
        return 0;
    }
}
