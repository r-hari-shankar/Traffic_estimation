#include <iostream>
#include <opencv2/opencv.hpp>
#include "modifierFunctions.hpp"
#include "bgEditor.hpp"
#include <sstream>
#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    //To check if input is null
    if(argv[1]==NULL){
        std::cout << "Video input not given ,check readme file for help" << std::endl;
        return 1;
    }
    //To check if the video input file does not exist
    ifstream ifile;
    ifile.open(argv[1]);
    if(!ifile) {
        cout<<"Video file doesn't exist in current directory"<<"\n";
        return 0;  
    }
    //opening the video file
    string instream = argv[1];
    VideoCapture capture( samples::findFile( instream ) );
    if (!capture.isOpened()){
        cerr << "Unable to open: " << instream << endl;
        return 0;
    }
    cv::Mat frame;
    cv::Mat empty = cv::imread("cropped_road.png",cv::IMREAD_GRAYSCALE); //empty frame for queue density evaluation
    cv::Mat previous = empty; //This matrix will store the value of the previous frame
 
    //points specify the region which is angle corrected and cropped
    std::vector<cv::Point2f> points;
    points.push_back(Point2f(977,212));
    points.push_back(Point2f(311,1059));
    points.push_back(Point2f(1530,1058));
    points.push_back(Point2f(1264,210));
    cout<<"frame_number"<<" "<<"queue density"<<" "<<"dynamic density"<<"\n";

    //fstream used to append the output densities in the "out.txt" file
    fstream file;
    file.open("out.txt",ios::out | ios::in);
    int frame_number=0; //keeps count of the frame
    while (true) {  //loop for traversing through all the frames of the video file
        capture >> frame;
        cv:: Mat grayscale;
        if (frame.empty())
            break;
        //size of frame discribed by rectangle
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        //To change color to grayscale
        cvtColor(frame, grayscale, COLOR_RGB2GRAY);
        //for frame number of the playing video
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //angle corrected and cropped image produced using functions defined in the previous assignment
        cv::Mat angleCorrectedImage = changePerspective(grayscale, points);
        cv::Mat croppedImage = cropImage(angleCorrectedImage);
        double queue = getQueue(croppedImage,empty); //stores the queue density
        double dynamic = getDynamic(croppedImage,previous); //stores the dynamic density
        cout<<frame_number<<" "<<queue<<" "<<dynamic<<"\n"; //return the values in console
        file<<frame_number<<" "<<queue<<" "<<dynamic<<"\n"; //return the values in the "out.txt"
        previous = croppedImage; //so that previous points to the previous frame 
        imshow("Density", croppedImage); //video displayed
        frame_number++;
        //Press any key to exit the program
        int keyboard = waitKey(30); 
        if (keyboard >= 65 && keyboard <= 122 || keyboard == 27)
            break;
    }
    file.close();
    return 0;
}
