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


const Point locationBtnNextPlayer[ 2 ] = { Point(290, 80), Point(330, 105) };
const Point locationBtnNextRound[ 2 ]  = { Point(385, 80), Point(425, 105) };

class CameraFeed
{
private:
    VideoCapture cameraCapture;
    Mat frameCrop;
    Mat button_grp;
    
    int key_pressed;
    
    int hmin, smin, vmin, hmax, smax, vmax;
    int detectBottles(Mat hsvImage);
    void detectDots(Mat hsvImage);
    
    vector<vector<Point>> getContours(Mat imgSrc);
    vector<vector<Point>> getBottleContours(vector<vector<Point>> contours, Mat imgDest);
    
    int onMouse(int event, int x, int y);
    static void onMouse(int event, int x, int y, int, void* userdata);
    
    
    // test
    void bottleLocation();
    
public:
    CameraFeed(WindowBowling windowBowling);
    ~CameraFeed();
};


#endif /* CameraFeed_hpp */
