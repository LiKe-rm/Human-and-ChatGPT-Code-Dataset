#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
#include <stdexcept>

struct BitmapHeader {
    std::uint32_t size;
    std::int32_t width;
    std::int32_t height;
    std::uint16_t planes;
    std::uint16_t bitCount;
    std::uint32_t compression;
    std::uint32_t sizeImage;
    std::int32_t xPelsPerMeter;
    std::int32_t yPelsPerMeter;
    std::uint32_t clrUsed;
    std::uint32_t clrImportant;
};

struct Color {
    std::uint8_t r, g, b;
};

struct Pixel {
    std::uint8_t colorIndex;
    char character;
};

void readBitmapHeader(std::ifstream &inputFile, BitmapHeader &header) {
    inputFile.read(reinterpret_cast<char *>(&header.size), 4);
    inputFile.seekg(8, std::ios_base::cur);
    inputFile.read(reinterpret_cast<char *>(&header.width), 4);
    inputFile.read(reinterpret_cast<char *>(&header.height), 4);
    inputFile.read(reinterpret_cast<char *>(&header.planes), 2);
    inputFile.read(reinterpret_cast<char *>(&header.bitCount), 2);
    inputFile.read(reinterpret_cast<char *>(&header.compression), 4);
    inputFile.read(reinterpret_cast<char *>(&header.sizeImage), 4);
    inputFile.read(reinterpret_cast<char *>(&header.xPelsPerMeter), 4);
    inputFile.read(reinterpret_cast<char *>(&header.yPelsPerMeter), 4);
    inputFile.read(reinterpret_cast<char *>(&header.clrUsed), 4);
    inputFile.read(reinterpret_cast<char *>(&header.clrImportant), 4);
}

Color toGrayscale(Color color) {
    std::uint8_t grayValue = static_cast<std::uint8_t>(0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
    return {grayValue, grayValue, grayValue};
}

std::uint8_t findClosestColorIndex(const Color &color, const std::vector<Color> &palette) {
    double minDistance = std::numeric_limits<double>::max();
    std::uint8_t closestIndex = 0;
    for (std::size_t i = 0; i < palette.size(); ++i) {
        double distance = std::sqrt(std::pow(color.r - palette[i].r, 2) + std::pow(color.g - palette[i].g, 2) + std::pow(color.b - palette[i].b, 2));
        if (distance < minDistance) {
            minDistance = distance;
            closestIndex = static_cast<std::uint8_t>(i);
        }
    }
    return closestIndex;
}

std::vector<Color> generatePalette(std::size_t numberOfColors) {
    std::vector<Color> palette(numberOfColors);
    for (std::size_t i = 0; i < numberOfColors; ++i) {
        std::uint8_t colorValue = static_cast<std::uint8_t>(255.0 * i / (numberOfColors - 1));
        palette[i] = {colorValue, colorValue, colorValue};
    }
    return palette;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_bitmap_file> <output_sprite_file> [<number_of_colors>]" << std::endl;
        return 1;
    }

    std::string inputFilename(argv[1]);
    std::string outputFilename(argv[2]);
    std::size_t numberOfColors = 40;
    if (argc > 3) {
        numberOfColors = std::stoul(argv[3]);
    }

    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file: " << inputFilename << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file: " << outputFilename << std::endl;
        return 1;
    }

    BitmapHeader header;
    readBitmapHeader(inputFile, header);

    if (header.bitCount != 24) {
        std::cerr << "Error: Only 24-bit bitmaps are supported." << std::endl;
        return 1;
    }

    inputFile.seekg(header.size, std::ios_base::beg);

    std::vector<Color> palette = generatePalette(numberOfColors);
    std::vector<std::vector<Pixel>> sprite(header.height, std::vector<Pixel>(header.width));

    for (std::int32_t y = header.height - 1; y >= 0; --y) {
        for (std::int32_t x = 0; x < header.width; ++x) {
            Color color;
            inputFile.read(reinterpret_cast<char *>(&color.b), 1);
            inputFile.read(reinterpret_cast<char *>(&color.g), 1);
            inputFile.read(reinterpret_cast<char *>(&color.r), 1);

            Color grayscaleColor = toGrayscale(color);
            std::uint8_t colorIndex = findClosestColorIndex(grayscaleColor, palette);

            sprite[y][x].colorIndex = colorIndex;
            sprite[y][x].character = 'X'; // You can choose a different character representation for the sprite here
        }

        inputFile.seekg((4 - (header.width * 3) % 4) % 4, std::ios_base::cur);
    }

    outputFile.write(reinterpret_cast<const char *>(&header.width), 4);
    outputFile.write(reinterpret_cast<const char *>(&header.height), 4);
    outputFile.write(reinterpret_cast<const char *>(&numberOfColors), 4);

    for (const auto &color : palette) {
        outputFile.write(reinterpret_cast<const char *>(&color.r), 1);
        outputFile.write(reinterpret_cast<const char *>(&color.g), 1);
        outputFile.write(reinterpret_cast<const char *>(&color.b), 1);
    }

    for (const auto &row : sprite) {
        for (const auto &pixel : row) {
            outputFile.write(reinterpret_cast<const char *>(&pixel.colorIndex), 1);
            outputFile.write(&pixel.character, 1);
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Sprite created successfully: " << outputFilename << std::endl;
    return 0;
}

