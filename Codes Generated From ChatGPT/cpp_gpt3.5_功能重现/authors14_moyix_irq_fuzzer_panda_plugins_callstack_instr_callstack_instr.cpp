#include "panda/plugin.h"
#include "panda/plugin_plugin.h"
#include "panda/rr/rr.h"
#include "callstack.h"

static CallStack *callstack;

static void on_call(CPUState *cpu, target_ulong pc) {
    callstack->push(pc);
}

static void on_return(CPUState *cpu) {
    callstack->pop();
}

static void on_init_plugin(void *self) {
    callstack = new CallStack();
}

static void on_unload_plugin(void *self) {
    delete callstack;
}

static void on_panda_before_exec_tb(CPUState *cpu, TranslationBlock *tb) {
    for (int i = 0; i < tb->size; i++) {
        target_ulong pc = tb->pc + i;
        if (is_call_insn(cpu, pc)) {
            on_call(cpu, pc);
        }
        if (is_return_insn(cpu, pc)) {
            on_return(cpu);
        }
    }
}

static void on_panda_after_mprotect(target_ulong start, size_t len, int prot) {
    if (callstack) {
        callstack->flush();
    }
}

extern "C" {
    void init_plugin(void *self) {
        panda_require("rr");
        panda_cb pcb = {
            .panda_before_exec_tb = on_panda_before_exec_tb,
            .panda_after_mprotect = on_panda_after_mprotect,
            .on_init = on_init_plugin,
            .on_unload = on_unload_plugin,
        };
        panda_register_callback(self, PANDA_CB_ALL, pcb);
    }
}
/*每当执行调用指令时都会调用该函数，并使用类的函数将当前程序计数器 （pc） 添加到调用堆栈中。on_call()push()CallStack

同样，每当执行返回指令时都会调用该函数，并使用类的函数从调用堆栈中删除最新的 pc。on_return()pop()CallStack

该函数通过创建类的新实例来初始化调用堆栈。on_init_plugin()CallStack

该函数在卸载插件时删除调用堆栈实例。on_unload_plugin()

在执行每个转换块 （TB） 之前调用该函数。它循环遍历 TB 中的指令，并检查每个指令是调用指令还是返回指令。如果是这样，它将调用相应的函数来更新调用堆栈。on_panda_before_exec_tb()

在进行内存保护更改后调用该函数。它刷新调用堆栈以防止过时的指针保留在堆栈上。on_panda_after_mprotect()

最后，该函数是插件的入口点。它使用该函数向 PANDA 注册插件回调。init_plugin()panda_register_callback()

*/