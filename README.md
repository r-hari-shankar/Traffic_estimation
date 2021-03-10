# Traffic Density Estimation

## Camera angle correction and frame cropping
We have used the concept of homography using OpenCV to create a C++ program which takes the four points of the image (road) to change perspective such that we get the top view of the road by warping the image with 4 points of rectangle which corrects the angle of camera as if viewing from the top .The cropping of the image is done by using the inbuilt function of OpenCV which allows us to crop the image by providing the starting point and the length and breadth of the needed region. We have implemented abstraction as much as possible so that these functions can be used for other programs as well. 

## Queue and Dynamic Density estimation
We have used the concept of background subtraction and optical flow across different frames to compute the queue and dynamic densities. For this we have taken the help of angle correction and cropping functions to get a top view of the road from the video file and computed the densities according to the pixel changes in the images. The densities calculated are saved in the file "out.txt".  
A make file is provided to make the job of running the program easier for the user .
We have tried to make the code as understandable as possible by adding the comments wherever required.

## How to execute the program
Follow these simple steps to execute the program
1) In terminal write cd "path of the program folder" to change to the folder containing the program files.
2) Make sure the video files whose Queue and Dynamic Density to be calculated are in the same directory, if not transfer the video files to the current directory.
3) <i> Type "make" in the terminal without quotes.
4) Type "./traffic_density.out <video_name.extension>" <br>
    <t> eg) ./traffic_density.out trafficvideo.mp4 <br>
    <t> Note: if improper or no input is provided, an error will be shown.</i>
5) The above inputs will run the program and the "framenum, queue density, dynamic density"  values will be shown in both the console and will also be stored in the file "out.txt" which will be used to plot the graph .
6) Press any key to exit the program . The density values are stored in "out.txt" for future references.
7) Type "make clean" in the terminal to clear all the object files. 
