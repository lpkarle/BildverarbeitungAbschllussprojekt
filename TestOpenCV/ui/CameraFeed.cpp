//
//  CameraFeed.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "CameraFeed.hpp"

CameraFeed::CameraFeed(void)
{
    cameraCapture = VideoCapture(0);
    
    if (!cameraCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
    }
    
    while(true) {
        
        Mat frame, frameResize, frameCrop, frameHSV;
        // Mat frameGrey, frameBlur, frameCanny, frameDilation, frameErode, frameHSV;
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        // Resize the img
        resize(frame, frameResize, Size(), 0.5, 0.5);
        // Center the field
        Rect roi(325, 75, 370, 355);
        frameCrop = frameResize(roi);
        cvtColor(frameCrop, frameHSV, COLOR_BGR2HSV);
                
        imshow("Camera HSV", frameHSV);
        
        if (waitKey(10) == 27) break;
    }
}

CameraFeed::~CameraFeed(void)
{
    cameraCapture.release();
}
