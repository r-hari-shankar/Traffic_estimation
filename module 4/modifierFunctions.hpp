#ifndef MODIFIERFUNCTIONS_HPP
#define MODIFIERFUNCTIONS_HPP

#include<opencv2/opencv.hpp>
#include<vector>

cv::Mat changePerspective(cv::Mat img, std::vector<cv::Point2f>corner);  // Function prototype, its declaration
cv::Mat cropImage(cv::Mat img);

#endif