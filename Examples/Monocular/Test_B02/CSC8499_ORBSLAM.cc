#include<iostream>
#include<chrono>
#include<System.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<thread>
#include<atomic>

using namespace cv;
using namespace std;

std::atomic<bool> endLoopFlag(false);
std::atomic<bool> printTimeFlag(false);

void getUserInput() {
    char c;
    while (!endLoopFlag) {
        std::cin >> c;
        if (c == 'q') 
            endLoopFlag = !endLoopFlag;
	if (c == 't') {
            printTimeFlag = !printTimeFlag;
        }
    }
}
 
int main(int argc, char* argv[]) {
    if(argc != 3)
        return 1;

    std::thread inputThread(getUserInput); 
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::MONOCULAR,true);
    cv::VideoCapture cap(0);
    
    while(!endLoopFlag)
    {
	Mat img;
        cap >> img;
	auto now = std::chrono::system_clock::now();
	auto epoch = now.time_since_epoch();
        std::chrono::duration<double> seconds = std::chrono::duration_cast<std::chrono::duration<double>>(epoch);
	double tframe = seconds.count();

	if(img.empty())
            return 1;
	if (printTimeFlag)
	    std::cout << std::fixed << std::setprecision(6) << "Current Time: " << tframe << std::endl;
	SLAM.TrackMonocular(img,tframe);

        usleep(5);
    }

    SLAM.Shutdown();
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");
    cap.release();
    inputThread.join();

    return 0;
}
