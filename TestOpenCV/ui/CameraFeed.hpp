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
#include "WindowBowling.hpp"

using namespace cv;
using namespace std;


const Point locationBtnNextPlayer[ 2 ] = { Point(290, 80), Point(330, 105) };
const Point locationBtnNextRound[ 2 ]  = { Point(385, 80), Point(425, 105) };

const vector<Point> pinAreas =  // 1 to 9
{
    Point(200, 65),
    Point(120, 146),
    Point(280, 146),
    Point( 40, 228),
    Point(200, 228),
    Point(355, 228),
    Point(120, 310),
    Point(280, 310),
    Point(200, 390)
};

const int pinBoxWidth = 75, pinBoxHeight = 75;


class CameraFeed
{
private:
    VideoCapture cameraCapture;
    
    int key_pressed;
    
    vector<Mat> preprocessImage(Mat frame);
    
    int hmin, smin, vmin, hmax, smax, vmax;
    int detectBottles(Mat hsvImage);
    void detectDots(Mat hsvImage);
    
    vector<vector<Point>> getContours(Mat img);
    vector<vector<Point>> getBottleContours(vector<vector<Point>> contours);
    vector<int> pinsUp(vector<vector<Point>> circleContours, Mat img);
    
    int onMouse(int event, int x, int y);
    static void onMouse(int event, int x, int y, int, void* userdata);
    
    
    // test
    void bottleLocation(Mat img);
    
public:
    CameraFeed(WindowBowling windowBowling);
    ~CameraFeed();
};


#endif /* CameraFeed_hpp */
