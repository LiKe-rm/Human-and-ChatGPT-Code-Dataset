#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class NamePath {
    std::string name;
    NamePath* parent;
    NamePath* next;

public:
    explicit NamePath(const std::string& name) : name(name), parent(nullptr), next(nullptr) {}

    std::string getNameWithParent() {
        std::ostringstream sb;
        if(parent != nullptr) {
            sb << parent->getNameWithParent();
        }
        if(!sb.str().empty()) {
            sb << ".";
        }
        sb << name;

        return sb.str();
    }

    std::string toString() {
        return name;
    }

    bool hasNext() {
        return next != nullptr;
    }

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static bool contains(const std::string& s, char ch) {
        return s.find(ch) != std::string::npos;
    }

    static NamePath* createNamePath(const std::string& name) {
        if (contains(name, '.')) {
            std::vector<std::string> arr = split(name, '.');
            NamePath* namePath = new NamePath(arr[0]);
            if (arr.size() > 1) {
                NamePath* first = namePath;
                for (int i=1; i<arr.size(); i++) {
                    NamePath* next = new NamePath(arr[i]);
                    first->next = next;
                    next->parent = first;
                    first = next;
                }
            }
            return namePath;
        } else {
            return new NamePath(name);
        }
    }
};

int main() {
    NamePath* namePath = NamePath::createNamePath("test.name.path");
    std::cout << "Name with parent: " << namePath->getNameWithParent() << std::endl;

    while (namePath->hasNext()) {
        namePath = namePath->next;
        std::cout << "Next name with parent: " << namePath->getNameWithParent() << std::endl;
    }

    return 0;
}
