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

using namespace cv;
using namespace std;

#define NUM_THREADS 4

struct thread_data {
   int  thread_id;
   cv::Mat ci;
   cv::Mat emp;
   double answer;
};

void *opr1(void *threadarg){
    //cout<<"on"<<"\n";
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cv::imshow("Density", my_data -> ci);
    double queue = getQueue(my_data->ci,my_data->emp);
    cout<<queue<<"\n";
    my_data->answer = queue;
    return NULL;  
}

int divideImage(const cv::Mat& img, int numberPartitions, std::vector<cv::Mat>& blocks) {
 // Checking if the image was passed correctly
 if (!img.data || img.empty())
 {
              std::cout << "Image Error: Cannot load image to divide." << std::endl;
      return 1;
 }

 // init image dimensions
 int imgWidth = img.cols;
 int imgHeight = img.rows;
 //std::cout << "IMAGE SIZE: " << "(" << imgWidth << "," << imgHeight << ")" << std::endl;

int blockWidth, blockHeight;

 if(numberPartitions >= 4) {
    blockWidth = imgWidth/numberPartitions;
    blockHeight = imgHeight/numberPartitions;
 } else {
    blockWidth = imgWidth/numberPartitions;
    blockHeight = imgHeight;
 }

 // init block dimensions
 int bwSize;
 int bhSize;

 int y0 = 0;
 while (y0 < imgHeight)
 {
   // compute the block height
   bhSize = ((y0 + blockHeight) > imgHeight) * (blockHeight - (y0 + blockHeight - imgHeight)) + ((y0 + blockHeight) <= imgHeight) * blockHeight;

       int x0 = 0;
       while (x0 < imgWidth)
       {
     // compute the block height
         bwSize = ((x0 + blockWidth) > imgWidth) * (blockWidth - (x0 + blockWidth - imgWidth)) + ((x0 + blockWidth) <= imgWidth) * blockWidth;

               // crop block
               blocks.push_back(img(cv::Rect(x0, y0, bwSize, bhSize)).clone());

               // update x-coordinate
               x0 = x0 + blockWidth;
       }

       // update y-coordinate
       y0 = y0 + blockHeight;
 }
 return 0;
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
    fstream file1, file2;
    file1.open("method4.txt",ios::out | ios::in);
    int frame_number=0; //keeps count of the frame
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;
    int i;

    double error = 0;

    while (true) {  //loop for traversing through all the frames of the video file
        capture >> frame;
        double density;
        string s,fno,den;
        if(getline(file2,s)) {
            istringstream sep(s);
            sep >> fno;
            sep >> den;
            density = stod(den);
        }
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
        std::vector<cv::Mat> blocks1;
        std::vector<cv::Mat> blocks2;
        cv::Mat angleCorrectedImage = changePerspective(grayscale, points);
        cv::Mat croppedImage = cropImage(angleCorrectedImage);
        int divide1 = divideImage(croppedImage, NUM_THREADS, blocks1);
        int divide2 = divideImage(empty, NUM_THREADS, blocks2);
        
        for( i = 0; i < NUM_THREADS; i++ ) {
          //cout <<"main() : creating thread, " << i << endl;
            td[i].ci = blocks1[i];
            td[i].emp = blocks2[i];
          //cout<<"done3"<<"\n";
          rc = pthread_create(&threads[i], NULL, opr1, (void *)&td[i]);
          
          if (rc) {
             cout << "Error:unable to create thread," << rc << endl;
             exit(-1);
          }
       }

       double sum = 0;

       for(int i = 0; i < NUM_THREADS; i++) {
           int a = pthread_join(threads[i], NULL);
           sum += td[i].answer;
       }

        file1 << frame_number << " " << sum << "\n";
        cout << frame_number << " " << sum << "\n";
        //error += abs(sum - density);

        //double queue = getQueue(croppedImage,empty); //stores the queue density
        //double dynamic = getDynamic(croppedImage,previous,empty); //stores the dynamic density
        //cout<<frame_number<<" "<<queue<<" "<<dynamic<<"\n"; //return the values in console
        //file<<frame_number<<" "<<queue<<" "<<dynamic<<"\n"; //return the values in the "out.txt"
        previous = croppedImage; //so that previous points to the previous frame 
        imshow("Density", croppedImage); //video displayed
        frame_number++;
        //Press any key to exit the program
        int keyboard = waitKey(30); 
        if (keyboard >= 65 && keyboard <= 122 || keyboard == 27)
            break;
    }
    file1.close();
    return 0;
}
