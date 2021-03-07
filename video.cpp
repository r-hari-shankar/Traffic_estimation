#include <iostream>
#include <opencv2/opencv.hpp>
#include "modifierFunctions.hpp"
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

void mouseClick(int evt, int x, int y, int flags, void* data_ptr)
{
    if  ( evt == cv::EVENT_LBUTTONDOWN ){
        std::vector<cv::Point2f> *data = ((std::vector<cv::Point2f> *) data_ptr);
        if (data->size() < 4) {
            data->push_back(cv::Point2f(x,y));
        }
    }
}

int main(int argc, char* argv[])
{
    const char* input_file = "{ input          | trafficvideo.mp4 |}";
    CommandLineParser parser(argc, argv, input_file);
    parser.about( "This program shows how to use background subtraction methods provided by "
                  " OpenCV. You can process both videos and images.\n" );
    
    VideoCapture capture( samples::findFile( parser.get<String>("input") ) );
    if (!capture.isOpened()){
        cerr << "Unable to open: " << parser.get<String>("input") << endl;
        return 0;
    }
    Mat frame;
    std::vector<cv::Point2f> points;
    points.push_back(Point2f(977,212));
    points.push_back(Point2f(311,1059));
    points.push_back(Point2f(1530,1058));
    points.push_back(Point2f(1264,210));
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        cv::Mat angleCorrectedImage = changePerspective(frame, points);
        cv::Mat croppedImage = cropImage(angleCorrectedImage);
        imshow("Density", croppedImage); //error thrown when asked to return cropped imag
        int keyboard = waitKey(30);
        if (keyboard >= 65 && keyboard <= 122 || keyboard == 27)
            break;
    }
    return 0;
}