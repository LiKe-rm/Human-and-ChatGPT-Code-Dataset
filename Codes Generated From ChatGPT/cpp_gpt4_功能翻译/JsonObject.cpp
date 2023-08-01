#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <exception>

class JsonObject {
    nlohmann::json jsonObj;

public:
    explicit JsonObject(const nlohmann::json& json) : jsonObj(json) {}

    static std::string toJSONString(const nlohmann::json& object) {
        try {
            return object.dump();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return "null";
        }
    }

    static nlohmann::json parseObject(const std::string& json) {
        try {
            return nlohmann::json::parse(json);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return nlohmann::json::object();
        }
    }

    static JsonObject parseObjectToObject(const std::string& json) {
        try {
            return JsonObject(nlohmann::json::parse(json));
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return JsonObject(nlohmann::json::object());
        }
    }

    int getInteger(const std::string& name) {
        try {
            return jsonObj[name].get<int>();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }

    long getLong(const std::string& name) {
        try {
            return jsonObj[name].get<long>();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }

    std::string getString(const std::string& name) {
        try {
            return jsonObj[name].get<std::string>();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return "";
        }
    }

    JsonObject getJsonObject(const std::string& name) {
        try {
            return JsonObject(jsonObj[name]);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return JsonObject(nlohmann::json::object());
        }
    }

    std::map<std::string, nlohmann::json> getMap(const std::string& name) {
        try {
            return jsonObj[name].get<std::map<std::string, nlohmann::json>>();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return std::map<std::string, nlohmann::json>();
        }
    }
};

int main() {
    nlohmann::json json = {
        {"name", "John"},
        {"age", 30},
        {"city", "New York"},
        {"numbers", {1, 2, 3}},
        {"details", {{"height", 180}, {"weight", 70}}}
    };

    std::string jsonString = JsonObject::toJSONString(json);
    std::cout << "JSON string: " << jsonString << std::endl;

    nlohmann::json parsedJson = JsonObject::parseObject(jsonString);
    std::cout << "Parsed JSON: " << parsedJson.dump() << std::endl;

    JsonObject jsonObject = JsonObject::parseObjectToObject(jsonString);
    
    int age = jsonObject.getInteger("age");
    std::cout << "Age: " << age << std::endl;

    long defaultLong = jsonObject.getLong("default");
    std::cout << "Default (long): " << defaultLong << std::endl;

    std::string name = jsonObject.getString("name");
    std::cout << "Name: " << name << std::endl;

    std::string defaultString = jsonObject.getString("default");
    std::cout << "Default (string): " << defaultString << std::endl;

    JsonObject details = jsonObject.getJsonObject("details");
    int height = details.getInteger("height");
    std::cout << "Height: " << height << std::endl;

    std::map<std::string, nlohmann::json> detailsMap = details.getMap("");
    for(auto& [key, value] : detailsMap) {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }

    return 0;
}

