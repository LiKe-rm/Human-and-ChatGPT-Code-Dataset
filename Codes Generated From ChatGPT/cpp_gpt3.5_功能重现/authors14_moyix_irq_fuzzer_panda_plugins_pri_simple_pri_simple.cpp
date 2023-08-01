#include <panda/plugin.h>
#include <panda/plugin_plugin.h>
#include <panda/common.h>

// Define a macro
#define PLUGIN_NAME "MyPlugin"

// Define functions to initialize and uninitialize the plugin
bool init_plugin(void *self) {
    panda_require("osi");
    printf("%s plugin loaded!\n", PLUGIN_NAME);
    return true;
}

void uninit_plugin(void *self) {
    printf("%s plugin unloaded!\n", PLUGIN_NAME);
}

// Define functions to handle various events that occur during program execution
void on_line_change(CPUState *env, TranslationBlock *tb, uint64_t pc) {
    printf("on_line_change called!\n");
    // TODO: iterate through live variables at current program counter and print information about them
}

void on_fn_start(CPUState *env, target_ulong pc) {
    printf("on_fn_start called!\n");
    // TODO: iterate through live variables at current program counter and print information about them
}

bool virt_mem_helper(CPUState *env, target_ulong address, uint8_t size, bool is_write) {
    printf("virt_mem_helper called!\n");
    // TODO: determine if access to virtual memory is valid and print information about associated symbol
    return true;
}

bool virt_mem_read(CPUState *env, target_ulong address, uint8_t size, void *buf) {
    printf("virt_mem_read called!\n");
    // TODO: implement pre-read operation on virtual memory
    return true;
}

bool virt_mem_write(CPUState *env, target_ulong address, uint8_t size, void *buf) {
    printf("virt_mem_write called!\n");
    // TODO: implement pre-write operation on virtual memory
    return true;
}

// Register plugin callbacks with PANDA system
static panda_arg_list my_plugin_args = {
    { "my_plugin_arg", NULL, "My Plugin Argument" }
};

static panda_plugin::PluginStateInitializer init_handler = {
    .panda_api_version = PANDA_PLUGIN_CURRENT_VERSION,
    .name = PLUGIN_NAME,
    .version = "1.0",
    .init = init_plugin,
    .uninit = uninit_plugin,
    .on_line_change = on_line_change,
    .on_fn_start = on_fn_start,
    .virt_mem_helper = virt_mem_helper,
    .virt_mem_read = virt_mem_read,
    .virt_mem_write = virt_mem_write,
    .args = &my_plugin_args,
    .argc = 1,
    .options = {},
    .default_options = {}
};

// Initialize PRI and DWARF APIs for x86-32 architecture
static panda_plugin::PluginStateInitializer pri_init_handler = {
    .panda_api_version = PANDA_PLUGIN_CURRENT_VERSION,
    .name = "pri_init",
    .version = "1.0",
    .init = NULL,
    .uninit = NULL,
    .args = NULL,
    .argc = 0,
    .options = {},
    .default_options = {}
};

#ifdef TARGET_I386
extern "C" PANDA_INTERNAL void init_plugin() {
    panda_plugin_register_state_initializer(&init_handler);
    panda_plugin_register_state_initializer(&pri_init_handler);
}
#else
PANDA_EXPORT void init_plugin(void *self) {
    panda_plugin_register_state_initializer(&init_handler);
}
#endif
