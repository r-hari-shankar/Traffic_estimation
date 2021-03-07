#ifndef BGEDITOR_HPP
#define BGEDITOR_HPP

#include <opencv2/opencv.hpp>

cv::Mat backgroundSubtraction(cv::Mat img, cv::Mat mask);
double getQueue(cv::Mat img, cv::Mat emptyImage);
double getDynamic(cv::Mat img, cv::Mat previousImage);

#endif