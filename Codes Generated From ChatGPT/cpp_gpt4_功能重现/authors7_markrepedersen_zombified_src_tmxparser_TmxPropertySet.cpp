#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <stdexcept>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class PropertySet {
private:
    unordered_map<string, string> properties;

    template <typename T>
    T convert(const string& value) const {
        T result;
        stringstream ss(value);
        ss >> result;
        if (ss.fail()) {
            throw runtime_error("Failed to convert value.");
        }
        return result;
    }

public:
    PropertySet() = default;
    ~PropertySet() = default;

    void parse(const XMLNode* node) {
        properties.clear();
        if (node == nullptr) {
            return;
        }

        const XMLElement* propertiesElement = node->FirstChildElement("properties");
        if (propertiesElement == nullptr) {
            return;
        }

        const XMLElement* propertyElement = propertiesElement->FirstChildElement("property");
        while (propertyElement != nullptr) {
            const char* name = propertyElement->Attribute("name");
            const char* value = propertyElement->Attribute("value");

            if (name != nullptr && value != nullptr) {
                properties[name] = value;
            }

            propertyElement = propertyElement->NextSiblingElement("property");
        }
    }

    bool hasProperty(const string& name) const {
        return properties.find(name) != properties.end();
    }

    string getString(const string& name) const {
        auto it = properties.find(name);
        if (it != properties.end()) {
            return it->second;
        }
        throw runtime_error("Property not found.");
    }

    int getInt(const string& name) const {
        return convert<int>(getString(name));
    }

    float getFloat(const string& name) const {
        return convert<float>(getString(name));
    }

    double getDouble(const string& name) const {
        return convert<double>(getString(name));
    }

    bool getBool(const string& name) const {
        string value = getString(name);
        if (value == "true" || value == "1") {
            return true;
        } else if (value == "false" || value == "0") {
            return false;
        }
        throw runtime_error("Failed to convert value to bool.");
    }
};
