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
    Point(175, 365),
    Point(95 , 285),
    Point(255, 285),
    Point( 15, 203),
    Point(175, 203),
    Point(330, 203),
    Point( 95, 121),
    Point(255, 121),
    Point(175,  40)
};

const int pinBoxWidth = 100, pinBoxHeight = 100;


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
    
    // test
    void bottleLocation(Mat img);
    
public:
    CameraFeed();
    ~CameraFeed();
    
    vector<int> start();
};


#endif /* CameraFeed_hpp */
