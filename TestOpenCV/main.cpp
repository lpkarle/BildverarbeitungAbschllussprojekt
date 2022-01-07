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

#include "ui/Window_Bowling.hpp"
#include "ui/CameraFeed.hpp"


using namespace cv;
using namespace std;

// ------------------------------------------------- READ IMAGES
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    
    if (img.empty()) {
        cout << "Image not found or empty!" << endl;
        return 0;
    }
    
    imshow("Image", img);
    waitKey(0); // infinity
    
    return 0;
}
 */

// ------------------------------------------------- READ VIDEO
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/BewegtBild_Uebung3.mp4";
    VideoCapture cap(path);
    
    Mat img;
    
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(20); // 20 ms
    }
    
    return 0;
}
*/

// ------------------------------------------------- READ WEBCAM
/*
int main(int argc, const char * argv[]) {
    
    VideoCapture videoCapture(0);
    
    if (!videoCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
        return -1;
    }
    
    while(true) {
        Mat frame;
        videoCapture >> frame;
        if(frame.empty()) break;
        imshow("Camera feed", frame);
        if (waitKey(10) == 27) break;
    }
    videoCapture.release();
    return 0;
}
*/

// ------------------------------------------------- BASIC IMAGE FUNCTION
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    Mat imgGrey;
    Mat imgBlur;
    Mat imgCanny1, imgCanny2;
    Mat imgDilation, imgErode;
    
    cvtColor(img, imgGrey, COLOR_BGR2GRAY); // --------- to grey
    GaussianBlur(img, imgBlur, Size(3,3), 3, 0); // --------- to grey
    
    // mostly before using cenny a little bit of blur is used
    Canny(imgBlur, imgCanny1, 50, 150);
    Canny(imgBlur, imgCanny2, 25, 75);
    
    // for edge detection "erweitern"
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny1, imgDilation, kernel);
    erode(imgDilation, imgErode, kernel);
    
    if (img.empty()) {
        cout << "Image not found or empty!" << endl;
        return 0;
    }
    
    imshow("Image", img);
    imshow("Image Grey", imgGrey);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny1);
    imshow("Image Canny2", imgCanny2);
    imshow("Image Dilation", imgDilation);
    imshow("Image Erode", imgErode);
    waitKey(0);
    
    return 0;
}
*/

// ------------------------------------------------- RESIZE AND CROP IMG
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    Mat imgResize, imgCrop;
    
    resize(img, imgResize, Size(), 2, 2);
    
    // Crop is important to get information about an region of the img
    // roi -> region of interest (Bildausschnitt erzeugen)
    Rect roi(75, 75, 150, 150);
    imgCrop = imgResize(roi);
    
    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);
 
    waitKey(0);
    
    return 0;
}
*/

// ------------------------------------------------- SHAPES AND TEXT
/*
int main(int argc, const char * argv[]) {
    
    // blank image
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
    
    circle(img, Point(256, 256), 150, Scalar(255,0,0), 10);
    circle(img, Point(256, 256), 50, Scalar(255,0,0), FILLED);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 0, 0), 3);
    line(img, Point(0,0), Point(512, 512), Scalar(0, 255, 255), 20);
    
    putText(img, "well hello there...", Point(50, 50), FONT_ITALIC, 0.75, Scalar(0, 0,255));
    
    imshow("Image", img);
    waitKey(0);
    
    return 0;
}
*/

