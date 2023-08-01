#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>

class MyClass {
public:
    std::string name;
    MyClass(const std::string& name) : name(name) {}
};

class ClassCache {
private:
    std::unordered_map<std::string, MyClass> classesCache;
public:
    void add(const std::string& className, const MyClass& clz) {
        classesCache[className] = clz;
    }
    MyClass findClass(const std::string& name) {
        if (classesCache.find(name) != classesCache.end()) {
            return classesCache[name];
        }
        else {
            throw std::runtime_error("Class not found");
        }
    }
};

int main() {
    ClassCache cache;
    MyClass myClass("Test");
    cache.add("Test", myClass);
    try {
        MyClass foundClass = cache.findClass("Test");
        std::cout << "Found class: " << foundClass.name << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
