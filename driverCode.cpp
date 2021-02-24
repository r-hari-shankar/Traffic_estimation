#include <iostream>
#include <opencv2/opencv.hpp>

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
        std::cout << "Image not given in input" << std::endl;
        return 1;
    }
    cv::Mat originalImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    if(originalImage.empty())
    {
        std::cout << "Could not read the image:" << argv[1]<< std::endl;
        return 1;
    }
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
    int n = cv::waitKey(0);
    if(n=='t'){
        cv::imwrite("perspective_traffic.jpg",angleCorrectedImage);
    }
    else{
        cv::imwrite("perspective_empty.jpg",angleCorrectedImage);
    }
    cv::Mat croppedImage = cropImage(angleCorrectedImage);
    cv::imshow("New Perspective + Cropped", croppedImage);
    int k = cv::waitKey(0);
    if(k=='t'){
        cv::imwrite("cropped_traffic.jpg",croppedImage);
    }
    else{
        cv::imwrite("cropped_empty.jpg",croppedImage);
    }
}