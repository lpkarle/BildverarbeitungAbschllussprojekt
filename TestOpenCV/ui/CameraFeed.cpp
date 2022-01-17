//
//  CameraFeed.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "CameraFeed.hpp"
#include "../Constants.cpp"


CameraFeed::CameraFeed()
{
    while (!cameraCapture.isOpened())
    {
        cameraCapture = VideoCapture(1);
    }
}


CameraFeed::~CameraFeed()
{
    cameraCapture.release();
}

vector<int> CameraFeed::start()
{
    Mat frame, frameHSV, frameDilation;
    vector<int> pins;
    
    cameraCapture >> frame;
    if(frame.empty()) return pins;
        
    auto images = preprocessImage(frame);
    frameHSV = images[2];
    frameDilation = images[5];
        
    // get the shapes/contours from the eroded image
    // and filter the bottles
    vector<vector<Point>> bottleContours = getBottleContours(getContours(frameDilation));
                
    // check the bottle location and mark them in standard and hsv
    bottleLocation(frameHSV);
    pins = pinsUp(bottleContours, frameHSV);
    
    return pins;   
}


vector<Mat> CameraFeed::preprocessImage(Mat frame)
{
    Mat imgResize, imgCrop, imgDest, imgHSV, imgBlur, imgCanny, imgDilation;
    
    // Resize the img
    resize(frame, imgResize, Size(), 0.7, 0.7);
    
    // Center the field
    Rect roi(450, 50, 500, 500);
    imgCrop = imgResize(roi);
    
    cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);
    
    // Yellow
    hmin = 12; smin = 46; vmin = 248;
    hmax = 49; smax = 198; vmax = 255;
    
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, imgDest);
    
    //cvtColor(img, img_grey, COLOR_BGR2GRAY);
    GaussianBlur(imgDest, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDilation, kernel);
    
    vector<Mat> processedImages = { imgCrop, imgDest, imgHSV, imgBlur, imgCanny, imgDilation };
    
    return processedImages;
}


vector<vector<Point>> CameraFeed::getContours(Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    return contours;
}


vector<vector<Point>> CameraFeed::getBottleContours(vector<vector<Point>> contours)
{
    vector<vector<Point>> contourCircle;
    
    // filter area
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
                
        if (area >= 580 && area <= 750)
        {
            vector<Point> currentContour;
            float parameter = arcLength(contours[i], true);
            approxPolyDP(contours[i], currentContour, 0.02 * parameter, true);
            int objCornerPoints = (int) currentContour.size();
            
            if (objCornerPoints > 4)
            {
                contourCircle.insert(contourCircle.end(), currentContour);
            }
        }
    }
    return contourCircle;
}


vector<int> CameraFeed::pinsUp(vector<vector<Point>> circleContours, Mat img)
{
    vector<int> pins;
    
    for (auto circ : circleContours)
    {
        auto boundRect = boundingRect(circ);
        rectangle(img, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 2);
        
        for (int i = 0; i < (int) pinAreas.size(); i++)
        {
            if (boundRect.tl().x >= pinAreas[i].x && boundRect.br().x <= pinAreas[i].x + pinBoxWidth &&
                boundRect.tl().y >= pinAreas[i].y && boundRect.br().y <= pinAreas[i].y + pinBoxHeight)
            {
                pins.insert(pins.end(), i + 1);
                break;
            }
        }
    }
    
    imshow(WINDOW_CAMERA, img);
    
    return pins;
}


// TEST
void CameraFeed::bottleLocation(Mat img)
{    
    for (auto pin : pinAreas)
    {
        rectangle(img, pin, {pin.x + pinBoxWidth, pin.y + pinBoxHeight}, Scalar(255, 0, 0), 2);
    }
}
