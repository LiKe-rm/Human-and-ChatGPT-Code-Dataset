#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <iterator>
#include <algorithm>

template <typename Key, typename Value>
class AbstractMapBasedMultimap {
public:
    using Entry = std::pair<Key, Value>;
    using Collection = std::vector<Value>;
    using MapType = std::map<Key, Collection>;

    void insert(const Key& key, const Value& value) {
        map_[key].push_back(value);
    }

    Collection& get(const Key& key) {
        return map_[key];
    }

    bool remove(const Key& key, const Value& value) {
        auto iter = map_.find(key);
        if (iter != map_.end()) {
            auto& collection = iter->second;
            auto valueIter = std::find(collection.begin(), collection.end(), value);
            if (valueIter != collection.end()) {
                collection.erase(valueIter);
                return true;
            }
        }
        return false;
    }

    size_t size() const {
        size_t totalSize = 0;
        for (const auto& pair : map_) {
            totalSize += pair.second.size();
        }
        return totalSize;
    }

    void forEachEntry(const std::function<void(const Entry&)>& func) const {
        for (const auto& pair : map_) {
            for (const auto& value : pair.second) {
                func(std::make_pair(pair.first, value));
            }
        }
    }

    void forEachKey(const std::function<void(const Key&)>& func) const {
        for (const auto& pair : map_) {
            func(pair.first);
        }
    }

    void forEachValue(const std::function<void(const Value&)>& func) const {
        for (const auto& pair : map_) {
            for (const auto& value : pair.second) {
                func(value);
            }
        }
    }

    void clear() {
        map_.clear();
    }

private:
    MapType map_;
};

int main() {
    AbstractMapBasedMultimap<std::string, int> multimap;
    multimap.insert("one", 1);
    multimap.insert("one", 11);
    multimap.insert("two", 2);
    multimap.insert("three", 3);
    multimap.insert("three", 33);
    multimap.insert("three", 333);

    std::cout << "Multimap size: " << multimap.size() << std::endl;

    multimap.forEachEntry([](const AbstractMapBasedMultimap<std::string, int>::Entry& entry) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    });

    multimap.remove("one", 11);

    std::cout << "Multimap size: " << multimap.size() << std::endl;

    multimap.forEachEntry([](const AbstractMapBasedMultimap<std::string, int>::Entry& entry) {
        std::cout << "Key: " << entry.first << ", Value: " << entry.second << std::endl;
    });

    multimap.clear();

    std::cout << "Multimap size: " << multimap.size() << std::endl;

    return 0;
}
