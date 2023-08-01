#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
    // 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "无法打开摄像头" << endl;
        return -1;
    }

    Mat frame, gray, prevGray, diff, thresh;
    double motion_threshold = 30;
    bool recording = false;
    VideoWriter video;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cerr << "无法捕获摄像头帧" << endl;
            break;
        }

        // 转换为灰度图像
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(21, 21), 0);

        if (!prevGray.empty()) {
            // 计算帧之间的差异
            absdiff(gray, prevGray, diff);
            threshold(diff, thresh, 25, 255, THRESH_BINARY);

            // 检测运动
            double motion = countNonZero(thresh);

            if (motion > motion_threshold) {
                if (!recording) {
                    recording = true;
                    video.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, frame.size(), true);

                    if (!video.isOpened()) {
                        cerr << "无法创建视频文件" << endl;
                        break;
                    }
                }

                putText(frame, "Recording", Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
                video << frame;
            } else {
                recording = false;
                if (video.isOpened()) {
                    video.release();
                }
            }
        }

        imshow("Real-time Monitoring", frame);

        if (waitKey(30) >= 0) {
            break;
        }

        swap(gray, prevGray);
    }

    // 释放资源
    cap.release();
    if (video.isOpened()) {
        video.release();
    }
    destroyAllWindows();

    return 0;
}
