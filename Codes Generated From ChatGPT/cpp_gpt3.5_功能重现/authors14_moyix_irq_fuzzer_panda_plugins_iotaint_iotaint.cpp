#include <stdio.h>
#include <string.h>
#include <set>
#include "panda/plugin.h"
#include "panda/plugin_plugin.h"
#include "panda/plog.h"
#include "taint2/taint2.h"
#include "loadstate/loadstate.h"

static Taint2 taint;
static std::set<uint32_t> seen_io_addrs;

static void on_taint_mmio_read(CPUState *env, target_ulong pc, target_ulong addr, size_t size, void *buf, void *opaque) {
    if (seen_io_addrs.find(addr) == seen_io_addrs.end()) {
        seen_io_addrs.insert(addr);
        printf("Tainted IO address: 0x%x\n", addr);
    }

    uint64_t label = taint.get_unique_label();
    taint.add_label_range(env, addr, size, label);
}

static void on_tainted_pc(CPUState *env, target_ulong pc, target_ulong tainted_pc, void *opaque) {
    printf("Jump to tainted address: 0x%x\n", tainted_pc);
}

static void after_machine_init(void *opaque) {
    const char *state_file = panda_parse_string_opt("state", "state file to load", NULL);
    const char *int_opt = panda_parse_string_opt("int", "interrupt to trigger", NULL);

    if (state_file) {
        LoadState ls;
        ls.load(state_file);
        ls.load_cpu_state();
    }

    taint.enable();
    panda_cb_add_taint_mmio_read(on_taint_mmio_read, NULL);
    panda_cb_add_tainted_pc(on_tainted_pc, NULL);

    if (int_opt) {
        uint32_t int_num = strtoul(int_opt, NULL, 0);
        panda_interrupt(int_num);
    }
}

static bool init_plugin(void *self) {
    panda_arg_list *args = panda_get_args("ioread");
    if (!args) {
        printf("Failed to get ioread plugin args\n");
        return false;
    }

    panda_cb pcb;
    pcb.after_machine_init = after_machine_init;
    panda_register_callback(self, PANDA_CB_AFTER_MACHINE_INIT, pcb);

    panda_cb pcb_ioread;
    pcb_ioread.taint_mmio_read = on_taint_mmio_read;
    panda_register_callback(self, PANDA_CB_TAINT_MMIO_READ, pcb_ioread);

    return true;
}

static void uninit_plugin(void *self) {}

PANDA_PLUGIN_API int init_plugin_panda_plugin_ioread(void *self) {
    return init_plugin(self) ? PANDA_PLUGIN_RET_OK : PANDA_PLUGIN_RET_ERR;
}
