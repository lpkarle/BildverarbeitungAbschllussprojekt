//
//  FilterFromHSV.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 20.01.22.
//

#include "FilterFromHSV.hpp"


FilterFromHSV::FilterFromHSV()
{
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
        
        createTrackbar("H_Min", windowTitleCameraBinary, &hmin, slider_max, onTrackbar );
        createTrackbar("H_Max", windowTitleCameraBinary, &hmax, slider_max, onTrackbar );
        createTrackbar("S_Min", windowTitleCameraBinary, &smin, slider_max, onTrackbar );
        createTrackbar("S_Max", windowTitleCameraBinary, &smax, slider_max, onTrackbar );
        createTrackbar("V_Min", windowTitleCameraBinary, &vmin, slider_max, onTrackbar );
        createTrackbar("V_Max", windowTitleCameraBinary, &vmax, slider_max, onTrackbar );
        
        onTrackbar( hmin, 0 );
        onTrackbar( hmax, 0 );
        onTrackbar( smin, 0 );
        onTrackbar( smax, 0 );
        onTrackbar( vmin, 0 );
        onTrackbar( vmax, 0 );
            
        if (waitKey(10) == 27) break;
    }
}


FilterFromHSV::~FilterFromHSV()
{
    cameraCapture.release();
}


void FilterFromHSV::onTrackbar(int i, void *data)
{
    FilterFromHSV* filterFromHSV = reinterpret_cast<FilterFromHSV*>(data);
    filterFromHSV->onTrackbar(i);
}


void FilterFromHSV::onTrackbar(int i)
{
    cout << "ontrackbar" << endl;
    Scalar lower(this->hmin, this->smin, this->vmin);
    Scalar upper(this->hmax, this->smax, this->vmax);
    
    
    inRange(imgHSV, lower, upper, dst);
    
    rectangle(windowHSVValues, Point(0, 0), Point(200, 500), Scalar(255, 255, 255), FILLED);
    putText(windowHSVValues, "hmin: " + to_string(hmin), Point(5, 25), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "hmax: " + to_string(hmax), Point(5, 50), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0,255));
    putText(windowHSVValues, "smin: " + to_string(smin), Point(5, 75), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "smax: " + to_string(smax), Point(5, 100), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "vmin: " + to_string(vmin), Point(5, 125), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
    putText(windowHSVValues, "vmax: " + to_string(vmax), Point(5, 150), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255));
   
    imshow( windowTitleHSV, windowHSVValues );
    imshow( windowTitleCamera, imgCrop);
    imshow( windowTitleCameraBinary, dst );
}
