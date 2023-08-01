#include <lua.hpp>

namespace LuaWrapper {

    // 定义一个结构体，用于记录分配的内存块的大小和数据指针
    struct MemoryBlock {
        size_t size;
        void* data;
    };

    // 实现分配器的分配和释放操作
    class Allocator {
    public:
        // 根据新分配内存的大小，选择在已有内存块中重复利用或者重新分配内存块，并进行内存数据的拷贝和释放
        MemoryBlock allocate(size_t size);
        void deallocate(MemoryBlock& block);
    };

    // panic 函数，用于处理 Lua 函数运行时的异常情况，打印错误信息并进行长跳转
    int panic(lua_State* L);

    // init 函数，用于初始化一个 Lua 状态并加载标准库，如果初始化失败则返回 nullptr
    lua_State* init();

    // destroy 函数，用于销毁一个 Lua 状态
    void destroy(lua_State* L);

    // get_context 函数，用于从 Lua 状态中获取上下文信息
    void* get_context(lua_State* L);

    // execute 函数，用于在 Lua 状态中执行指定代码，处理异常和返回值，并支持与用户交互
    int execute(lua_State* L, const char* code);

    // 两个 Lua 风格的辅助函数，用于获取 Lua 值的地址和内部值
    template<typename T>
    T* get_pointer(lua_State* L, int index);

    template<typename T>
    T& get_value(lua_State* L, int index);
}

MemoryBlock Allocator::allocate(size_t size) {
    MemoryBlock block;
    // TODO: 实现分配器的分配操作
    return block;
}

void Allocator::deallocate(MemoryBlock& block) {
    // TODO: 实现分配器的释放操作
}

int LuaWrapper::panic(lua_State* L) {
    // 打印错误信息
    const char* message = lua_tostring(L, -1);
    std::cerr << "PANIC: unprotected error in call to Lua API (" << message << ")\n";
    // 进行长跳转
    std::longjmp(*static_cast<std::jmp_buf*>(lua_getextraspace(L)), 1);
}

lua_State* LuaWrapper::init() {
    // 创建一个 Lua 状态
    lua_State* L = luaL_newstate();
    if (L != nullptr) {
        // 加载标准库
        luaL_openlibs(L);
        // 设置 panic 函数
        lua_atpanic(L, panic);
    }
    return L;
}

void LuaWrapper::destroy(lua_State* L) {
    if (L != nullptr) {
        // 关闭 Lua 状态
        lua_close(L);
    }
}

void* LuaWrapper::get_context(lua_State* L) {
    // 获取上下文信息
    return lua_getextraspace(L);
}

int LuaWrapper::execute(lua_State* L, const char* code) {
    // 加载代码
    int result = luaL_loadstring(L, code);
    if (result == LUA_OK) {
        // 执行代码
        result = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    // 处理异常和返回值
    if (result != LUA_OK) {
        // 打印错误信息
        const char* message = lua_tostring(L, -1);
        std::cerr << message << '\n';
        // 清除栈
        lua_pop(L, 1);
    } else {
        // 获取返回值数量
        int nresults = lua_gettop(L);
        // 如果有返回值，打印返回值
        if (nresults > 0) {
            std::cout << "Returned: ";
            for (int i = 1; i <= nresults; i++) {
                const char* str = lua_tostring(L, i);
                if (str != nullptr) {
                    std::cout << str << ' ';
                }
            }
            std::cout << '\n';
            // 清除栈
            lua_pop(L, nresults);
        }
    }
    return result;
}

template<typename T>
T* LuaWrapper::get_pointer(lua_State* L, int index) {
    // 获取指针
    return static_cast<T*>(lua_touserdata(L, index));
}

template<typename T>
T& LuaWrapper::get_value(lua_State* L, int index) {
    // 获取值
    T* ptr = get_pointer<T>(L, index);
    assert(ptr != nullptr);
    return *ptr;
}


