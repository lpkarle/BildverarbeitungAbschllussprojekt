//
//  CameraFeed.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#ifndef CameraFeed_hpp
#define CameraFeed_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Window_Bowling.hpp"

using namespace cv;
using namespace std;

class CameraFeed
{
private:
    VideoCapture cameraCapture;
    
    int key_pressed;
    
    int hmin, smin, vmin, hmax, smax, vmax;
    int detectBottles(Mat hsvImage);
    void detectDots(Mat hsvImage);
    
    vector<vector<Point>> getContoures(Mat imgSrc, Mat imgDest);
    
public:
    CameraFeed(WindowBowling windowBowling);
    ~CameraFeed();
};


#endif /* CameraFeed_hpp */
