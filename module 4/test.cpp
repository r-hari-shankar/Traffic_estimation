#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

void blur(cv::Mat &image) {
  cv::GaussianBlur(image, image, cv::Size(7,7), -1);
}

int main(int argc, char *argv[]) {

    cv::VideoCapture cap("trafficvideo.mp4");

    if(!cap.isOpened())
    {
        std::cout<<"VideoCapture did not open"<<std::endl;
        return -1;
    }

    cv::Mat frames[2];
    std::thread tds[2];

    while(true) {
        if(!cap.read(frames[0]) || !cap.read(frames[1]))
        {
            std::cout<<"Frames empty"<<std::endl;
            break;
        }

        tds[0] = std::thread(&blur, std::ref(frames[0]));
        tds[1] = std::thread(&blur, std::ref(frames[1]));

        tds[0].join();
        tds[1].join();

        cv::imshow("Frame", frames[0]);
        if ((cv::waitKey(30) & 0XFF) == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
