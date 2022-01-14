//
//  CameraFeed.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "CameraFeed.hpp"

CameraFeed::CameraFeed(WindowBowling windowBowling)
{
    while (!cameraCapture.isOpened())
    {
        cameraCapture = VideoCapture(1);
    }
        
    while(true) {
        
        Mat frame, frameResize, frameHSV;
        
        Mat frameBlur, frameCanny, frameDilation, frameErode, dst;
        
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        // Resize the img
        resize(frame, frameResize, Size(), 0.7, 0.7);
        // Center the field
        Rect roi(450, 50, 500, 500);
        frameCrop = frameResize(roi);
        bottleLocation();
        
        cvtColor(frameCrop, frameHSV, COLOR_BGR2HSV);
        
        
        
        int bottles_up = detectBottles(frameHSV);
        
        cout << "-------------- bottles ----> " << bottles_up << endl;
    
        
        detectDots(frameHSV);
        
        
        imshow("Camera", frameCrop);
        
        
        if (waitKey(10) == 27) break;
    
    }
}


CameraFeed::~CameraFeed()
{
    cameraCapture.release();
}


int CameraFeed::detectBottles(Mat hsvImage)
{
    Mat img_dst, img_blur, img_canny, img_dilation, img_erode;
    
    // Yellow
    hmin = 12; smin = 46; vmin = 248;
    hmax = 49; smax = 198; vmax = 255;
    
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(hsvImage, lower, upper, img_dst);
    
    GaussianBlur(img_dst, img_blur, Size(3,3), 3, 0);
    
    // mostly before using cenny a little bit of blur is used
    Canny(img_blur, img_canny, 50, 150);
    
    // for edge detection "erweitern"
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_canny, img_dilation, kernel);
    erode(img_dilation, img_erode, kernel);
    
    //imshow("Camera Canny Bottles", img_canny);
    imshow("Camera dilation", img_dilation);
    //imshow("Camera erode Bottles", img_erode);
    
    return (int) getBottleContours(getContours(img_dilation), hsvImage).size();
}


void CameraFeed::detectDots(Mat hsvImage)
{
    Mat img_dst, img_blur, img_canny, img_dilation, img_erode;

    // dots
    hmin = 0; smin = 0; vmin = 175;
    hmax = 255; smax = 146; vmax = 255;
    
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(hsvImage, lower, upper, img_dst);
    
    GaussianBlur(img_dst, img_blur, Size(3,3), 3, 0);
    
    // mostly before using cenny a little bit of blur is used
    Canny(img_blur, img_canny, 50, 150);
    
    // for edge detection "erweitern"
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(img_canny, img_dilation, kernel);
    erode(img_dilation, img_erode, kernel);
    
    //imshow("Camera Canny Dots", img_canny);
    //imshow("Camera dst Dots", img_dst);
    ///imshow("Camera erode Dots", img_erode);
}

vector<vector<Point>> CameraFeed::getContours(Mat imgSrc)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    return contours;
}


vector<vector<Point>> CameraFeed::getBottleContours(vector<vector<Point>> contours, Mat imgDest)
{
    int count = 0;
    vector<vector<Point>> contourCircle(contours.size());
    vector<Rect> boundRect(contours.size());
    
    // filter area
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;
        
        string objType;
        
        if (area >= 580 && area <= 660)
        {
            float parameter = arcLength(contours[i], true);
            
            approxPolyDP(contours[i], contourCircle[i], 0.02 * parameter, true);
            int objCornerPoints = (int) contourCircle[i].size();
            
            if (objCornerPoints > 4)
            {
                count++;
                drawContours(imgDest, contourCircle, i, Scalar(0, 0, 0), 2);
                boundRect[i] = boundingRect(contourCircle[i]);
                rectangle(imgDest, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
                putText(imgDest, "Circle", {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0,0,0));
            }
        }
    }
    imshow("Camera HSV", imgDest);
    
    return contourCircle;
}



// TEST
void CameraFeed::bottleLocation()
{
    int lenX = 75, lenY = 75;
    
    Point pin1 = Point(200, 65);
    Point pin2 = Point(120, 150);
    Point pin3 = Point(280, 150);
    Point pin4 = Point(40,  230);
    Point pin5 = Point(200, 230);
    Point pin6 = Point(355, 230);
    Point pin7 = Point(120, 310);
    Point pin8 = Point(280, 310);
    Point pin9 = Point(200, 385);
    
    
    rectangle(frameCrop, pin1, {pin1.x + lenX, pin1.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin2, {pin2.x + lenX, pin2.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin3, {pin3.x + lenX, pin3.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin4, {pin4.x + lenX, pin4.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin5, {pin5.x + lenX, pin5.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin6, {pin6.x + lenX, pin6.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin7, {pin7.x + lenX, pin7.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin8, {pin8.x + lenX, pin8.y + lenY}, Scalar(0, 0, 255), 1);
    rectangle(frameCrop, pin9, {pin9.x + lenX, pin9.y + lenY}, Scalar(0, 0, 255), 1);
}
