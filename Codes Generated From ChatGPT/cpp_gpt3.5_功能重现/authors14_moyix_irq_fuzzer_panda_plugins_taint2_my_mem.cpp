#include <iostream>
#include <cstdlib>
#include <cstring>

#define MAX_POOLS 10
#define MAX_POOL_SIZE 1024

// Define a struct to track memory usage statistics for each pool
struct pool_info {
    size_t bytes_allocated;
    size_t num_mallocs;
    size_t num_frees;
    size_t num_strdups;
    size_t num_constr_calls;
    size_t num_destr_calls;
};

// Define an array to hold memory usage statistics for each pool
pool_info mem_usage[MAX_POOLS];

// Define custom memory allocation functions that track usage statistics
void* my_malloc(size_t size, int pool_id) {
    void* ptr = std::malloc(size);
    if (ptr != nullptr) {
        mem_usage[pool_id].bytes_allocated += size;
        mem_usage[pool_id].num_mallocs++;
    }
    return ptr;
}

void* my_calloc(size_t nmemb, size_t size, int pool_id) {
    void* ptr = std::calloc(nmemb, size);
    if (ptr != nullptr) {
        mem_usage[pool_id].bytes_allocated += nmemb * size;
        mem_usage[pool_id].num_mallocs++;
    }
    return ptr;
}

void* my_realloc(void* ptr, size_t size, int pool_id) {
    void* new_ptr = std::realloc(ptr, size);
    if (new_ptr != nullptr) {
        mem_usage[pool_id].bytes_allocated += size;
        mem_usage[pool_id].num_mallocs++;
        if (ptr != nullptr) {
            mem_usage[pool_id].bytes_allocated -= sizeof(*ptr);
            mem_usage[pool_id].num_frees++;
        }
    }
    return new_ptr;
}

void my_free(void* ptr, int pool_id) {
    if (ptr != nullptr) {
        mem_usage[pool_id].bytes_allocated -= sizeof(*ptr);
        mem_usage[pool_id].num_frees++;
        std::free(ptr);
    }
}

char* my_strdup(const char* str, int pool_id) {
    char* new_str = std::strdup(str);
    if (new_str != nullptr) {
        mem_usage[pool_id].bytes_allocated += std::strlen(str) + 1;
        mem_usage[pool_id].num_strdups++;
    }
    return new_str;
}

// Define a function to print memory usage statistics for all pools
void spit_mem_usage() {
    for (int i = 0; i < MAX_POOLS; i++) {
        if (mem_usage[i].bytes_allocated > 0) {
            std::cout << "Pool " << i << ":\n"
                      << "  bytes allocated:    " << mem_usage[i].bytes_allocated << "\n"
                      << "  num mallocs:        " << mem_usage[i].num_mallocs << "\n"
                      << "  num frees:          " << mem_usage[i].num_frees << "\n"
                      << "  num strdups:        " << mem_usage[i].num_strdups << "\n"
                      << "  num constr calls:   " << mem_usage[i].num_constr_calls << "\n"
                      << "  num destr calls:    " << mem_usage[i].num_destr_calls << "\n";
        }
    }
}

int main() {
    // Example usage
    int* int_ptr
    = static_cast<int*>(my_malloc(sizeof(int), 0));
    *int_ptr = 42;
    std::cout << "Allocated " << sizeof(*int_ptr) << " bytes for int value " << *int_ptr << "\n";
    spit_mem_usage();

    char* str = my_strdup("Hello, world!", 1);
    std::cout << "Allocated " << std::strlen(str) + 1 << " bytes for string value " << str << "\n";
    spit_mem_usage();

    my_free(int_ptr, 0);
    std::cout << "Freed " << sizeof(*int_ptr) << " bytes for int value " << *int_ptr << "\n";
    spit_mem_usage();

    my_free(str, 1);
    std::cout << "Freed " << std::strlen(str) + 1 << " bytes for string value " << str << "\n";
    spit_mem_usage();

    return 0;
}