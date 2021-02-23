#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

/*struct userdata{
    Mat im;
    vector<Point2f> points;
};*/


void mouseClick(int event, int x, int y, int flags, void* data_ptr)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        userdata *data = ((userdata *) data_ptr);
        circle(data->im, Point(x,y),3,Scalar(0,0,255), 5, cv::LINE_AA);
        imshow("Original Image", data->im);
        if (data->points.size() < 4)
        {
            data->points.push_back(Point2f(x,y));
        }
    }
}

void rgb2grayscale(string img)
{
    Mat im_rgb  = imread(img);
    Mat im_gray;
    cvtColor(im_rgb,im_gray,CV_RGB2GRAY);
}

int main( int argc, char** argv)
{

    // Read source image.
    Mat im_src = imread("empty.jpg",CV_LOAD_IMAGE_GRAYSCALE);

    return 0;
}