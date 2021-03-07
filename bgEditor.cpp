#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include "bgEditor.hpp"

cv::Mat backgroundSubtraction(cv::Mat img) {
    cv::Mat mask;
    cv::Ptr<cv::BackgroundSubtractor> pBackSub;
    pBackSub->apply(img, mask);
    return mask;
}

double getQueue(cv::Mat img, cv::Mat emptyImage) {
    cv::Mat img1 = backgroundSubtraction(img);
    cv::Mat img2 = backgroundSubtraction(emptyImage);

    int a1 = cv::countNonZero(img1);
    int a2 = cv::countNonZero(img2);

    return (double)(a1-a2) / (double)(img1.rows*img1.cols);
}

double getDynamic(cv::Mat img, cv::Mat previousImage) {
    cv::Mat img1 = backgroundSubtraction(img);
    cv::Mat img2 = backgroundSubtraction(previousImage);

    int a1 = cv::countNonZero(img1);
    int a2 = cv::countNonZero(img2);

    return (double)(a1-a2) / (double)(img1.rows*img1.cols);
}