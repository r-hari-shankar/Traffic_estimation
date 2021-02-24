#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include "angleCorrection.hpp"

cv::Mat changePerspective(cv::Mat img, std::vector<cv::Point2f>corner) {
    std::vector<cv::Point2f> desiredCorner;  // this vector contains my desired location for final points
    desiredCorner.push_back(cv::Point2f(472,52));   // top left corner
    desiredCorner.push_back(cv::Point2f(472,830));  // bottom left corner
    desiredCorner.push_back(cv::Point2f(800,830));  // bottom right corner
    desiredCorner.push_back(cv::Point2f(800,52));   // top right corner

    cv::Mat H = cv::findHomography(corner, desiredCorner);  // Find the approximate homography for the image
    cv::Mat newPerspectiveImage;
    cv::warpPerspective(img, newPerspectiveImage, H, img.size());  // map all the points to new points 
    return newPerspectiveImage;
}

cv::Mat cropImage(cv::Mat img) {
    cv::Rect crop_region(472,52,328,778);
    cv::Mat im = img(crop_region);
    return im;
}