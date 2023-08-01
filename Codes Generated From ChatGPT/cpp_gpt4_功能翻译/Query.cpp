#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>

enum FilterOp {
    EQ,
    GT,
    GE,
    LT,
    LE,
    NE,
    ISNULL,
    NOTNULL,
    IN
};

struct FilterValue {
    FilterOp op;
    std::string value;
};

class Query {
    int version;
    std::string name;
    std::map<std::string, FilterValue> where;
    std::vector<std::string> fields;

public:
    Query() {}

    Query(std::initializer_list<std::string> names) {
        for (const auto& name : names)
            fields.push_back(name);
    }

    Query& eq(std::string name, std::string value) {
        return addFilter(name, EQ, value);
    }

    Query& gt(std::string name, std::string value) {
        return addFilter(name, GT, value);
    }

    Query& ge(std::string name, std::string value) {
        return addFilter(name, GE, value);
    }

    Query& lt(std::string name, std::string value) {
        return addFilter(name, LT, value);
    }

    Query& le(std::string name, std::string value) {
        return addFilter(name, LE, value);
    }

    Query& ne(std::string name, std::string value) {
        return addFilter(name, NE, value);
    }

    Query& isNull(std::string name) {
        return addFilter(name, ISNULL, "");
    }

    Query& isNotNull(std::string name) {
        return addFilter(name, NOTNULL, "");
    }

    Query& field(std::string name) {
        fields.push_back(name);
        return *this;
    }

    Query& field(std::initializer_list<std::string> names) {
        for (const auto& name : names)
            fields.push_back(name);
        return *this;
    }

    void addFilter(std::string name, FilterOp op, std::string value) {
        FilterValue filter;
        filter.op = op;
        filter.value = value;
        where[name] = filter;
    }

    std::map<std::string, std::string> fieldsToMap() {
        std::map<std::string, std::string> fieldsMap;
        for (const auto& field : fields)
            fieldsMap[field] = "";
        return fieldsMap;
    }
};

int main() {
    Query query({"name", "age"});
    query.eq("name", "John").lt("age", "30");

    auto fieldsMap = query.fieldsToMap();
    for (const auto& pair : fieldsMap)
        std::cout << pair.first << " : " << pair.second << std::endl;

    return 0;
}
