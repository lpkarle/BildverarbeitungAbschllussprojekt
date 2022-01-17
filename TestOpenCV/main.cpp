//
//  main.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 15.10.21.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "logic/GameManager.hpp"
#include "ui/WindowWelcome.hpp"
#include "ui/WindowBowling.hpp"
#include "ui/CameraFeed.hpp"
#include "Constants.cpp"


using namespace cv;
using namespace std;


// --------------------------------------- GET HSV COLORS
/*
string window_title = "HSV Colors";
const int slider_max = 255;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 255, smax = 255, vmax = 255;

Mat src, src_resized, src_crop;
Mat dst;
Mat hsv_values;

Mat kegel_window;

void on_trackbar( int, void* )
{
    cout << "ontrackbar" << endl;
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    
    
    inRange(src, lower, upper, dst);
    
    rectangle(hsv_values, Point(0, 0), Point(200, 500), Scalar(255, 255, 255), FILLED);
    putText(hsv_values, "hmin: " + to_string(hmin), Point(5, 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "hmax: " + to_string(hmax), Point(5, 50), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0,255));
    putText(hsv_values, "smin: " + to_string(smin), Point(5, 75), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "smax: " + to_string(smax), Point(5, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "vmin: " + to_string(vmin), Point(5, 125), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "vmax: " + to_string(vmax), Point(5, 150), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
   
    imshow( "window_title", hsv_values );
    imshow( "original", src);
    imshow( window_title, dst );
}

int main( void )
{
    src = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/bowling_dots.png");
    if( src.empty() ) { cout << "Error loading src1 \n"; return -1; }
    
    
    // Window for displaying HSV values
    hsv_values = Mat(200, 200, CV_8UC3, Scalar(255, 255, 255));
    
    namedWindow(window_title, WINDOW_AUTOSIZE); // Create Window
    
    createTrackbar("hmin", window_title, &hmin, slider_max, on_trackbar );
    createTrackbar("hmax", window_title, &hmax, slider_max, on_trackbar );
    createTrackbar("smin", window_title, &smin, slider_max, on_trackbar );
    createTrackbar("smax", window_title, &smax, slider_max, on_trackbar );
    createTrackbar("vmin", window_title, &vmin, slider_max, on_trackbar );
    createTrackbar("vmax", window_title, &vmax, slider_max, on_trackbar );
    
    on_trackbar( hmin, 0 );
    on_trackbar( hmax, 0 );
    on_trackbar( smin, 0 );
    on_trackbar( smax, 0 );
    on_trackbar( vmin, 0 );
    on_trackbar( vmax, 0 );

   
    waitKey(0);
    return 0;
}*/


int main(int argc, const char * argv[])
{
    GameManager gameManager;
    return 0;
}
