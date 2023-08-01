#include <iostream>
#include <bitset>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

enum State {
    Hiding,
    FillingWithZeros
};

Mat embedText(const string& text, const Mat& inputBitmap) {
    State state = Hiding;
    int textIndex = 0, pixelElementIndex = 0, charValue = 0;
    int textLength = text.size();
    Mat outputBitmap = inputBitmap.clone();
    
    for (int row = 0; row < outputBitmap.rows; ++row) {
        for (int col = 0; col < outputBitmap.cols; ++col) {
            Vec3b& pixel = outputBitmap.at<Vec3b>(row, col);
            for (int color = 0; color < 3; ++color) {
                if (pixelElementIndex % 8 == 0) {
                    if (state == FillingWithZeros && charValue == 0) {
                        break;
                    }

                    if (textIndex >= textLength) {
                        state = FillingWithZeros;
                    } else {
                        charValue = text[textIndex++];
                    }
                }
                pixel[color] = (pixel[color] & ~1) | ((charValue >> (7 - (pixelElementIndex % 8))) & 1);
                ++pixelElementIndex;
            }
        }
    }
    
    return outputBitmap;
}

void SaveToFile(const string& filename, const Mat& bitmap) {
    imwrite(filename, bitmap);
}

void LSB_encode(const string& text, const Mat& inputBitmap, const string& outputFilename) {
    Mat outputBitmap = embedText(text, inputBitmap);
    SaveToFile(outputFilename, outputBitmap);
}

int reverseBits(int n) {
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

string extractText(const Mat& inputBitmap) {
    string extractedText;
    int charValue = 0, pixelElementIndex = 0;
    
    for (int row = 0; row < inputBitmap.rows; ++row) {
        for (int col = 0; col < inputBitmap.cols; ++col) {
            Vec3b pixel = inputBitmap.at<Vec3b>(row, col);
            for (int color = 0; color < 3; ++color) {
                charValue = (charValue << 1) | (pixel[color] & 1);
                ++pixelElementIndex;
                if (pixelElementIndex % 8 == 0) {
                    charValue = reverseBits(charValue);
                    if (charValue == 0) {
                        return extractedText;
                    }
                    extractedText += static_cast<char>(charValue);
                    charValue = 0;
                }
            }
        }
    }

    return extractedText;
}

string LSB_decode(const string& inputFilename) {
    Mat inputBitmap = imread(inputFilename);
    return extractText(inputBitmap);
}

int main() {
    string inputFilename = "input.bmp";
    string outputFilename = "output.bmp";
    string text = "Hello, World!";
    
    Mat inputBitmap = imread(inputFilename, IMREAD_COLOR);
    LSB_encode(text, inputBitmap, outputFilename);
    
    string extractedText = LSB_decode(outputFilename);
    cout << "Extracted text: " << extractedText << endl;

    return 0;
}
