//
//  main.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 15.10.21.
//
#include <iostream>
#include "logic/GameManager.hpp"


/*
// ------------------------------- FILTER HSV COLORS FROM WEBCAM
string windowTitleCamera = "Camera Feed";
string windowTitleCameraBinary = "Camera Feed Binary";
string windowTitleHSV = "HSV Colors";

int slider_max = 255;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

Mat frame, imgResize, imgCrop, imgHSVYellow, imgHSV, dst;
Mat windowHSVValues;


void on_trackbar(int i, void* data)
{
    cout << "ontrackbar" << endl;
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    
    
    inRange(imgHSV, lower, upper, dst);
    
    rectangle(windowHSVValues, Point(0, 0), Point(200, 500), Scalar(255, 255, 255), FILLED);
    putText(windowHSVValues, "H_Min: " + to_string(hmin), Point(5, 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "H_Max: " + to_string(hmax), Point(5, 50), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0,255));
    putText(windowHSVValues, "smin: " + to_string(smin), Point(5, 75), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "smax: " + to_string(smax), Point(5, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "vmin: " + to_string(vmin), Point(5, 125), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "vmax: " + to_string(vmax), Point(5, 150), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
   
    imshow( windowTitleHSV, windowHSVValues );
    imshow( windowTitleCamera, imgCrop);
    imshow( windowTitleCameraBinary, dst );
}

int main( void )
{
    VideoCapture cameraCapture;
    namedWindow(windowTitleCameraBinary, WINDOW_AUTOSIZE);
    windowHSVValues = Mat(200, 200, CV_8UC3, Scalar(255, 255, 255));
    
    while (!cameraCapture.isOpened())
    {
        cameraCapture = VideoCapture(1);
    }
    
    while (true)
    {
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        resize(frame, imgResize, Size(), 0.7, 0.7);
        imgCrop = imgResize(Rect(450, 50, 500, 500));
        cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);
        
        createTrackbar("H_Min", windowTitleCameraBinary, &hmin, slider_max, on_trackbar );
        createTrackbar("H_Max", windowTitleCameraBinary, &hmax, slider_max, on_trackbar );
        createTrackbar("S_Min", windowTitleCameraBinary, &smin, slider_max, on_trackbar );
        createTrackbar("S_Max", windowTitleCameraBinary, &smax, slider_max, on_trackbar );
        createTrackbar("V_Min", windowTitleCameraBinary, &vmin, slider_max, on_trackbar );
        createTrackbar("V_Max", windowTitleCameraBinary, &vmax, slider_max, on_trackbar );
        
        on_trackbar( hmin, 0 );
        on_trackbar( hmax, 0 );
        on_trackbar( smin, 0 );
        on_trackbar( smax, 0 );
        on_trackbar( vmin, 0 );
        on_trackbar( vmax, 0 );
            
        if (waitKey(10) == 27) break;
    }
    
    return 0;
}
*/

int main(int argc, const char * argv[])
{
    GameManager gameManager;
    return 0;
}
