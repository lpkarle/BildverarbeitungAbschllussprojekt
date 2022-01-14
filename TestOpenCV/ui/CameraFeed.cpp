//
//  CameraFeed.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "CameraFeed.hpp"

CameraFeed::CameraFeed(void)
{
    while (!cameraCapture.isOpened())
    {
        cameraCapture = VideoCapture(1);
    }
    
    while(true) {
        
        Mat frame, frameResize, frameCrop, frameHSV;
        
        Mat frameBlur, frameCanny, frameDilation, frameErode, dst;
        
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        // Resize the img
        resize(frame, frameResize, Size(), 0.7, 0.7);
        // Center the field
        Rect roi(450, 50, 500, 500);
        frameCrop = frameResize(roi);
        
        cvtColor(frameCrop, frameHSV, COLOR_BGR2HSV);
        
        
        
        detectBottles(frameHSV);
        detectDots(frameHSV);
        
        
        imshow("Camera HSV", frameHSV);
        
        
        
        
        /*
        GaussianBlur(dst, frameBlur, Size(3,3), 3, 0);
        
        // mostly before using cenny a little bit of blur is used
        Canny(frameBlur, frameCanny, 50, 150);
        
        // for edge detection "erweitern"
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(frameCanny, frameDilation, kernel);
        erode(frameDilation, frameErode, kernel);
        */
        
        
        if (waitKey(10) == 27) break;
    }
}


CameraFeed::~CameraFeed(void)
{
    cameraCapture.release();
}


void CameraFeed::detectBottles(Mat hsvImage)
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
    
    imshow("Camera Canny Bottles", img_canny);
    imshow("Camera dst Bottles", img_dst);
    imshow("Camera erode Bottles", img_erode);
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
    
    imshow("Camera Canny Dots", img_canny);
    imshow("Camera dst Dots", img_dst);
    imshow("Camera erode Dots", img_erode);
}
