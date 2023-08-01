#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <utility>
#include <stdexcept>

// 定义特殊按键常量
enum class SpecialKey {
    None = 0,
    Ctrl = 1 << 0,
    Shift = 1 << 1,
    Alt = 1 << 2
};

inline SpecialKey operator|(SpecialKey a, SpecialKey b) {
    return static_cast<SpecialKey>(static_cast<int>(a) | static_cast<int>(b));
}

class KeyMap {
public:
    using Key = std::pair<char, SpecialKey>;
    using Action = std::function<void()>;

    // 默认键映射
    static std::map<Key, Action> MapDefault;

    // 添加映射
    void addMapping(char key, SpecialKey modifier, Action action) {
        Key k = std::make_pair(key, modifier);
        keyMap[k] = action;
    }

    // 执行映射操作
    void execute(char key, SpecialKey modifier) {
        Key k = std::make_pair(key, modifier);
        auto it = keyMap.find(k);

        if (it != keyMap.end()) {
            it->second();
        } else {
            throw std::runtime_error("No mapping found for the given key combination");
        }
    }

private:
    std::map<Key, Action> keyMap;
};

// 初始化默认键映射
std::map<KeyMap::Key, KeyMap::Action> KeyMap::MapDefault = {
    {{'C', SpecialKey::Ctrl}, []() { std::cout << "Ctrl+C: Copy" << std::endl; }},
    {{'V', SpecialKey::Ctrl}, []() { std::cout << "Ctrl+V: Paste" << std::endl; }},
    {{'X', SpecialKey::Ctrl}, []() { std::cout << "Ctrl+X: Cut" << std::endl; }},
    {{'Z', SpecialKey::Ctrl}, []() { std::cout << "Ctrl+Z: Undo" << std::endl; }},
    {{'Y', SpecialKey::Ctrl}, []() { std::cout << "Ctrl+Y: Redo" << std::endl; }}
};

int main() {
    try {
        KeyMap keyMap;

        // 使用默认键映射
        keyMap = KeyMap::MapDefault;

        // 添加自定义映射
        keyMap.addMapping('A', SpecialKey::Ctrl | SpecialKey::Shift, []() {
            std::cout << "Ctrl+Shift+A: Custom action" << std::endl;
        });

        // 执行映射操作
        keyMap.execute('C', SpecialKey::Ctrl);
        keyMap.execute('V', SpecialKey::Ctrl);
        keyMap.execute('X', SpecialKey::Ctrl);
        keyMap.execute('Z', SpecialKey::Ctrl);
        keyMap.execute('Y', SpecialKey::Ctrl);
        keyMap.execute('A', SpecialKey::Ctrl | SpecialKey::Shift);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
