#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

// 符号信息结构体
struct SymbolInfo {
    void* address;  // 符号地址
    void* originalImplementation;  // 符号原始实现
    void* hookImplementation;  // Hook后的实现
    SymbolInfo* next;  // 链表指针，指向同一符号的下一个被Hook的实例
};

// Hook实例结构体
struct HookInstance {
    SymbolInfo* symbolInfo;  // 指向1对象的指针
    void* hookImplementation;  // Hook后的实现
    void* originalImplementation;  // 原始实现的指针
    HookInstance* next;  // 链表指针，指向同一符号的下一个Hook实例
};

// 动态链接库信息结构体
struct LibInfo {
    void* baseAddress;  // 基地址
    std::unordered_map<std::string, SymbolInfo> symbolTable;  // 动态符号表
    std::unordered_map<std::string, void*> stringTable;  // 字符串表
    std::unordered_map<void*, void*> relocationTable;  // 重定位表

    // 对一个动态链接库中的符号进行Hook操作
    void applyHooks() {
        for (auto& p : symbolTable) {
            SymbolInfo& symbolInfo = p.second;
            void** symbolAddress = static_cast<void**>(symbolInfo.address);
            void* originalImplementation = *symbolAddress;
            symbolInfo.originalImplementation = originalImplementation;

            // 修改符号实现为Hook实现
            *symbolAddress = symbolInfo.hookImplementation;

            // 在Hook实例链表中添加一个Hook实例
            HookInstance* hookInstance = new HookInstance;
            hookInstance->symbolInfo = &symbolInfo;
            hookInstance->hookImplementation = symbolInfo.hookImplementation;
            hookInstance->originalImplementation = originalImplementation;
            hookInstance->next = symbolInfo.next;
            symbolInfo.next = hookInstance;
        }
    }
};

// HookManager类
class HookManager {
public:
    // 向HookManager中添加一个动态链接库
    void addLibrary(void* baseAddress, const std::unordered_map<std::string, void*>& symbols) {
        LibInfo libInfo;
        libInfo.baseAddress = baseAddress;
        for (auto& p : symbols) {
            SymbolInfo symbolInfo;
            symbolInfo.address = p.second;
            symbolInfo.originalImplementation = nullptr;
            symbolInfo.hookImplementation = nullptr;
            symbolInfo.next = nullptr;
            libInfo.symbolTable.emplace(p.first, symbolInfo);
        }
        libraries.emplace_back(libInfo);
    }

    // 从HookManager中删除一个动态链接库
    void removeLibrary(void* baseAddress) {
        libraries.erase(std::remove_if(libraries.begin(), libraries.end(),
            [baseAddress](const LibInfo& libInfo) { return libInfo.baseAddress == baseAddress; }),
            libraries.end());
    }

    // 创建一个HookInstance对象，表示对一个特定的符号进行Hook
    HookInstance* createHookInstance(const std::string& symbolName, void* hookImplementation) {
        HookInstance* hookInstance = new HookInstance;
        for (auto& lib : libraries) {
            auto it = lib.symbolTable.find(symbolName);
            if (it != lib.symbolTable.end()) {
                SymbolInfo& symbolInfo = it->second;
                if (symbolInfo.hookImplementation == nullptr) {
                    // 如果该符号还没有被Hook，则在动态链接库中进行Hook操作
                    symbolInfo.hookImplementation = hookImplementation;
                    lib.applyHooks();
                }
                hookInstance->symbolInfo = &symbolInfo;
                hookInstance->hookImplementation = hookImplementation;
                hookInstance->originalImplementation = symbolInfo.originalImplementation;
                hookInstance->next = nullptr;

                // 在Hook实例链表中添加一个Hook实例
                HookInstance** ppHookInstance = &(symbolInfo.next);
                while (*ppHookInstance != nullptr) {
                    ppHookInstance = &((*ppHookInstance)->next);
                }
                *ppHookInstance = hookInstance;
                break;
            }
        }
        return hookInstance;
    }

    // 删除一个HookInstance对象
    void removeHookInstance(HookInstance* hookInstance) {
        SymbolInfo* symbolInfo = hookInstance->symbolInfo;
        HookInstance** ppHookInstance = &(hookInstance->next);
        while (*ppHookInstance != nullptr) {
            if (*ppHookInstance == hookInstance) {
                *ppHookInstance = hookInstance->next;
                break;
            }
            ppHookInstance = &((*ppHookInstance)->next);
        }
        delete hookInstance;
    }

    // 对所有已添加的动态链接库中的符号进行Hook操作
    void applyHooks() {
        for (auto& lib : libraries) {
            lib.applyHooks();
        }
    }
private:
    std::vector<LibInfo> libraries; // 动态链接库信息列表
};
