#include <iostream>
#include <opencv2/opencv.hpp>

void mouseClick(int evt, int x, int y, int flags, void* data_ptr)
{
    if  ( evt == cv::EVENT_LBUTTONDOWN ){
        std::vector<cv::Point2f> *data = ((std::vector<cv::Point2f> *) data_ptr);
        if (data->size() < 4) {
            data->push_back(cv::Point2f(x,y));
        }
    }
}

int main( int argc, char** argv)
{
    cv::Mat originalImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat inputImage = originalImage.clone();
    std::vector<cv::Point2f> points;
    std::cout << "Click Order: TL, TR, BR, BL" << std::endl;
    cv::imshow("InputImage", inputImage);
    cv::setMouseCallback("InputImage", mouseClick, &points);
    cv::waitKey(0);
    cv::imshow("OriginalImage", originalImage);
    if(points.size() == 0) {
        std::cout << "empty" << std::endl;
    }
    for(int i = 0; i < points.size(); i++) {
        std::cout << points[i].x << " " << points[i].y << std::endl;
    }
    for(int i = 0; i < points.size(); i++) {
        cv::circle(inputImage, points[i], 3, cv::Scalar(0,0,255), 5);
    }
    cv::destroyWindow("InputImage");
    cv::imshow("SelectedPoints", inputImage);
    cv::waitKey(0);
}
