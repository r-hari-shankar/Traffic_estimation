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
#include <pthread.h>
#include <chrono>
using namespace cv;
using namespace std;
using namespace std::chrono;
#define NUM_THREADS 8

struct thread_data {
   int  thread_id;
   int frameno;
   cv::Mat ci;
   cv::Mat emp;
};

void *opr1(void *threadarg){
    //cout<<"on"<<"\n";
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cv::imshow("Density", my_data -> ci);

    double queue = getQueue(my_data->ci,my_data->emp);
    int fr =my_data->frameno;
    cout<<fr<<" "<<queue<<"\n";

    return NULL;  
}

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
    cv::Mat frame,frame1,frame2,frame3,frame4,frame5,frame6,frame7;
    cv::Mat empty = cv::imread("cropped_road.png",cv::IMREAD_GRAYSCALE); //empty frame for queue density evaluation
    cv::Mat previous = empty; //This matrix will store the value of the previous frame
    //cout<<"done"<<"\n";
    //points specify the region which is angle corrected and cropped
    std::vector<cv::Point2f> points;
    points.push_back(Point2f(977,212));
    points.push_back(Point2f(311,1059));
    points.push_back(Point2f(1530,1058));
    points.push_back(Point2f(1264,210));
    //cout<<"frame_number"<<" "<<"queue density"<<" "<<"dynamic density"<<"\n";

    //fstream used to append the output densities in the "out.txt" file
    fstream file;
    file.open("out.txt",ios::out | ios::in);
    int frame_number=0; //keeps count of the frame
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    int i;
    //cout<<"done1"<<"\n";
    auto start = high_resolution_clock::now();
    while (true) {  //loop for traversing through all the frames of the video file
        capture >> frame;
        capture >> frame1;
        capture >> frame2;
        capture >> frame3;
        capture >> frame4;
        capture >> frame5;
        capture >> frame6;
        capture >> frame7;

        cv:: Mat grayscale;
        cv:: Mat grayscale1;
        cv:: Mat grayscale2;
        cv:: Mat grayscale3;
        cv:: Mat grayscale4;
        cv:: Mat grayscale5;
        cv:: Mat grayscale6;
        cv:: Mat grayscale7;
        if (frame.empty() || frame1.empty() frame2.empty() || frame3.empty() || frame4.empty() || frame5.empty() || frame6.empty() || frame7.empty())
            break;
        //size of frame discribed by rectangle
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame1, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame2, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame3, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame4, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame5, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame6, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        rectangle(frame7, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        //To change color to grayscale
        cvtColor(frame, grayscale, COLOR_RGB2GRAY);
        cvtColor(frame1, grayscale1, COLOR_RGB2GRAY);
        cvtColor(frame2, grayscale2, COLOR_RGB2GRAY);
        cvtColor(frame3, grayscale3, COLOR_RGB2GRAY);
        cvtColor(frame4, grayscale4, COLOR_RGB2GRAY);
        cvtColor(frame5, grayscale5, COLOR_RGB2GRAY);
        cvtColor(frame6, grayscale6, COLOR_RGB2GRAY);
        cvtColor(frame7, grayscale7, COLOR_RGB2GRAY);
        //cout<<"done2"<<"\n";
        //for frame number of the playing video
        stringstream ss;
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //angle corrected and cropped image produced using functions defined in the previous assignment
        cv::Mat angleCorrectedImage = changePerspective(grayscale, points);
        cv::Mat croppedImage = cropImage(angleCorrectedImage);
        cv::Mat angleCorrectedImage1 = changePerspective(grayscale1, points);
        cv::Mat croppedImage1 = cropImage(angleCorrectedImage1);
        cv::Mat angleCorrectedImage2 = changePerspective(grayscale2, points);
        cv::Mat croppedImage2 = cropImage(angleCorrectedImage2);
        cv::Mat angleCorrectedImage3 = changePerspective(grayscale3, points);
        cv::Mat croppedImage3 = cropImage(angleCorrectedImage3);
        cv::Mat angleCorrectedImage4 = changePerspective(grayscale4, points);
        cv::Mat croppedImage4 = cropImage(angleCorrectedImage4);
        cv::Mat angleCorrectedImage5 = changePerspective(grayscale5, points);
        cv::Mat croppedImage5 = cropImage(angleCorrectedImage5);
        cv::Mat angleCorrectedImage6 = changePerspective(grayscale6, points);
        cv::Mat croppedImage6 = cropImage(angleCorrectedImage6);
        cv::Mat angleCorrectedImage7 = changePerspective(grayscale7, points);
        cv::Mat croppedImage7 = cropImage(angleCorrectedImage7);
        for( i = 0; i < NUM_THREADS; i++ ) {
          //cout <<"main() : creating thread, " << i << endl;
          td[i].thread_id = i;
          td[i].emp = empty;
          if(i==0){
            td[i].ci=croppedImage;
            td[i].frameno = frame_number; 
          }
          else if(i==1){
            td[i].ci=croppedImage1;
            td[i].frameno = frame_number+1;
          }
          else if(i==2){
            td[i].ci=croppedImage2;
            td[i].frameno = frame_number+2;
          }
          else if(i==3){
            td[i].ci=croppedImage3;
            td[i].frameno = frame_number+3;
          }
          else if(i==4){
            td[i].ci=croppedImage4;
            td[i].frameno = frame_number+4;
          }
          else if(i==5){
            td[i].ci=croppedImage5;
            td[i].frameno = frame_number+5;
          }
          else if(i==6){
            td[i].ci=croppedImage6;
            td[i].frameno = frame_number+6;
          }
          else if(i==7){
            td[i].ci=croppedImage7;
            td[i].frameno = frame_number+7;
          }
          //cout<<"done3"<<"\n";
          rc = pthread_create(&threads[i], NULL, opr1, (void *)&td[i]);
          
          if (rc) {
             cout << "Error:unable to create thread," << rc << endl;
             exit(-1);
          }
          
       }
       //cout<<"done4"<<"\n";
        //pthread_exit(NULL);
        //cout<<"done5"<<"\n";
        //double queue = getQueue(croppedImage,empty); //stores the queue density
        //double dynamic = getDynamic(croppedImage,previous,empty); //stores the dynamic density
        //cout<<frame_number<<" "<<queue<<" "<<"\n"; //return the values in console
        //file<<frame_number<<" "<<queue<<" "<<"\n"; //return the values in the "out.txt"
        previous = croppedImage; //so that previous points to the previous frame 
        //imshow("Density", croppedImage); //video displayed
        frame_number+=NUM_THREADS;
        //Press any key to exit the program
        int keyboard = waitKey(30); 
        if (keyboard >= 65 && keyboard <= 122 || keyboard == 27)
            break;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken by function: "<< duration.count() << " seconds" << endl;
    file.close();
    return 0;
}
