//
//  main.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 15.10.21.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/opencv.hpp>
#include <iostream>

#include "ui/WindowWelcome.hpp"
#include "ui/Window_Bowling.hpp"
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


// ------------------------------------------------- WEBCAM

/*
int key_pressed;
bool runtime = true;

int amountPlayers = 0;
int amountRounds = 0;

void updateWindow(Mat currentWindow)
{
    imshow(WINDOW_NAME, currentWindow);
}

void cancelCallback()
{
    runtime = false;
    key_pressed = 27;
    cout << "Cancel Callback!" << endl;
    cout << runtime << endl;
}

void playCallback()
{
    runtime = false;
    key_pressed = 27;
    cout << "Cancel Callback!" << endl;
    cout << runtime << endl;
}



int main(int argc, const char * argv[]) {
    
    
    CameraFeed cameraFeed;
    
    
    
    cout << "Worked !" << endl;
    
    
    //CameraFeed cameraFeed;
    
  
    // ---- Player and Rounds
    
    /*WindowWelcome windowWelcome(cancelCallback);
    
    key_pressed = waitKey(0);
    
    switch(key_pressed)
    {
            
        case 27: // esc
            cout << "ESC" << endl;
            destroyWindow("window_welcome");
            break;
                
        case 13: // Enter
            cout << "Enter" << endl;
            
            amountPlayers = windowWelcome.getNrOfPlayers();
            amountRounds = windowWelcome.getNrOfRounds();
            
            destroyWindow("window_welcome");
            
            cout << "players: " << amountPlayers << "; rounds: " << amountRounds << endl;
            break;
    }
    
    
    // ---- Game
    
    //WindowBowling windowBowling;
    
    
    key_pressed = waitKey(0);
    
    switch(key_pressed)
        
    {
            
        case 27: // esc
            cout << "ESC" << endl;
            destroyWindow("window_welcome");
            break;
                
        case 13: // Enter
            cout << "Enter" << endl;
            
            amountPlayers = windowWelcome.getNrOfPlayers();
            amountRounds = windowWelcome.getNrOfRounds();
            
            destroyWindow("window_welcome");
            
            cout << "players: " << amountPlayers << "; rounds: " << amountRounds << endl;
            break;
    }
    
    return 0;
}

*/


void get_contours(Mat img_dilation, Mat img_destination)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(img_dilation, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(img_destination, contours, -1, Scalar(0, 0, 0), 3);
    
    // filter area
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;
        
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        
        string objType;
        
        if (area > 11000)
        {
            float parameter = arcLength(contours[i], true);
            
            approxPolyDP(contours[i], conPoly[i], 0.02 * parameter, true);
            drawContours(img_destination, conPoly, i, Scalar(255, 0, 255), 2);
            
            cout << conPoly.size() << endl;
            
            boundRect[i] = boundingRect(conPoly[i]);
            //rectangle(img_destination, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            
            int objCornerPoints = (int) conPoly[i].size();
            
            switch (objCornerPoints)
            {
                case 3:
                    cout << "Triangle" << endl;
                    objType = "Triangle";
                case 4:
                    cout << "Rectangle" << endl;
                    objType = "Rectangle";
                default:
                    cout << "Circle" << endl;
                    objType = "Circle";
            }
            
            putText(img_destination, objType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0,0,0));
        }
    }
}

int main( void )
{
    Mat src_dots_hsv = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/bowling_dots.png");
    Mat src_bottles_hsv = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/bowling_22_01_12.png");
    //imshow("src_dots_hsv", src_dots_hsv);
    //imshow("src_bottles_hsv", src_bottles_hsv);
        
    Mat src_shapes = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/shapes.png");
    imshow("shapes", src_shapes);
    
    Mat img_grey, img_blur, img_canny, img_dilation, img_erode;
    
    // --------- Preprocessing
    cvtColor(src_shapes, img_grey, COLOR_BGR2GRAY);
    GaussianBlur(img_grey, img_blur, Size(3, 3), 3, 0);
    Canny(img_blur, img_canny, 25, 75);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_canny, img_dilation, kernel);
    erode(img_dilation, img_erode, kernel);
    
    get_contours(img_dilation, src_shapes);
    imshow("contours", src_shapes);
    
    //imshow("shapes grey", img_grey);
    //imshow("shapes blur", img_blur);
    //imshow("shapes canny", img_canny);
    //imshow("shapes dilation", img_dilation);
    //imshow("shapes erode", img_erode);
    
    
   
    waitKey(0);
    return 0;
}
