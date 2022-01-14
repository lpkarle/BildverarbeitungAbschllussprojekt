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
        
        
        
        int bottles_up = detectBottles(frameHSV);
        
        cout << "-------------- bottles ----> " << bottles_up << endl;
    
        
        detectDots(frameHSV);
        
        
        imshow("Camera", frameCrop);
        
        
        
        
        
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
    
    return (int) getContoures(img_dilation, hsvImage).size();
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

vector<vector<Point>> CameraFeed::getContoures(Mat imgSrc, Mat imgDest)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgSrc, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(imgDest, contours, -1, Scalar(255, 255, 255), 2);
    
    
    
    // filter area
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;
        
        vector<vector<Point>> conPoly(contours.size());
        vector<Rect> boundRect(contours.size());
        
        string objType;
        
        if (area >= 610 && area <= 675)
        {
            float parameter = arcLength(contours[i], true);
            
            approxPolyDP(contours[i], conPoly[i], 0.02 * parameter, true);
            drawContours(imgDest, conPoly, i, Scalar(0, 0, 0), 2);
            
            cout << conPoly.size() << endl;
            
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(imgDest, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
            
            int objCornerPoints = (int) conPoly[i].size();
            
            switch (objCornerPoints)
            {
                case 3:
                    objType = "Triangle";
                case 4:
                    objType = "Rectangle";
                default:
                    objType = "Circle";
            }
            
            putText(imgDest, objType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0,0,0));
        }
    }
    imshow("Camera HSV", imgDest);
    
    return contours;
}
