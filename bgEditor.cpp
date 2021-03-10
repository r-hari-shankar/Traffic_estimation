#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include "bgEditor.hpp"

using namespace cv;

cv::Mat backgroundSubtraction(cv::Mat imgO, cv::Mat mask) {
    cv::Mat img = imgO.clone();

    cv::GaussianBlur(img, img, cv::Size(5,5), 0);
    cv::GaussianBlur(mask, mask, cv::Size(5,5), 0);

    cv::absdiff(img, mask, img);
    cv::threshold(img, img, 30, 255.0, cv::THRESH_BINARY);

    cv::Mat structuringElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));

    cv::dilate(img, img, structuringElement);
    cv::dilate(img, img, structuringElement);
    cv::erode(img, img, structuringElement);

    cv::Mat clone = img.clone();
    cv::Mat imgContours(img.size(), CV_8UC3, cv::Scalar(0,0,0));

    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(clone, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(imgContours, contours, -1, cv::Scalar(255,255,255), -1);

    return imgContours;
}

cv::Mat opticalFlow(cv::Mat img, cv::Mat prevImage) {
    cv::Mat flow(prevImage.size(), CV_32FC2);
    cv::calcOpticalFlowFarneback(prevImage, img, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    cv::Mat flow_parts[2];
    cv::split(flow, flow_parts);
    cv::Mat magnitude, angle, magn_norm;
    cv::cartToPolar(flow_parts[0], flow_parts[1], magnitude, angle, true);
    cv::normalize(magnitude, magn_norm, 0.0f, 1.0f, cv::NORM_MINMAX);
    angle *= ((1.f / 360.f) * (180.f / 255.f));
    //build hsv image
    cv::Mat _hsv[3], hsv, hsv8, bgr;
    _hsv[0] = angle;
    _hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
    _hsv[2] = magn_norm;
    cv::merge(_hsv, 3, hsv);
    hsv.convertTo(hsv8, CV_8U, 255.0);
    cv::cvtColor(hsv8, bgr, cv::COLOR_HSV2BGR);
    bgr.convertTo(bgr, prevImage.type());
    return bgr;
}

double getQueue(cv::Mat img, cv::Mat emptyImage) {
    cv::Mat img1 = backgroundSubtraction(img, emptyImage);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    int a1 = cv::countNonZero(img1);
    cv::imshow("queue", img1);

    return (double)(a1) / (double)(img1.rows*img1.cols);
}

double getDynamic(cv::Mat img, cv::Mat previousImage, cv::Mat emptyImage) {
    cv::Mat img1 = opticalFlow(img, previousImage);
    //cv::Mat img2 = backgroundSubtraction(previousImage, emptyImage);
    //cv::absdiff(img1, img2, img1);
    cvtColor(img1, img1, COLOR_BGR2GRAY);
    cv::threshold(img1, img1, 20, 255, cv::THRESH_BINARY);
    cv::imshow("dynamic", img1);
    int a1 = cv::countNonZero(img1);

    return (double)(a1) / (double)(img1.rows*img1.cols);
}
