# Traffic Density Estimation

## Camera angle correction and frame cropping

## How to execute the program
Follow these simple steps to execute the program
1) In terminal write cd "path of the program folder" to change to the folder containing the program files.
2) Make sure the image files whose angle correction and frame cropping to be done are in the same folder, if not transfer those images to this program containing file.
3) <i> Type "make" in the terminal without quotes.
4) Type "./traffic_estimation.out <image_name.extension>" <br>
    </t> eg) ./traffic_estimation.out empty.jpg <br>
    </t>   Note: if improper or no imput is provided an error will be shown.</i>
5) The above inputs will run the program and the user will be prompted to mark the 4 points on which angle correction and frame cropping is to be performed.
6) If the above process was performed for an image containing traffic then press the key "T" on your keyboard to view the 2 transformed images which are also saved in the same folder as perspective_traffic.jpg and cropped_traffic.jpg and the program will exit.
7) If the above process was performed for an image containing empty road then press the key "E" or any key except "T" on your keyboard to view the 2 transformed images which are also saved in the same folder as perspective_empty.jpg and cropped_empty.jpg and the program will exit.
