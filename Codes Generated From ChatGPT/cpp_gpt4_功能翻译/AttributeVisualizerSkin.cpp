#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <memory>

class Mote {
public:
    Mote(int id, double x, double y) : id_(id), x_(x), y_(y) {}

    int getId() const {
        return id_;
    }

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }

    void addAttribute(const std::string& key, const std::string& value) {
        attributes_[key] = value;
    }

    std::map<std::string, std::string> getAttributes() const {
        return attributes_;
    }

private:
    int id_;
    double x_;
    double y_;
    std::map<std::string, std::string> attributes_;
};

class MoteAttributesVisualizer {
public:
    MoteAttributesVisualizer() {}

    void addMote(const std::shared_ptr<Mote>& mote) {
        motes_.push_back(mote);
    }

    void removeMote(int id) {
        motes_.erase(std::remove_if(motes_.begin(), motes_.end(),
                    [&id](const std::shared_ptr<Mote>& mote) {
                        return mote->getId() == id;
                    }),
            motes_.end());
    }

    void displayMoteAttributes() {
        for (const auto& mote : motes_) {
            std::cout << "Mote " << mote->getId() << " at (" << mote->getX() << ", " << mote->getY() << "):\n";

            auto attributes = mote->getAttributes();
            for (const auto& attribute : attributes) {
                std::cout << "  " << attribute.first << ": " << attribute.second << "\n";
            }
        }
    }

private:
    std::vector<std::shared_ptr<Mote>> motes_;
};

int main() {
    MoteAttributesVisualizer visualizer;

    auto mote1 = std::make_shared<Mote>(1, 0.0, 0.0);
    mote1->addAttribute("color", "red");
    mote1->addAttribute("energy", "50");

    auto mote2 = std::make_shared<Mote>(2, 1.0, 1.0);
    mote2->addAttribute("color", "blue");
    mote2->addAttribute("energy", "75");

    visualizer.addMote(mote1);
    visualizer.addMote(mote2);

    visualizer.displayMoteAttributes();

    return 0;
}
