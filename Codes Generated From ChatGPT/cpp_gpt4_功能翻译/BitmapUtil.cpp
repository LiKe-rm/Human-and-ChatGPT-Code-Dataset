#include <iostream>
#include <opencv2/opencv.hpp>

class BitmapUtil {
private:
    cv::Mat temp;

public:
    cv::Mat bitmapZoomByHeight(cv::Mat &srcBitmap, float newHeight) {
        float scale = newHeight / (float)srcBitmap.rows;
        return bitmapZoomByScale(srcBitmap, scale, scale);
    }

    cv::Mat bitmapZoomByScale(cv::Mat &srcBitmap, float scaleWidth, float scaleHeight) {
        cv::Mat resizedBitmap;
        cv::resize(srcBitmap, resizedBitmap, cv::Size(), scaleWidth, scaleHeight);
        return resizedBitmap;
    }

    cv::Mat bitmapToMat(cv::Mat &bitmap) {
        cv::Mat mat;
        bitmap.convertTo(mat, CV_32F);
        return mat;
    }

    void saveBitmapToDisk(cv::Mat &bitmap, std::string path) {
        try {
            cv::imwrite(path, bitmap);
            std::cout << "----------save success-------------------" << std::endl;
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
        }
    }

    cv::Mat getBitmapFromDisk(std::string path) {
        cv::Mat bitmap;
        try {
            bitmap = cv::imread(path, cv::IMREAD_COLOR);
        } catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
        }

        return bitmap;
    }
};

int main() {
    BitmapUtil bitmapUtil;

    std::string imagePath = "path_to_your_image";

    // Load image from disk
    cv::Mat image = bitmapUtil.getBitmapFromDisk(imagePath);

    if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Resize image
    cv::Mat resizedImage = bitmapUtil.bitmapZoomByHeight(image, 200.0f);

    // Save image to disk
    bitmapUtil.saveBitmapToDisk(resizedImage, "path_to_save_your_image");

    return 0;
}
