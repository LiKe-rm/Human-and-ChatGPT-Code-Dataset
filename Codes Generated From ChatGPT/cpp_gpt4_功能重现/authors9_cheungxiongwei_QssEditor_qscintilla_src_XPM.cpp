#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <sstream>

class RGBAImage {
public:
    RGBAImage() : width_(0), height_(0) {}

    RGBAImage(int width, int height) : width_(width), height_(height), data_(width * height * 4, 0) {}

    int width() const { return width_; }

    int height() const { return height_; }

    unsigned char *data() { return data_.data(); }

    const unsigned char *data() const { return data_.data(); }

    unsigned int getPixel(int x, int y) const {
        int index = (y * width_ + x) * 4;
        return (data_[index] << 24) | (data_[index + 1] << 16) | (data_[index + 2] << 8) | data_[index + 3];
    }

    void setPixel(int x, int y, unsigned int value) {
        int index = (y * width_ + x) * 4;
        data_[index] = (value >> 24) & 0xFF;
        data_[index + 1] = (value >> 16) & 0xFF;
        data_[index + 2] = (value >> 8) & 0xFF;
        data_[index + 3] = value & 0xFF;
    }

private:
    int width_, height_;
    std::vector<unsigned char> data_;
};

class RGBAImageSet {
public:
    void addImage(const RGBAImage &image) {
        images_.push_back(image);
    }

    RGBAImage &getImage(int index) {
        if (index >= 0 && index < static_cast<int>(images_.size())) {
            return images_[index];
        } else {
            throw std::out_of_range("Invalid image index.");
        }
    }

    const RGBAImage &getImage(int index) const {
        if (index >= 0 && index < static_cast<int>(images_.size())) {
            return images_[index];
        } else {
            throw std::out_of_range("Invalid image index.");
        }
    }

    int size() const {
        return static_cast<int>(images_.size());
    }

private:
    std::vector<RGBAImage> images_;
};

class XPM {
public:
    XPM(const std::string &data) {
        loadFromString(data);
    }

    XPM(const std::vector<std::string> &data) {
        loadFromVector(data);
    }

    void draw(RGBAImage &surface, int x, int y) const {
        for (int j = 0; j < image_.height(); ++j) {
            for (int i = 0; i < image_.width(); ++i) {
                surface.setPixel(x + i, y + j, image_.getPixel(i, j));
            }
        }
    }

    unsigned int getPixel(int x, int y) const {
        return image_.getPixel(x, y);
    }

    void setPixel(int x, int y, unsigned int value) {
        image_.setPixel(x, y, value);
    }

private:
    void loadFromString(const std::string &data) {
        std::istringstream iss(data);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(iss, line)) {
            lines.push_back(line);
        }
        loadFromVector(lines);
    }

    void loadFromVector(const std::vector<std::string> &data) {
        int width, height, num_colors, chars_per_pixel;
        sscanf(data[0].c_str(), "%d %d %d %d", &width, &height, &num_colors, &chars_per_pixel);
        std::map<std::string, unsigned int> color_map;
        for (int i = 1; i <= num_colors; ++i) {
            std::string color_code = data[i].substr(0, chars_per_pixel);
            std::string color_value = data[i].substr(chars_per_pixel + 1);
            unsigned int rgba;
            if (color_value == "None") {
                rgba = 0;
            } else {
                sscanf(color_value.c_str(), "#%08X", &rgba);
            }
            color_map[color_code] = rgba;
        }

        image_ = RGBAImage(width, height);
        for (int y = 0; y < height; ++y) {
            const std::string &line = data[num_colors + 1 + y];
            for (int x = 0; x < width; ++x) {
                std::string color_code = line.substr(x * chars_per_pixel, chars_per_pixel);
                unsigned int rgba = color_map[color_code];
                image_.setPixel(x, y, rgba);
            }
        }
    }

    RGBAImage image_;
};

int main() {
    std::vector<std::string> xpm_data = {
    "3 3 2 1",
    " c #FFFFFF",
    "X c #000000",
    " X ",
    "X X",
    " X "
    };

    XPM xpm(xpm_data);
    RGBAImage surface(10, 10);

    xpm.draw(surface, 2, 2);

    for (int y = 0; y < surface.height(); ++y) {
        for (int x = 0; x < surface.width(); ++x) {
            unsigned int rgba = surface.getPixel(x, y);
            if (rgba & 0xFF000000) {
                std::cout << "X";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
