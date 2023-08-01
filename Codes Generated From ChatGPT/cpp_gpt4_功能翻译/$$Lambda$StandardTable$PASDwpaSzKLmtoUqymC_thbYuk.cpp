#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <iterator>
#include <utility>

class StandardTable {
public:
    using ValueType = std::pair<std::string, std::map<std::string, int>>;
    using MapType = std::map<std::string, std::map<std::string, int>>;

    StandardTable() = default;
    ~StandardTable() = default;

    void insert(const std::string& key, const std::map<std::string, int>& value) {
        table[key] = value;
    }

    std::vector<ValueType> apply() {
        std::vector<ValueType> result;

        for (auto& entry : table) {
            auto transformedEntry = transformEntry(entry);
            result.push_back(transformedEntry);
        }

        return result;
    }

private:
    MapType table;

    ValueType transformEntry(const ValueType& entry) {
        std::map<std::string, int> transformedMap;

        for (const auto& subEntry : entry.second) {
            transformedMap[subEntry.first] = subEntry.second * 2;
        }

        return {entry.first, transformedMap};
    }
};

int main() {
    StandardTable table;

    table.insert("Row1", {{"Col1", 1}, {"Col2", 2}, {"Col3", 3}});
    table.insert("Row2", {{"Col1", 4}, {"Col2", 5}, {"Col3", 6}});
    table.insert("Row3", {{"Col1", 7}, {"Col2", 8}, {"Col3", 9}});

    auto result = table.apply();

    for (const auto& entry : result) {
        std::cout << "Key: " << entry.first << std::endl;

        for (const auto& subEntry : entry.second) {
            std::cout << "  SubKey: " << subEntry.first << " Value: " << subEntry.second << std::endl;
        }
    }

    return 0;
}
