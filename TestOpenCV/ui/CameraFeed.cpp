//
//  CameraFeed.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "CameraFeed.hpp"

CameraFeed::CameraFeed(void)
{
    cameraCapture = VideoCapture(1);
    
    if (!cameraCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
    }
    
    while(true) {
        
        Mat frame, frameResize, frameCrop, frameHSV;
        Mat frameBlur, frameCanny, frameDilation, frameErode, dst;
        
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        // Resize the img
        resize(frame, frameResize, Size(), 0.5, 0.5);
        // Center the field
        Rect roi(300, 0, 475, 425);
        frameCrop = frameResize(roi);
        
        cvtColor(frameCrop, frameHSV, COLOR_BGR2HSV);
        
        int hmin = 40, smin = 126, vmin = 69;
        int hmax = 89, smax = 255, vmax = 166;
        
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(frameHSV, lower, upper, dst);
        
        
        GaussianBlur(dst, frameBlur, Size(3,3), 3, 0);
        
        // mostly before using cenny a little bit of blur is used
        Canny(frameBlur, frameCanny, 50, 150);
        
        // for edge detection "erweitern"
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(frameCanny, frameDilation, kernel);
        erode(frameDilation, frameErode, kernel);
        
        
        
        
                
        imshow("Camera HSV", frameHSV);
        imshow("Camera Blur", frameBlur);
        imshow("Camera Canny", frameCanny);
        imshow("Camera Dilation", frameDilation);
        imshow("Camera dst", dst);
        imshow("Camera erode", frameErode);
        
        if (waitKey(10) == 27) break;
    }
}

CameraFeed::~CameraFeed(void)
{
    cameraCapture.release();
}
