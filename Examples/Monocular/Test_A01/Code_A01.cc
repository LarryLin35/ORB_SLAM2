#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include<System.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include <sstream>

using namespace cv;
using namespace std;

void WaitForInput();

int main(int argc, char* argv[]) {
    std::cout << "====================Start=====================" << std::endl;

    WaitForInput();

    VideoCapture cap(0);
    if(!cap.isOpened()){
        cout << "Error opening video stream" << endl;
        return -1;
    }


    // Set frame width and height
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    int index = 0;
    while(1){
        Mat frame;

        // Capture frame-by-frame
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Display the resulting frame
        imshow( "Live Video", frame );

	// Press 'e' on keyboard to exit
	// Press 'm' on keyboard to save an image
        char c=(char)waitKey(25);
        if(c=='q')  
            break;
	if(c=='m'){  
            std::ostringstream filename;
            filename << "/home/lin/ORB_SLAM2/Examples/Monocular/Test_A01/Image/" << index << ".png";
            cv::imwrite(filename.str(), frame);
	}


        index++;
    }


    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    std::cout << "====================End====================" << std::endl;

    return 0;
}


void WaitForInput()
{
    while (true) {
        std::cout << "Input: ";
        char c; std::cin >> c;
        if (c == 'n')
            break;
    }
}
