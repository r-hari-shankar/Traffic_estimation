#ifndef BGEDITOR_HPP
#define BGEDITOR_HPP

#include <opencv2/opencv.hpp>

cv::Mat backgroundSubtraction(cv::Mat imgO, cv::Mat mask);
cv::Mat opticalFlow(cv::Mat img, cv::Mat prevImage);
double getQueue(cv::Mat img, cv::Mat emptyImage);
double getDynamic(cv::Mat img, cv::Mat previousImage, cv::Mat emptyImage);

#endif