#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include "bgEditor.hpp"

cv::Mat backgroundSubtraction(cv::Mat img, cv::Mat mask) {
    cv::Mat output;
    cv::subtract(img, mask, output);
    return output;
}

double getQueue(cv::Mat img, cv::Mat emptyImage) {
    cv::Mat img1 = backgroundSubtraction(img, emptyImage);

    int a1 = cv::countNonZero(img1);

    return (double)(a1) / (double)(img1.rows*img1.cols);
}

double getDynamic(cv::Mat img, cv::Mat previousImage) {
    cv::Mat img1 = backgroundSubtraction(img, previousImage);

    int a1 = cv::countNonZero(img1);

    return (double)(a1) / (double)(img1.rows*img1.cols);
}
