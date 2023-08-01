#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat computeLuminanceHistogram(const cv::Mat& inputImage);
cv::Mat computeChromaLuminanceHistogram(const cv::Mat& inputImage);
cv::Mat computeColorChannelHistogram(const cv::Mat& inputImage);
cv::Mat displayYUVPixelCoordinates(const cv::Mat& inputImage);
cv::Mat displayChromaPixelCoordinates(const cv::Mat& inputImage);

int main() {
    cv::Mat inputImage = cv::imread("input_image.jpg", cv::IMREAD_COLOR);
    if (inputImage.empty()) {
        std::cout << "Error: Cannot read input image!" << std::endl;
        return -1;
    }

    cv::Mat luminanceHistogram = computeLuminanceHistogram(inputImage);
    cv::Mat chromaLuminanceHistogram = computeChromaLuminanceHistogram(inputImage);
    cv::Mat colorChannelHistogram = computeColorChannelHistogram(inputImage);
    cv::Mat yuvPixelCoordinates = displayYUVPixelCoordinates(inputImage);
    cv::Mat chromaPixelCoordinates = displayChromaPixelCoordinates(inputImage);

    cv::imwrite("luminance_histogram.jpg", luminanceHistogram);
    cv::imwrite("chroma_luminance_histogram.jpg", chromaLuminanceHistogram);
    cv::imwrite("color_channel_histogram.jpg", colorChannelHistogram);
    cv::imwrite("yuv_pixel_coordinates.jpg", yuvPixelCoordinates);
    cv::imwrite("chroma_pixel_coordinates.jpg", chromaPixelCoordinates);

    return 0;
}

cv::Mat computeLuminanceHistogram(const cv::Mat& inputImage) {
    // 将输入图像转换为HSV格式
    cv::Mat hsvImage;
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    // 提取亮度通道（V通道）
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsvImage, hsvChannels);
    cv::Mat luminance = hsvChannels[2];

    // 计算亮度直方图
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    cv::Mat hist;
    cv::calcHist(&luminance, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // 将直方图绘制到输出图像中
    int histWidth = 512, histHeight = 400;
    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
                 cv::Point(histWidth * (i - 1) / histSize, histHeight - cvRound(hist.at<float>(i - 1))),
                 cv::Point(histWidth * i / histSize, histHeight - cvRound(hist.at<float>(i))),
                 cv::Scalar(0, 255, 0),
                 2, 8, 0);
    }

    return histImage;
}

cv::Mat computeChromaLuminanceHistogram(const cv::Mat& inputImage) {
    // Implement function 2 here
}

cv::Mat computeColorChannelHistogram(const cv::Mat& inputImage) {
    // Implement function 3 here
}

cv::Mat displayYUVPixelCoordinates(const cv::Mat& inputImage) {
    // Implement function 4 here
}

cv::Mat displayChromaPixelCoordinates(const cv::Mat& inputImage) {
    // Implement function 5 here
}
