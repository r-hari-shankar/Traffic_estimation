#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//used to store the selected points and the image
struct userdata{
    Mat im;
    vector<Point2f> points;
};

//clickEvent given in another function as it may be needed in abstraction for future functions
bool clickEvent(int cursor){
	if(cursor == EVENT_LBUTTONDOWN){
		return true;
	}
	else 
		return false;
	return false;
}

void mouseClick(int event, int x, int y, int flags, void* data_ptr)
{
    if  ( clickEvent(event) )//checks for mouse click
    {
        userdata *data = ((userdata *) data_ptr);
        circle(data->im, Point(x,y),3,Scalar(0,0,255), 5, cv::LINE_AA); //properties of circle
        imshow("Original Image", data->im); //displays image for selection of the four points
        if (data->points.size() < 4)
        {
            data->points.push_back(Point2f(x,y)); //stores the four selected point as reference pointers in data
        }
    }
}

/*void rgb2grayscale(string img)
{
    Mat im_rgb  = imread(img);
    Mat im_gray;
    cvtColor(im_rgb,im_gray,CV_RGB2GRAY);
}*/

int main( int argc, char** argv)
{

    // Read source image.
    Mat source = imread("empty.jpg", cv::COLOR_BGR2GRAY);
    //creating clone of the original image
    Mat temp = source.clone();
    // Set data for mouse event
    userdata data;
    data.im = temp;

    cout << "Click points in clockwise manner starting from top left" << endl;
    // Show image and wait for 4 clicks.
    imshow("Image", temp);
    // Set the callback function for any mouse event
    setMouseCallback("Image", mouseClick, &data);
    waitKey(0);
    return 0;
}