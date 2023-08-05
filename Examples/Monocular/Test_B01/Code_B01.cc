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
#include <thread>
#include <atomic>

using namespace cv;
using namespace std;

std::atomic<bool> f1(true); // Keep running
std::atomic<bool> f2(false); // Show current timestamp

void WaitForInput();
void getUserInput();

int main(int argc, char* argv[]) {
    std::cout << "====================Start Program====================" << std::endl;

    if(argc != 3)
    {
        cerr << endl << "Usage: ./mono_tum path_to_vocabulary path_to_settings" << endl;
        return 1;
    }

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    std::cout << "====================Start SLAM Setting====================" << std::endl;
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);


    VideoCapture cap(0);
    if(!cap.isOpened()){
        cout << "Error opening video stream" << endl;
        return -1;
    }


    // Set frame width and height
    cap.set(CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(CAP_PROP_FRAME_HEIGHT, 720);
    

    std::thread inputThread(getUserInput);    

    std::cout << std::fixed << std::setprecision(6); 

    int index = 0;
    while(true)
    {
	Mat img;
        cap >> img;

	// Get the current time
	auto now = std::chrono::system_clock::now();

	// Convert it to a time_point for the Epoch (1970-01-01 00:00:00)
	auto epoch = now.time_since_epoch();

	// Convert that to seconds
        std::chrono::duration<double> seconds = std::chrono::duration_cast<std::chrono::duration<double>>(epoch);

	// Convert to a double
	double tframe = seconds.count();
	
        if (f2) 
	    std::cout << "Index: " << index << " ; Frame Timestamp: " << tframe << std::endl;

        // Check if the image was successfully read
        if(img.empty())
        {
            std::cerr << "ERROR: Unable to read the image\n";
            return 1;
        }

	SLAM.TrackMonocular(img,tframe);

        usleep(5);

	if (!f1) 
	    break;
 
        index++;
    }
    std::cout << "====================End Loop====================" << std::endl;

    SLAM.Shutdown();
    std::cout << "====================End SLAM====================" << std::endl;

    // When everything done, release the video capture object
    cap.release();


    // Closes all the frames
    destroyAllWindows();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("Examples/Monocular/Test_B01/Code_B01_KeyFrameTrajectory.txt");
    cout << "Save trajectory" << endl;

    // Save camera trajectory
    //SLAM.SaveTrajectoryTUM("CameraTrajectory_copy.txt");
    //cout << "Save trajectory" << endl;

    inputThread.join();

    std::cout << "====================End Program====================" << std::endl;

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

void getUserInput() {
    char c;
    while (true) {
        std::cin >> c;
        if (c == 'q') {
            f1 = !f1;
            break;
        }
	if (c == 't') {
            f2 = !f2;
        }
    }
}