// ------------------------------------------------- SHAPES AND TEXT
/*
int main(int argc, const char * argv[]) {
    
    string path_without_flash = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/kegeln_1_ohne_blitz.jpg";
    string path_with_flash = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/kegeln_2_mit_blitz.jpg";
    
    Mat img_without_flash = imread(path_without_flash);
    Mat img_with_flash = imread(path_with_flash);
    
    // ----------------------------- color detection
    Mat img_with_flash_HSV, mask;
    cvtColor(img_with_flash, img_with_flash_HSV, COLOR_BGR2HSV);
    // use color range because of lighting effects
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;
    
    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 255);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Hue Max", "Trackbars", &hmax, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    
    
    
    Mat img_without_flash_blur, img_with_flash_blur;
    Mat img_without_flash_canny, img_with_flash_canny;
    Mat img_without_flash_dilation, img_with_flash_dilation;
    Mat img_without_flash_erode, img_with_flash_erode;
    
    GaussianBlur(img_without_flash, img_without_flash_blur, Size(3,3), 3, 0);
    GaussianBlur(img_with_flash, img_with_flash_blur, Size(3,3), 3, 0);
    
    // mostly before using cenny a little bit of blur is used
    Canny(img_without_flash, img_without_flash_canny, 50, 150);
    Canny(img_with_flash, img_with_flash_canny, 50, 150);
    
    // for edge detection "erweitern"
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_without_flash_canny, img_without_flash_dilation, kernel);
    dilate(img_with_flash_canny, img_with_flash_dilation, kernel);
    erode(img_with_flash_dilation, img_with_flash_erode, kernel);
    
    
    
    if (img_without_flash.empty() || img_with_flash.empty()) {
        cout << "Image(s) not found or empty!" << endl;
        return 0;
    }
    
    // imshow("Kegel mit Blitz", img_with_flash);
    // imshow("Kegel ohne Blitz Canny", img_without_flash_canny);
    // imshow("Kegel mit Blitz Canny", img_with_flash_canny);
    // imshow("Kegel ohne Blitz Dilation", img_without_flash_dilation);
    // imshow("Kegel mit Blitz Dilation", img_with_flash_dilation);
    // imshow("Kegel mit Blitz Erode", img_with_flash_erode);
    
    imshow("Kegel mit Blitz HSV", img_with_flash_HSV);
    
    while (true) {
        
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(img_with_flash_HSV, lower, upper, mask);
        
        imshow("Kegel mit Blitz mask", mask);
        
        waitKey(1);
    }
    
    // imshow("Kegel ohne Blitz", img_without_flash);
    // imshow("Kegel mit Blitz", img_with_flash);
    // imshow("Kegel ohne Blitz Canny", img_without_flash_canny);
    // imshow("Kegel mit Blitz Canny", img_with_flash_canny);
    // imshow("Kegel ohne Blitz Dilation", img_without_flash_dilation);
    // imshow("Kegel mit Blitz Dilation", img_with_flash_dilation);
    //imshow("Kegel mit Blitz Erode", img_with_flash_erode);
    
    // imshow("Kegel mit Blitz HSV", img_with_flash_HSV);
    // imshow("Kegel mit Blitz mask", mask);
    
    
    // waitKey(0); // infinity
    
    return 0;
}
*/

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
    
    
    inRange(src_crop, lower, upper, dst);
    
    rectangle(hsv_values, Point(0, 0), Point(200, 500), Scalar(255, 255, 255), FILLED);
    putText(hsv_values, "hmin: " + to_string(hmin), Point(5, 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "hmax: " + to_string(hmax), Point(5, 50), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0,255));
    putText(hsv_values, "smin: " + to_string(smin), Point(5, 75), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "smax: " + to_string(smax), Point(5, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "vmin: " + to_string(vmin), Point(5, 125), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(hsv_values, "vmax: " + to_string(vmax), Point(5, 150), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
   
    imshow( "window_title", hsv_values );
    imshow( "original", src_resized);
    imshow( window_title, dst );
}

int main( void )
{
    //src = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/kegeln_2_mit_blitz.jpg");
    src = imread("/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/kegeln_farben.jpg");
    if( src.empty() ) { cout << "Error loading src1 \n"; return -1; }
    
    // Resize the img
    resize(src, src_resized, Size(), 0.1, 0.1);
    
    // Center the field
    Rect roi(50, 50, 300, 300);
    src_crop = src_resized(roi);
    
    
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
    
    kegel_window = Mat(512, 512, CV_8UC3, Scalar(225, 225, 225));
    
    
    circle(kegel_window, Point(257, 65), 21, Scalar(200, 200, 200), FILLED);  // shadow
    circle(kegel_window, Point(256, 64), 20, Scalar(255, 255, 255), FILLED);  // kegel
    circle(kegel_window, Point(256, 64), 8, Scalar(0, 0, 255), FILLED);       // deckel
    circle(kegel_window, Point(256, 64), 22, Scalar(200, 200, 200), FILLED);  // knocked down
    
    circle(kegel_window, Point(65, 257), 21, Scalar(200, 200, 200), FILLED);
    circle(kegel_window, Point(64, 256), 20, Scalar(255, 255, 255), FILLED);
    circle(kegel_window, Point(64, 256), 8, Scalar(0, 0, 255), FILLED);
    
    circle(kegel_window, Point(449, 257), 21, Scalar(200, 200, 200), FILLED);
    circle(kegel_window, Point(448, 256), 20, Scalar(255, 255, 255), FILLED);
    circle(kegel_window, Point(448, 256), 8, Scalar(0, 0, 255), FILLED);
    
    circle(kegel_window, Point(257, 449), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(256, 448), 20, Scalar(255, 255, 255), FILLED);
    circle(kegel_window, Point(256, 448), 8, Scalar(0,0,255), FILLED);
    
    circle(kegel_window, Point(257, 257), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(256, 256), 20, Scalar(255,255,255), FILLED);
    circle(kegel_window, Point(256, 256), 8, Scalar(0,0,255), FILLED);
    
    circle(kegel_window, Point(161, 161), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(160, 160), 20, Scalar(255,255,255), FILLED);
    circle(kegel_window, Point(160, 160), 8, Scalar(0,0,255), FILLED);
    
    circle(kegel_window, Point(161, 353), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(160, 352), 20, Scalar(255, 255, 255), FILLED);
    circle(kegel_window, Point(160, 352), 8, Scalar(0,0,255), FILLED);
    
    circle(kegel_window, Point(353, 161), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(352, 160), 20, Scalar(255,255,255), FILLED);
    circle(kegel_window, Point(352, 160), 8, Scalar(0,0,255), FILLED);
    
    circle(kegel_window, Point(353, 353), 21, Scalar(200,200,200), FILLED);
    circle(kegel_window, Point(352, 352), 20, Scalar(255,255,255), FILLED);
    circle(kegel_window, Point(352, 352), 8, Scalar(0,0,255), FILLED);
    
    
    imshow("Kegel", kegel_window);
   
    waitKey(0);
    return 0;
}
*/

// ------------------------------------------------- WEBCAM

int main(int argc, const char * argv[]) {
    
    WindowBowling windowBowling;
    
    windowBowling.knockDownPin(2);
    
    CameraFeed cameraFeed;
    return 0;
}
