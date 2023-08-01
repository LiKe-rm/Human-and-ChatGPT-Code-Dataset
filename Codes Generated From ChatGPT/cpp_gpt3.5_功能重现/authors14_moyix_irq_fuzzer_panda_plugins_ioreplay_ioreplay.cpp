// Authors: [Author Name(s)]
// License: [License Type]

#include <deque>
#include <panda/plugin.h>
#include <panda/loadstate.h>

#define MAX_BLOCKS 1000

static std::set<uint64_t> ioaddrs_seen;
static std::deque<uint8_t> iovals_to_replay;
static int label_number = 0;
static bool interrupt_flag = false;
static bool fiq_flag = false;
static bool replay_debug_flag = false;

static uint8_t ioread(panda_state *s, target_ulong addr, int size) {
    uint8_t val;
    if (!iovals_to_replay.empty()) {
        val = iovals_to_replay.front();
        iovals_to_replay.pop_front();
    } else {
        std::ifstream urandom("/dev/urandom", std::ios::binary);
        urandom.read(reinterpret_cast<char*>(&val), size);
    }
    ioaddrs_seen.insert(addr);
    return val;
}

static void before_block_exec(CPUState *cpu, TranslationBlock *tb) {
    label_number++;
    if (label_number >= MAX_BLOCKS) {
        panda_disable();
    }
}

static void after_machine_init(panda_state *s) {
    if (interrupt_flag) {
        panda_enable_interrupt();
    }
}

static void init_plugin(void *self) {
    panda_require("loadstate");

    panda_cb pcb;

    pcb.before_block_exec = before_block_exec;
    panda_register_callback(self, PANDA_CB_BEFORE_BLOCK_EXEC, pcb);

    pcb.after_machine_init = after_machine_init;
    panda_register_callback(self, PANDA_CB_AFTER_MACHINE_INIT, pcb);

    pcb.io_before_read = ioread;
    panda_register_callback(self, PANDA_CB_IO_BEFORE_READ, pcb);

    int argc;
    const char **argv;
    panda_arg_list(&argc, &argv);

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-iovals") {
            i++;
            while (i < argc && argv[i][0] != '-') {
                uint8_t val = std::stoi(argv[i]);
                iovals_to_replay.push_back(val);
            }
        } else if (std::string(argv[i]) == "-memcpusave") {
            i++;
            const char* filename = argv[i];
            panda_load_vm_state(filename);
        } else if (std::string(argv[i]) == "-interrupt") {
            interrupt_flag = true;
        } else if (std::string(argv[i]) == "-fiq") {
            fiq_flag = true;
        } else if (std::string(argv[i]) == "-replay_debug") {
            replay_debug_flag = true;
        }
    }
}

static void uninit_plugin(void *self) {
    // Cleanup code (if any)
}

