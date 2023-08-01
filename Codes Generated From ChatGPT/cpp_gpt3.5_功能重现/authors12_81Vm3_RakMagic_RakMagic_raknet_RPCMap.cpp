#include <iostream>
#include <map>
#include <vector>
#include <string>

class RPCMap {
    public:
        // 构造函数
    RPCMap() {}

    // 清空所有信息
    void Clear() {
        index_map_.clear();
        name_map_.clear();
        function_ptrs_.clear();
    }

    // 通过索引获取节点
    std::pair<std::string, void*> GetNodeFromIndex(int index) const {
        if (index < 0 || index >= function_ptrs_.size()) {
            return std::make_pair("", nullptr);
        }
        auto name_it = name_map_.find(index_map_.at(index));
        return std::make_pair(name_it->second, function_ptrs_.at(index));
    }

    // 通过函数名获取节点
    std::pair<int, void*> GetNodeFromFunctionName(const std::string& name) const {
        auto index_it = index_map_.find(name);
        if (index_it == index_map_.end()) {
            return std::make_pair(-1, nullptr);
        }
        int index = index_it->second;
        return std::make_pair(index, function_ptrs_.at(index));
    }

    // 通过函数名获取索引
    int GetIndexFromFunctionName(const std::string& name) const {
        auto index_it = index_map_.find(name);
        if (index_it == index_map_.end()) {
            return -1;
        }
        return index_it->second;
    }

    // 添加函数识别码和函数指针
    bool AddIdentifierWithFunction(const std::string& name, void* function_ptr) {
        auto index_it = index_map_.find(name);
        if (index_it != index_map_.end()) {
            return false;  // 名称已经存在
        }
        int index = function_ptrs_.size();
        function_ptrs_.push_back(function_ptr);
        index_map_[name] = index;
        name_map_[index] = name;
        return true;
    }

    // 在指定索引位置添加函数识别码和函数指针
    bool AddIdentifierAtIndex(const std::string& name, int index, void* function_ptr) {
        auto index_it = index_map_.find(name);
        if (index_it != index_map_.end() || index < 0 || index > function_ptrs_.size()) {
            return false;  // 名称已经存在或者索引无效
        }
        function_ptrs_.insert(function_ptrs_.begin() + index, function_ptr);
        for (int i = index; i < function_ptrs_.size(); i++) {
            std::string& n = name_map_[i];
            index_map_[n] = i;
        }
        name_map_[index] = name;
        index_map_[name] = index;
        return true;
    }

    // 移除节点
    bool RemoveNode(const std::string& name) {
        auto index_it = index_map_.find(name);
        if (index_it == index_map_.end()) {
            return false;  // 名称不存在
        }
        int index = index_it->second;
        function_ptrs_.erase(function_ptrs_.begin() + index);
        index_map_.erase(index_it);
        name_map_.erase(index);
        for (int i = index; i < function_ptrs_.size(); i++) {
            std::string& n = name_map_[i + 1];
            index_map_[n] = i;
        }
        return true;
    }
    private:
    std::map<std::string, int> index_map_; // 函数名称和索引的映射
    std::map<int, std::string> name_map_; // 索引和函数名称的映射
    std::vector<void*> function_ptrs_; // 函数指针的向量
};

int main() {
    RPCMap rpc_map;
    // 添加一些函数
    rpc_map.AddIdentifierWithFunction("foo", reinterpret_cast<void*>(&std::cout));
    rpc_map.AddIdentifierWithFunction("bar", reinterpret_cast<void*>(&std::cin));
    rpc_map.AddIdentifierAtIndex("baz", 0, reinterpret_cast<void*>(&std::cerr));
    // 获取节点信息
    std::pair<std::string, void*> node1 = rpc_map.GetNodeFromIndex(0);
    std::pair<int, void*> node2 = rpc_map.GetNodeFromFunctionName("foo");
    int index = rpc_map.GetIndexFromFunctionName("bar");
    std::cout << "Node1: " << node1.first << ", " << node1.second << std::endl;
    std::cout << "Node2: " << node2.first << ", " << node2.second << std::endl;
    std::cout << "Index of 'bar': " << index << std::endl;
    // 移除一个函数
    rpc_map.RemoveNode("baz");
    node1 = rpc_map.GetNodeFromIndex(0);
    std::cout << "Node1 after removal: " << node1.first << ", " << node1.second << std::endl;
    return 0;
}