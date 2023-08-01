#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <dlfcn.h>
#include <sys/system_properties.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>

#include "MemModule.h"
#include "GotIntegrity.h"
#include "HookTest.h"
#include "InlineStatus.h"
#include "Log.h"
#include "MyApi.h"
#include "MemoryScan.h"
#include "SectionIntegrity.h"

std::mutex mtx;

void library_init() {
    void* handle;
    void (*test)();

    handle = dlopen("libsample.so", RTLD_NOW);

    if (!handle) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cerr << "Error: " << dlerror() << std::endl;
        return;
    }

    test = (void (*)())dlsym(handle, "test");

    if (!test) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cerr << "Error: " << dlerror() << std::endl;
        dlclose(handle);
        return;
    }

    test();
    dlclose(handle);
}

void integrity_check() {
    GotIntegrity got_integrity;
    SectionIntegrity section_integrity;
    InlineStatus inline_status;
    MemoryScan memory_scan;

    while (true) {
        got_integrity.check();
        section_integrity.check();
        inline_status.check();
        memory_scan.check();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void hook_test() {
    HookTest hook_test;

    while (true) {
        hook_test.check();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void log_thread() {
    Log log;

    while (true) {
        log.write();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    struct stat sb;

    if (stat("/system/lib/libsample.so", &sb) == 0) {
        library_init();
    }

    std::thread t1(integrity_check);
    std::thread t2(hook_test);
    std::thread t3(log_thread);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
