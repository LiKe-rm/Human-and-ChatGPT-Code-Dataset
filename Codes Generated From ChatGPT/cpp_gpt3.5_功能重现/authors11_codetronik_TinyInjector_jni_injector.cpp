#include <iostream>
#include <dlfcn.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <unistd.h>
#include <cstring>

const char *LIB_PATH = "/path/to/your/shared/library.so";

pid_t find_target_pid(const char *target_process_name) {
    DIR *dir = opendir("/proc");
    if (!dir) {
        return -1;
    }

    pid_t target_pid = -1;
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        int pid = atoi(entry->d_name);
        if (pid <= 0) {
            continue;
        }

        std::ostringstream cmdline_path;
        cmdline_path << "/proc/" << pid << "/cmdline";
        std::ifstream cmdline_file(cmdline_path.str());
        std::string cmdline;
        std::getline(cmdline_file, cmdline);

        if (!cmdline.empty()) {
            size_t pos = cmdline.find('\0');
            if (pos != std::string::npos) {
                cmdline = cmdline.substr(0, pos);
            }

            if (cmdline.find(target_process_name) != std::string::npos) {
                target_pid = pid;
                break;
            }
        }
    }

    closedir(dir);
    return target_pid;
}

uintptr_t get_remote_func_address(pid_t target_pid, const char *library_name, const char *func_name) {
    uintptr_t func_address = 0;

    std::ostringstream maps_path;
    maps_path << "/proc/" << target_pid << "/maps";
    std::ifstream maps_file(maps_path.str());
    std::string line;

    uintptr_t library_base = 0;
    while (std::getline(maps_file, line)) {
        if (line.find(library_name) != std::string::npos) {
            std::istringstream iss(line);
            uintptr_t start, end;
            char dash;
            iss >> std::hex >> start >> dash >> end;
            library_base = start;
            break;
        }
    }

    if (library_base == 0) {
        return 0;
    }

    void *local_handle = dlopen(library_name, RTLD_NOW);
    if (!local_handle) {
        return 0;
    }

    uintptr_t local_func_address = reinterpret_cast<uintptr_t>(dlsym(local_handle, func_name));
    if (!local_func_address) {
        dlclose(local_handle);
        return 0;
    }

    func_address = local_func_address - reinterpret_cast<uintptr_t>(local_handle) + library_base;
    dlclose(local_handle);

    return func_address;
}


uintptr_t remote_function_call(pid_t target_pid, uintptr_t func_address, uintptr_t *args, size_t args_count) {
    struct user_regs_struct old_regs, new_regs;

    if (ptrace(PTRACE_GETREGS, target_pid, NULL, &old_regs) == -1) {
        return 0;
    }

    new_regs = old_regs;

    // 设置参数
    for (size_t i = 0; i < args_count && i < 6; i++) {
        new_regs.uregs[i] = args[i];
    }

    // 设置返回地址和函数地址
    new_regs.ARM_lr = new_regs.ARM_pc;
    new_regs.ARM_pc = func_address;

    if (ptrace(PTRACE_SETREGS, target_pid, NULL, &new_regs) == -1) {
        return 0;
    }

    if (ptrace(PTRACE_CONT, target_pid, NULL, NULL) == -1) {
        return 0;
    }

    int status;
    waitpid(target_pid, &status, 0);

    if (ptrace(PTRACE_GETREGS, target_pid, NULL, &new_regs) == -1) {
        return 0;
    }

    // 获取返回值
    uintptr_t return_value = new_regs.ARM_r0;

    // 恢复寄存器状态
    if (ptrace(PTRACE_SETREGS, target_pid, NULL, &old_regs) == -1) {
        return 0;
    }

    return return_value;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <target_process_name>" << std::endl;
        return 1;
    }

    pid_t target_pid = find_target_pid(argv[1]);
    if (target_pid == -1) {
        std::cerr << "Cannot find the target process: " << argv[1] << std::endl;
        return 1;
    }

    if (ptrace(PTRACE_ATTACH, target_pid, NULL, NULL) == -1) {
        std::cerr << "Cannot attach to the target process with pid: " << target_pid << std::endl;
        return 1;
    }

    int status;
    waitpid(target_pid, &status, 0);

    uintptr_t mmap_address = get_remote_func_address(target_pid, "libc.so", "mmap");
    uintptr_t dlopen_address = get_remote_func_address(target_pid, "libdl.so", "dlopen");
    uintptr_t dlclose_address = get_remote_func_address(target_pid, "libdl.so", "dlclose");

    uintptr_t mmap_args[] = {
        0, strlen(LIB_PATH) + 1, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0
    };
    uintptr_t remote_lib_path_address = remote_function_call(target_pid, mmap_address, mmap_args, sizeof(mmap_args) / sizeof(uintptr_t));

    for (size_t i = 0; i < strlen(LIB_PATH); i++) {
        ptrace(PTRACE_POKEDATA, target_pid, remote_lib_path_address + i, *reinterpret_cast<const long *>(LIB_PATH + i));
    }

    uintptr_t dlopen_args[] = {
        remote_lib_path_address, RTLD_NOW
    };
    uintptr_t lib_handle = remote_function_call(target_pid, dlopen_address, dlopen_args, sizeof(dlopen_args) / sizeof(uintptr_t));

    if (lib_handle) {
        std::cout << "Library injected successfully!" << std::endl;

        uintptr_t munmap_address = get_remote_func_address(target_pid, "libc.so", "munmap");
        uintptr_t munmap_args[] = {
            remote_lib_path_address, strlen(LIB_PATH) + 1
        };
        remote_function_call(target_pid, munmap_address, munmap_args, sizeof(munmap_args) / sizeof(uintptr_t));
    } else {
        std::cerr << "Failed to inject the library" << std::endl;
    }

    ptrace(PTRACE_DETACH, target_pid, NULL, NULL);
    return 0;
}
