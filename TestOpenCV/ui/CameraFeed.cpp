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


/**
 * Starts the image processing.
 *
 * @return a vector of all standing pins
 */
vector<int> CameraFeed::startReceivingPinsUp()
{
    Mat frame, frameDilation;
    vector<int> pins;
    
    cameraCapture >> frame;
    if(frame.empty()) return pins;
        
    auto images = preprocessImageDilation(frame);
    frameDilation = images[5];
        
    vector<vector<Point>> bottleContours = filterCircleContourByAreaAndCornerPoints(getImageContours(frameDilation));
                
    markPinLocationWithRect(images[0]);
    pins = getStandingPins(bottleContours, images[0]);
    
    return pins;   
}


/**
 * Function to preprocess the frame received from the webcam.
 *
 * Following steps:
 * 1. Decrease the frame resolution by 0.7
 * 2. Crop the game board (center of interest)
 * 3. Convert the frame in HSV
 * 4. Use the HSV thresholds for the yellow caps
 * 5. Blur the image
 * 6. Use canny to detect the contours
 * 7. Close and thicken the contours by using dilation
 *
 * @param frame the original image
 * @return the dilated image
 */
vector<Mat> CameraFeed::preprocessImageDilation(Mat frame)
{
    Mat imgResize, imgCrop, imgHSVYellow, imgHSV, imgBlur, imgCanny, imgDilation;
    
    resize(frame, imgResize, Size(), RESIZE_FACTOR, RESIZE_FACTOR);
    
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


/**
 * Extract all contours from the received image.
 *
 * @param img to detect contours
 * @return all contours from img
 */
vector<vector<Point>> CameraFeed::getImageContours(Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    return contours;
}


/**
 * Filters all the detected contours by using the area of the contour and the edge amount.
 *
 * @param contours all detected contours
 * @return only the circle contours of the bottles
 */
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


/**
 * Detects all standing pins by checking if a circle contour is in a defined rectangle range.
 *
 * @param circleContours detected circles in img
 * @param img to show the detected pins
 * @return all standing pins
 */
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


/**
 * Shows the predefined location areas of the bottles.
 *
 * @param img to draw the bottle location in
 */
void CameraFeed::markPinLocationWithRect(Mat img)
{    
    for (auto pin : PIN_AREAS)
    {
        rectangle(img, pin, {pin.x + PIN_BOX_SIZE, pin.y + PIN_BOX_SIZE}, BLUE, 2);
    }
}
