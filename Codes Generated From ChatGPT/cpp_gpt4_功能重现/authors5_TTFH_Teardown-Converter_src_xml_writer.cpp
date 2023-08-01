#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
#include <memory>

class XmlElement {
public:
    XmlElement(const std::string& name)
        : name(name) {}

    void addAttribute(const std::string& key, const std::string& value) {
        attributes[key] = value;
    }

    void addChild(std::shared_ptr<XmlElement> child) {
        children.push_back(child);
    }

    void removeChild(std::shared_ptr<XmlElement> child) {
        children.erase(std::remove(children.begin(), children.end(), child), children.end());
    }

    void moveTo(std::shared_ptr<XmlElement> newParent) {
        if (parent) {
            parent->removeChild(shared_from_this());
        }
        newParent->addChild(shared_from_this());
        parent = newParent;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "<" << name;

        for (const auto& attr : attributes) {
            ss << " " << attr.first << "=\"" << attr.second << "\"";
        }

        if (children.empty()) {
            ss << "/>";
        } else {
            ss << ">";
            for (const auto& child : children) {
                ss << child->toString();
            }
            ss << "</" << name << ">";
        }

        return ss.str();
    }

private:
    std::string name;
    std::map<std::string, std::string> attributes;
    std::vector<std::shared_ptr<XmlElement>> children;
    std::shared_ptr<XmlElement> parent;
};

class XmlFile {
public:
    XmlFile(const std::string& rootName)
        : root(std::make_shared<XmlElement>(rootName)) {}

    std::shared_ptr<XmlElement> getRoot() const {
        return root;
    }

    std::string toString() const {
        return root->toString();
    }

private:
    std::shared_ptr<XmlElement> root;
};

std::string FloatToString(float value) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(6) << value;
    std::string s = ss.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s.back() == '.') {
        s.pop_back();
    }
    return s;
}

int main() {
    XmlFile xmlFile("Scene");
    auto root = xmlFile.getRoot();

    auto element1 = std::make_shared<XmlElement>("Element1");
    element1->addAttribute("boolAttribute", "true");
    element1->addAttribute("floatAttribute", FloatToString(3.14159f));
    element1->addAttribute("vectorAttribute", "1.0 2.0 3.0");
    element1->addAttribute("colorAttribute", "255 0 0");

    auto element2 = std::make_shared<XmlElement>("Element2");
    element2->addAttribute("boolAttribute", "false");
    element2->addAttribute("floatAttribute", FloatToString(2.71828f));
    element2->addAttribute("vectorAttribute", "4.0 5.0 6.0");
    element2->addAttribute("colorAttribute", "0 255 0");

    root->addChild(element1);
    root->addChild(element2);

    std::cout << xmlFile.toString() << std::endl;

    element2->moveTo(element1);

    std::cout << xmlFile.toString() << std::endl;

    return 0;
}
