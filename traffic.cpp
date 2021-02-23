#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

struct userdata{
    Mat im;
    vector<Point2f> points;
};


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
    cvtColor(im_rgb,im_gray,COLOR_RGB2GRAY);
}

int main( int argc, char** argv)
{

    // Read source image.
    Mat im_src = imread("empty.jpg",IMREAD_GRAYSCALE);

    // Destination image. The aspect ratio of the book is 3/4
    Size size(338,778);
    Mat im_dst = Mat::zeros(size,CV_8UC3);

    // Create a vector of destination points.
    vector<Point2f> points;

    points.push_back(Point2f(0,0));
    points.push_back(Point2f(size.width - 1, 0));
    points.push_back(Point2f(size.width - 1, size.height -1));
    points.push_back(Point2f(0, size.height - 1 ));

    // Set data for mouse event
    Mat im_temp = im_src.clone();
    userdata data;
    data.im = im_temp;

    cout << "Click on the four corners of the book -- top left first and" << endl
    << "bottom left last -- and then hit ENTER" << endl;

    // Show image and wait for 4 clicks.
    imshow("Image", im_temp);
    // Set the callback function for any mouse event
    setMouseCallback("Image", mouseClick, &data);
    waitKey(0);

    // Calculate the homography
    Mat h = findHomography(data.points, points);

    // Warp source image to destination
    warpPerspective(im_src, im_dst, h, size);

    // Show image
    imshow("Image", im_dst);
    waitKey(0);
    return 0;
}
