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
/*ÿ��ִ�е���ָ��ʱ������øú�������ʹ����ĺ�������ǰ��������� ��pc�� ��ӵ����ö�ջ�С�on_call()push()CallStack

ͬ����ÿ��ִ�з���ָ��ʱ������øú�������ʹ����ĺ����ӵ��ö�ջ��ɾ�����µ� pc��on_return()pop()CallStack

�ú���ͨ�����������ʵ������ʼ�����ö�ջ��on_init_plugin()CallStack

�ú�����ж�ز��ʱɾ�����ö�ջʵ����on_unload_plugin()

��ִ��ÿ��ת���� ��TB�� ֮ǰ���øú�������ѭ������ TB �е�ָ������ÿ��ָ���ǵ���ָ��Ƿ���ָ����������������������Ӧ�ĺ��������µ��ö�ջ��on_panda_before_exec_tb()

�ڽ����ڴ汣�����ĺ���øú�������ˢ�µ��ö�ջ�Է�ֹ��ʱ��ָ�뱣���ڶ�ջ�ϡ�on_panda_after_mprotect()

��󣬸ú����ǲ������ڵ㡣��ʹ�øú����� PANDA ע�����ص���init_plugin()panda_register_callback()

*/