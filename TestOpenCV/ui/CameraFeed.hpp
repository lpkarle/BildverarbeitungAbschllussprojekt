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
#include "WindowBowling.hpp"

using namespace cv;


class CameraFeed
{
private:
    // constants image preproccessing
    const double RESIZE_FACTOR = 0.7;
    const Rect CENTER_OF_INTEREST = Rect(450, 50, 500, 500);
    const int H_MIN = 12, S_MIN = 46, V_MIN = 248, H_MAX = 49, S_MAX = 198, V_MAX = 255;
    const Scalar YELLOW_HSV_LOWER_THRESH = Scalar(H_MIN, S_MIN, V_MIN);
    const Scalar YELLOW_HSV_UPPER_THRESH = Scalar(H_MAX, S_MAX, V_MAX);
    const int COVER_AREA_MIN = 580, COVER_AREA_MAX = 750;
    
    // constants bottle/pin location
    const vector<Point> PIN_AREAS =  // pin 1 to 9
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
    const int PIN_BOX_SIZE = 100;
    
    VideoCapture cameraCapture;
    int key_pressed;
    
    vector<Mat> preprocessImageDilation(Mat frame);
    vector<vector<Point>> getImageContours(Mat img);
    vector<vector<Point>> filterCircleContourByAreaAndCornerPoints(vector<vector<Point>> contours);
    vector<int> getStandingPins(vector<vector<Point>> circleContours, Mat img);
    void markPinLocationWithRect(Mat img);
    
public:
    CameraFeed();
    ~CameraFeed();
    
    vector<int> startReceivingPinsUp();
};


#endif /* CameraFeed_hpp */
