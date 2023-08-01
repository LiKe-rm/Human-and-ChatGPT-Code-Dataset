#include <panda/plugin.h>
#include <panda/plugin_plugin.h>
#include <panda/common.h>

static target_ulong asid;

static void log_source_info(CPUState *cpu, target_ulong pc) {
    TranslationBlock *tb = tb_find_fast(cpu, pc);
    if (tb != NULL && tb->pc == pc && tb->se_tb != NULL) {
        se_tb_t *tbdata = tb->se_tb;
        const TranslationBlock *se_tb = tbdata->last_tb;
        const TranslationBlock *se_tb_end = tbdata->last_tb_end;
        while (se_tb != se_tb_end) {
            PDBG("%s:%d\n", se_tb->filename, se_tb->line_num);
            se_tb = se_tb->se_tb_next;
        }
    } else {
        printf("No source-level debugging information available for PC %lx\n", pc);
    }
}

static void on_block_executed(CPUState *cpu, TranslationBlock *tb) {
    if (tb->pc != tb->cs_base) {
        log_source_info(cpu, tb->pc);
    }
}

static void init_plugin(void *self, panda_cb_t *cb) {
    int argc = 0;
    const char **argv = panda_get_argv("asid", &argc);
    if (argc != 1) {
        printf("Usage: -p %s:asid=<ASID>\n", self);
        return;
    }
    asid = strtoul(argv[0], NULL, 16);
    panda_enable_precise_pc();
    panda_cb pcb = {
        .on_block_executed = on_block_executed
    };
    panda_register_callback(self, PANDA_CB_BLOCK_EXEC, pcb);
}

static void uninit_plugin(void *self) {
    // Do nothing
}

PANDA_PLUGIN_API int init_plugin(void *self) {
    panda_require("PRI");
    return panda_register_plugin(self, "trace_source", "Trace execution with source-level debugging information", init_plugin, uninit_plugin);
}
