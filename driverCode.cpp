#include <opencv2/opencv.hpp>
#include "modifierFunctions.hpp"

void mouseClick(int evt, int x, int y, int flags, void* data_ptr)
{
    // This function will be executed whenever we perform a mouse click
    if  ( evt == cv::EVENT_LBUTTONDOWN ){// If it is left click, we continue. else we abort
        std::vector<cv::Point2f> *data = ((std::vector<cv::Point2f> *) data_ptr);//getting back our vector
        if (data->size() < 4) {
            data->push_back(cv::Point2f(x,y)); //adding the point to the vector
        }
    }
}

int main( int argc, char** argv)
{   // if no argument is passed, it prints out the given string and ends the execution
    if(argv[1]==NULL){

        std::cout << "Image not given in input check readme file for help" << std::endl;
        return 1;
    }
    cv::Mat originalImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);// Loading my original image
    if(originalImage.empty())// If the image is empty, we give an error again and abort the function
    {
        std::cout << "Could not read the image:" << argv[1]<<" check readme file for help" <<std::endl;
        return 1;
    }
    
    std::string s1 = argv[1];
    std::string s2 = "perspective_";
    std::string s3 = "cropped_";
    cv::Mat inputImage = originalImage.clone();//making a clone of the original image. This will be interactive and will mark the input points with black dots
    std::vector<cv::Point2f> points; //vector for storing the points
    std::cout << "Click Order: TL, BL, BR, TR" << std::endl;
    cv::imshow("InputImage", inputImage); // show the input image to take inputs
    cv::setMouseCallback("InputImage", mouseClick, &points); //perform the action "mouseClick" upon a mouse click
    cv::waitKey(0); // wait for the user to hit a key
    cv::imshow("OriginalImage", originalImage);
    // Throw an error if number of selected points are not 4.
    if(points.size() == 0) {
        std::cout << "empty" << std::endl;
    }
    // Throw an error if number of selected points are not 4.
    if(points.size() != 4) {
        std::cout << "Invalid number of points selected, Had to select 4, but selected " << points.size() << std::endl;
    }
    for(int i = 0; i < points.size(); i++) {
        std::cout << points[i].x << " " << points[i].y << std::endl;
    }
    for(int i = 0; i < points.size(); i++) {
        cv::circle(inputImage, points[i], 3, cv::Scalar(0,0,255-75*i), 5);
    }
    cv::destroyWindow("InputImage");// close the input window
    cv::imshow("SelectedPoints", inputImage); //show a window with all the selected points marked with black dots
    cv::Mat angleCorrectedImage = changePerspective(originalImage, points); // Changing the perspective and storing it in new Mat
    cv::imshow("New Perspective", angleCorrectedImage); // Display this new image
    cv::waitKey(0);
    // This will save the image. if the key pressed in 
    std::string n1 = s2 + s1;// output name of perspective change image
    cv::imwrite(n1,angleCorrectedImage);
    cv::Mat croppedImage = cropImage(angleCorrectedImage);
    cv::imshow("New Perspective + Cropped", croppedImage);
    cv::waitKey(0);
    std::string n2 = s3 + s1;// output name  of cropped image
    cv::imwrite(n2,croppedImage);
}