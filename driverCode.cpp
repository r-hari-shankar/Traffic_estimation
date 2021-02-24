#include <iostream>
#include <opencv2/opencv.hpp>
#include "modifierFunctions.hpp"

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
    if(argv[1]==NULL){
        std::cout << "Image not given in input check readme file for help" << std::endl;
        return 1;
    }
    cv::Mat originalImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if(originalImage.empty())
    {
        std::cout << "Could not read the image:" << argv[1]<<" check readme file for help" <<std::endl;
        return 1;
    }
    
    std::string s1 = argv[1];
    std::string s2 = "perspective_";
    std::string s3 = "cropped_";
    cv::Mat inputImage = originalImage.clone();
    std::vector<cv::Point2f> points;
    std::cout << "Click Order: TL, BL, BR, TR" << std::endl;
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
        cv::circle(inputImage, points[i], 3, cv::Scalar(0,0,255-75*i), 5);
    }
    cv::destroyWindow("InputImage");
    cv::imshow("SelectedPoints", inputImage);
    cv::Mat angleCorrectedImage = changePerspective(originalImage, points);
    cv::imshow("New Perspective", angleCorrectedImage);
    cv::waitKey(0);
    std::string n1 = s2 + s1;
    cv::imwrite(n1,angleCorrectedImage);
    cv::Mat croppedImage = cropImage(angleCorrectedImage);
    cv::imshow("New Perspective + Cropped", croppedImage);
    cv::waitKey(0);
    std::string n2 = s3 + s1;
    cv::imwrite(n2,croppedImage);
}