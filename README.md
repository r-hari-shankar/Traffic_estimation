# Traffic Density Estimation

## Camera angle correction and frame cropping
We have used the concept of homography using OpenCV to create a C++ program which takes the four points of the image (road) to change perspective such that we get the top view of the road by warping the image with 4 points of rectangle which corrects the angle of camera as if viewing from the top .The cropping of the image is done by using the inbuilt function of OpenCV which allows us to crop the image by providing the starting point and the length and breadth of the needed region. We have implemented abstraction as much as posible so that these functions can be used for other programs as well. A make file is provided to make the job of running the program easier for the user .
We have tried to make the code as understandable as possible by adding the comments wherever required.

## How to execute the program
Follow these simple steps to execute the program
1) In terminal write cd "path of the program folder" to change to the folder containing the program files.
2) Make sure the image files whose angle correction and frame cropping to be done are in the same folder, if not transfer those images to this program containing file.
3) <i> Type "make" in the terminal without quotes.
4) Type "./traffic_estimation.out <image_name.extension>" <br>
    <t> eg) ./traffic_estimation.out empty.jpg <br>
    <t> Note: if improper or no imput is provided an error will be shown.</i>
5) The above inputs will run the program and the user will be prompted to mark the 4 points on which angle correction and frame cropping is to be performed.
6) Press any key to view the perspective and cropped images .These images are also stored in the file locally on your system.
7) Use "make clean" command to remove the object files.
