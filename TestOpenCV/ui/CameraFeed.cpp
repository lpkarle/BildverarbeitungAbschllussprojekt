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


vector<int> CameraFeed::startReceivingPinsUp()
{
    Mat frame, frameDilation;
    vector<int> pins;
    
    cameraCapture >> frame;
    if(frame.empty()) return pins;
        
    auto images = preprocessImageDilation(frame);
    frameDilation = images[5];
        
    // get the shapes/contours from the eroded image
    // and filter the bottles / pins
    vector<vector<Point>> bottleContours = filterCircleContourByAreaAndCornerPoints(getImageContours(frameDilation));
                
    // check the bottle location and mark them in standard and hsv
    markPinLocationWithRect(images[0]);
    pins = getStandingPins(bottleContours, images[0]);
    
    return pins;   
}


vector<Mat> CameraFeed::preprocessImageDilation(Mat frame)
{
    Mat imgResize, imgCrop, imgHSVYellow, imgHSV, imgBlur, imgCanny, imgDilation;
    
    // Resize the img
    resize(frame, imgResize, Size(), RESIZE_FACTOR, RESIZE_FACTOR);
    
    // crop the image by centering the field
    imgCrop = imgResize(CENTER_OF_INTEREST);
    
    cvtColor(imgCrop, imgHSV, COLOR_BGR2HSV);
    
    inRange(imgHSV, YELLOW_HSV_LOWER_THRESH, YELLOW_HSV_UPPER_THRESH, imgHSVYellow);
    
    GaussianBlur(imgHSVYellow, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 0, 1); // zero and one thresh -> img is binary
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDilation, kernel);
    
    vector<Mat> processedImages = { imgCrop, imgHSVYellow, imgHSV, imgBlur, imgCanny, imgDilation };
    
    return processedImages;
}


vector<vector<Point>> CameraFeed::getImageContours(Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    return contours;
}


vector<vector<Point>> CameraFeed::filterCircleContourByAreaAndCornerPoints(vector<vector<Point>> contours)
{
    vector<vector<Point>> contourCircle;
    
    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
                
        if (area >= COVER_AREA_MIN && area <= COVER_AREA_MAX)
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


vector<int> CameraFeed::getStandingPins(vector<vector<Point>> circleContours, Mat img)
{
    vector<int> pins;
    
    for (auto circ : circleContours)
    {
        auto boundRect = boundingRect(circ);
        rectangle(img, boundRect.tl(), boundRect.br(), RED, 2);
        
        for (int i = 0; i < (int) PIN_AREAS.size(); i++)
        {
            if (boundRect.tl().x >= PIN_AREAS[i].x && boundRect.br().x <= PIN_AREAS[i].x + PIN_BOX_SIZE &&
                boundRect.tl().y >= PIN_AREAS[i].y && boundRect.br().y <= PIN_AREAS[i].y + PIN_BOX_SIZE)
            {
                pins.insert(pins.end(), i + 1);
                break;
            }
        }
    }
    
    imshow(WINDOW_CAMERA, img);
    return pins;
}


void CameraFeed::markPinLocationWithRect(Mat img)
{    
    for (auto pin : PIN_AREAS)
    {
        rectangle(img, pin, {pin.x + PIN_BOX_SIZE, pin.y + PIN_BOX_SIZE}, BLUE, 2);
    }
}
