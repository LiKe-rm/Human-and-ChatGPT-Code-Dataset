#include <map>
#include <string>
#include <vector>
#include <panda/plugin.h>
#include <panda/plugin_plugin.h>
#include <panda/panda.h>
#include <panda/rr/rr.h>

static std::map<uint64_t, std::string> fd_to_filename_map;
static std::map<uint64_t, std::string> process_map;

static void on_library_load(const char* filename, uint64_t base_address, uint64_t size) {
    // Implement your logic here for tracking library loads and associating them with processes
}

static void on_mmap_return(CPUState* cpu, target_ulong retaddr, uint64_t fd, uint64_t addr, uint64_t len, uint64_t prot, uint64_t flags, uint64_t pgoff) {
    if (fd >= 0 && prot & PROT_EXEC) {
        const char* filename = nullptr;
        // Implement your logic here for retrieving the filename associated with the file descriptor
        on_library_load(filename, addr, len);
    }
}

static void on_process_change(CPUState* cpu, uint64_t pid) {
    process_map[cpu->get_pc()] = std::to_string(pid);
}

static void on_library_load_callback(const char* filename, uint64_t base_address, uint64_t size) {
    // Implement your logic here for handling library loads
}

static void on_mmap_return_callback(CPUState* cpu, target_ulong retaddr, uint64_t fd, uint64_t addr, uint64_t len, uint64_t prot, uint64_t flags, uint64_t pgoff) {
    // Implement your logic here for handling mmap returns
}

static void on_process_change_callback(CPUState* cpu, uint64_t pid) {
    // Implement your logic here for handling process changes
}

extern "C" {
    void panda_plugin_init(void *self) {
        panda_require("rr");
        panda_enable_memcb();
        panda_cb pcb = {
            .process_change = on_process_change,
            .linux_mmap_pgoff_return = on_mmap_return
        };
        panda_register_callback(self, PANDA_CB_ALL, pcb);

        panda_plugin_register_function(self, "on_library_load_callback", (void*)on_library_load_callback);
        panda_plugin_register_function(self, "on_mmap_return_callback", (void*)on_mmap_return_callback);
        panda_plugin_register_function(self, "on_process_change_callback", (void*)on_process_change_callback);
    }

    int init_plugin(void* self) {
        return 0;
    }
}
