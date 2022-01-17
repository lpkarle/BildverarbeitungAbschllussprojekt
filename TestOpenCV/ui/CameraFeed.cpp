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
        
    //int framesAmountToCompare = 24;
    //int frameCounter = 1;
    //int meanBottleCount = 0;
    
    Mat frame;
        
    while(true) {
        
        
        
        cameraCapture >> frame;
        if(frame.empty()) break;
        
        auto images = preprocessImage(frame);
        
        
        // get the shapes/contours from the eroded image
        // and filter the bottles
        vector<vector<Point>> bottleContours = getBottleContours(getContours(images[5]));
        
        cout << "--------- bottles up -------> " << bottleContours.size() << endl;
        
                
        // check the bottle location and mark them in standard and hsv
        bottleLocation(images[2]);
        checkBottleLocation(bottleContours, images[2], windowBowling);
        
        imshow("Frame Camera", images[0]);
        imshow("Frame HSV", images[2]);
        
        
        //for (int i = 0; i < (int) images.size(); i++)
        //{
        //    if (i == 0 || i == 2)
        //   {
        //        // check the bottle location and mark them in standard and hsv
        //        bottleLocation(images[i]);
        //        checkBottleLocation(bottleContours, images[i]);
        //        bottleLocation(images[i]);
        //        checkBottleLocation(bottleContours, images[i]);
        //
        //        imshow("Frame " + to_string(i), images[i]);
        //    }
        //}
        
        if (waitKey(10) == 27) break;
    
    }
}


CameraFeed::~CameraFeed()
{
    cameraCapture.release();
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
        //cout << area << endl;
                
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


void CameraFeed::checkBottleLocation(vector<vector<Point>> circleContours, Mat img, WindowBowling windowBowling)
{
    int pinNr = 1;
    string isUp = "";
    
    for (auto circ : circleContours)
    {
        auto boundRect = boundingRect(circ);
        rectangle(img, boundRect.tl(), boundRect.br(), Scalar(0, 255, 0), 2);
        // putText(img, "Circle", {boundRect.x, boundRect.y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0,0,0));
        
        for (int i = 0; i < (int) pins.size(); i++)
        {
            if (boundRect.tl().x >= pins[i].x && boundRect.br().x <= pins[i].x + pinBoxWidth &&
                boundRect.tl().y >= pins[i].y && boundRect.br().y <= pins[i].y + pinBoxHeight)
            {
                isUp += to_string(i + 1) + ", ";
                windowBowling.showPinUp(i + 1);
                break;
            }
            else
            {
                windowBowling.showPinDown(i + 1);
            }
        }
        pinNr++;
    }
    cout << "Pin " << isUp << " up."<< endl;
}


void CameraFeed::onMouse(int event, int x, int y, int, void* userdata)
{
    CameraFeed* cameraFeed = reinterpret_cast<CameraFeed*>(userdata);
    cameraFeed->onMouse(event, x, y);
}

int CameraFeed::onMouse(int event, int x, int y)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        // check the button positions
        if (x >= locationBtnNextRound[0].x && x <= locationBtnNextRound[1].x &&
            y >= locationBtnNextRound[0].y && y <= locationBtnNextRound[1].y)
        {
            cout << "BUTTON MINUS PLAYER" << endl;
    
        }
        else if (x >= locationBtnNextRound[0].x && x <= locationBtnNextRound[1].x &&
                 y >= locationBtnNextRound[0].y && y <= locationBtnNextRound[1].y)
        {
            cout << "BUTTON PLUS PLAYER" << endl;
            
        }
    }
    return 1;

}



// TEST
void CameraFeed::bottleLocation(Mat img)
{    
    for (auto pin : pins)
    {
        rectangle(img, pin, {pin.x + pinBoxWidth, pin.y + pinBoxHeight}, Scalar(255, 0, 0), 2);
    }
}
