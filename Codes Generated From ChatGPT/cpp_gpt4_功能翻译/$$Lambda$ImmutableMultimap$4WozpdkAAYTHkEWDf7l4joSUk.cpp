#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <functional>

template <typename K, typename V>
class Multimap {
public:
    using KeyValue = std::pair<K, V>;
    using KeyValues = std::vector<KeyValue>;
    using InternalMap = std::map<K, std::vector<V>>;

    void insert(const K& key, const V& value) {
        data_[key].push_back(value);
    }

    KeyValues entries() const {
        KeyValues result;
        for (const auto& [key, values] : data_) {
            for (const auto& value : values) {
                result.emplace_back(key, value);
            }
        }
        return result;
    }

    std::vector<V> get(const K& key) const {
        auto it = data_.find(key);
        if (it != data_.end()) {
            return it->second;
        }
        return std::vector<V>();
    }

    size_t size() const {
        size_t total_size = 0;
        for (const auto& [key, values] : data_) {
            total_size += values.size();
        }
        return total_size;
    }

    void clear() {
        data_.clear();
    }

private:
    InternalMap data_;
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Multimap<K, V>& multimap) {
    os << "{";
    auto entries = multimap.entries();
    for (size_t i = 0; i < entries.size(); ++i) {
        os << entries[i].first << ": " << entries[i].second;
        if (i < entries.size() - 1) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

int main() {
    Multimap<std::string, int> multimap;

    multimap.insert("a", 1);
    multimap.insert("b", 2);
    multimap.insert("a", 3);
    multimap.insert("c", 4);
    multimap.insert("b", 5);
    multimap.insert("a", 6);

    std::cout << "Multimap: " << multimap << std::endl;

    std::cout << "Size: " << multimap.size() << std::endl;

    std::cout << "Values for key 'a': ";
    for (const auto& value : multimap.get("a")) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Values for key 'b': ";
    for (const auto& value : multimap.get("b")) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Values for key 'c': ";
    for (const auto& value : multimap.get("c")) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Clearing the multimap." << std::endl;
    multimap.clear();
    std::cout << "Size after clearing: " << multimap.size() << std::endl;

    return 0;
}
