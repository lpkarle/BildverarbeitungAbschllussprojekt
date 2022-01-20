//
//  FilterFromHSV.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 20.01.22.
//

#ifndef FilterFromHSV_hpp
#define FilterFromHSV_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class FilterFromHSV
{
private:
    const double RESIZE_FACTOR = 0.7;
    const Rect CENTER_OF_INTEREST = Rect(450, 50, 500, 500);
    const int H_MIN = 12, S_MIN = 46, V_MIN = 248, H_MAX = 49, S_MAX = 198, V_MAX = 255;
    const Scalar YELLOW_HSV_LOWER_THRESH = Scalar(H_MIN, S_MIN, V_MIN);
    const Scalar YELLOW_HSV_UPPER_THRESH = Scalar(H_MAX, S_MAX, V_MAX);
    const int COVER_AREA_MIN = 580, COVER_AREA_MAX = 750;
    
    VideoCapture cameraCapture;
    
    string windowTitleCamera = "Camera Feed";
    string windowTitleCameraBinary = "Camera Feed Binary";
    string windowTitleHSV = "HSV Colors";

    int slider_max = 255;
    int hmin = 0, smin = 0, vmin = 0;
    int hmax = 255, smax = 255, vmax = 255;

    Mat frame, imgResize, imgCrop, imgHSVYellow, imgHSV, dst;
    Mat windowHSVValues;
    
    void onTrackbar(int);
    static void onTrackbar(int, void*);
    
public:
    FilterFromHSV();
    ~FilterFromHSV();
};


#endif /* FilterFromHSV_hpp */
