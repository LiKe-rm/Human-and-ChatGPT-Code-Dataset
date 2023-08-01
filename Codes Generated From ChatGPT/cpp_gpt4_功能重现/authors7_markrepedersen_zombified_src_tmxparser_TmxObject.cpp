#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <cmath>
#include <stdexcept>

// 用于解析XML文件的库
#include <tinyxml2.h>

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getRotation() const { return rotation; }
    std::string getPropertyValue(const std::string& propertyName) const {
        auto it = properties.find(propertyName);
        return (it != properties.end()) ? it->second : "";
    }

protected:
    std::string name;
    std::string type;
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float rotation = 0.0f;
    std::map<std::string, std::string> properties;

    void parseAttributes(const tinyxml2::XMLElement* objectElement) {
        if (objectElement->Attribute("name")) {
            name = objectElement->Attribute("name");
        }
        if (objectElement->Attribute("type")) {
            type = objectElement->Attribute("type");
        }
        objectElement->QueryFloatAttribute("x", &x);
        objectElement->QueryFloatAttribute("y", &y);
        objectElement->QueryFloatAttribute("width", &width);
        objectElement->QueryFloatAttribute("height", &height);
        objectElement->QueryFloatAttribute("rotation", &rotation);
    }

    void parseProperties(const tinyxml2::XMLElement* propertiesElement) {
        for (const tinyxml2::XMLElement* propertyElement = propertiesElement->FirstChildElement("property");
             propertyElement;
             propertyElement = propertyElement->NextSiblingElement("property")) {
            std::string propertyName = propertyElement->Attribute("name");
            std::string propertyValue = propertyElement->Attribute("value");
            properties[propertyName] = propertyValue;
        }
    }
};

class PolygonObject : public Object {
public:
    PolygonObject() = default;
    explicit PolygonObject(const tinyxml2::XMLElement* objectElement) {
        parseAttributes(objectElement);
        parseProperties(objectElement->FirstChildElement("properties"));

        const tinyxml2::XMLElement* polygonElement = objectElement->FirstChildElement("polygon");
        if (!polygonElement) {
            throw std::runtime_error("Polygon element not found.");
        }

        std::stringstream pointsStream(polygonElement->Attribute("points"));
        std::string point;
        while (std::getline(pointsStream, point, ' ')) {
            std::stringstream pointStream(point);
            std::string x, y;
            std::getline(pointStream, x, ',');
            std::getline(pointStream, y, ',');
            points.emplace_back(std::stof(x), std::stof(y));
        }
    }

    const std::vector<std::pair<float, float>>& getPoints() const {
        return points;
    }

private:
    std::vector<std::pair<float, float>> points;
};

class PolylineObject : public Object {
public:
    PolylineObject() = default;
    explicit PolylineObject(const tinyxml2::XMLElement* objectElement) {
        parseAttributes(objectElement);
        parseProperties(objectElement->FirstChildElement("properties"));

        const tinyxml2::XMLElement* polylineElement = objectElement->FirstChildElement("polyline");
        if (!polylineElement) {
            throw std::runtime_error("Polyline element not found.");
        }

        std::stringstream pointsStream(polylineElement->Attribute("points"));
        std::string point;
        while (std::getline(pointsStream, point, ' ')) {
            std::stringstream pointStream(point);
            std::string x, y;
            std::getline(pointStream, x, ',');
            std::getline(pointStream, y, ',');
            points.emplace_back(std::stof(x), std::stof(y));
        }
    }

const std::vector<std::pair<float, float>>& getPoints() const {
    return points;
}

private:
    std::vector<std::pair<float, float>> points;
};

class EllipseObject : public Object {
public:
    EllipseObject() = default;
    explicit EllipseObject(const tinyxml2::XMLElement* objectElement) {
        parseAttributes(objectElement);
        parseProperties(objectElement->FirstChildElement("properties"));
    }

};

class TextObject : public Object {
public:
    TextObject() = default;
    explicit TextObject(const tinyxml2::XMLElement* objectElement) {
        parseAttributes(objectElement);
        parseProperties(objectElement->FirstChildElement("properties"));
        const tinyxml2::XMLElement* textElement = objectElement->FirstChildElement("text");
        if (!textElement) {
            throw std::runtime_error("Text element not found.");
        }
        text = textElement->GetText();
    }

    const std::string& getText() const {
        return text;
    }
    
private:
    std::string text;
};
