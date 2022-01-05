//
//  main.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 15.10.21.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// ------------------------------------------------- READ IMAGES
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    
    if (img.empty()) {
        cout << "Image not found or empty!" << endl;
        return 0;
    }
    
    imshow("Image", img);
    waitKey(0); // infinity
    
    return 0;
}
 */

// ------------------------------------------------- READ VIDEO
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/BewegtBild_Uebung3.mp4";
    VideoCapture cap(path);
    
    Mat img;
    
    while (true) {
        cap.read(img);
        imshow("Image", img);
        waitKey(20); // 20 ms
    }
    
    return 0;
}
*/

// ------------------------------------------------- READ WEBCAM
/*
int main(int argc, const char * argv[]) {
    
    VideoCapture videoCapture(0);
    
    if (!videoCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
        return -1;
    }
    
    while(true) {
        Mat frame;
        videoCapture >> frame;
        if(frame.empty()) break;
        imshow("Camera feed", frame);
        if (waitKey(10) == 27) break;
    }
    videoCapture.release();
    return 0;
}
*/

// ------------------------------------------------- BASIC IMAGE FUNCTION
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    Mat imgGrey;
    Mat imgBlur;
    Mat imgCanny1, imgCanny2;
    Mat imgDilation, imgErode;
    
    cvtColor(img, imgGrey, COLOR_BGR2GRAY); // --------- to grey
    GaussianBlur(img, imgBlur, Size(3,3), 3, 0); // --------- to grey
    
    // mostly before using cenny a little bit of blur is used
    Canny(imgBlur, imgCanny1, 50, 150);
    Canny(imgBlur, imgCanny2, 25, 75);
    
    // for edge detection "erweitern"
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny1, imgDilation, kernel);
    erode(imgDilation, imgErode, kernel);
    
    if (img.empty()) {
        cout << "Image not found or empty!" << endl;
        return 0;
    }
    
    imshow("Image", img);
    imshow("Image Grey", imgGrey);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny1);
    imshow("Image Canny2", imgCanny2);
    imshow("Image Dilation", imgDilation);
    imshow("Image Erode", imgErode);
    waitKey(0);
    
    return 0;
}
*/

// ------------------------------------------------- RESIZE AND CROP IMG
/*
int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    Mat imgResize, imgCrop;
    
    resize(img, imgResize, Size(), 2, 2);
    
    // Crop is important to get information about an region of the img
    // roi -> region of interest (Bildausschnitt erzeugen)
    Rect roi(75, 75, 150, 150);
    imgCrop = imgResize(roi);
    
    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);
 
    waitKey(0);
    
    return 0;
}
*/

// ------------------------------------------------- WEBCAM EDGES
/*
int main(int argc, const char * argv[]) {
    
    VideoCapture videoCapture(0);
    
    if (!videoCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
        return -1;
    }
    
    while(true) {
        
        Mat frame, frameGrey, frameBlur, frameCanny, frameDilation, frameErode;
        videoCapture >> frame;
        if(frame.empty()) break;
        
        cvtColor(frame, frameGrey, COLOR_BGR2GRAY);
        GaussianBlur(frame, frameBlur, Size(5,5), 5, 0);
        Canny(frameBlur, frameCanny, 50, 150);
        
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        dilate(frameCanny, frameDilation, kernel);
        erode(frameDilation, frameErode, kernel);
        
        imshow("Camera feed", frame);       // normal
        imshow("Camera grey", frameGrey);   // grey
        imshow("Camera blur", frameBlur);   // blur
        imshow("Camera canny", frameCanny); // canny
        imshow("Image Dilation", frameDilation);
        imshow("Image Erode", frameErode);
        
        if (waitKey(10) == 27) break;
    }
    videoCapture.release();
    return 0;
}
*/

int main(int argc, const char * argv[]) {
    
    // blank image
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
    
    circle(img, Point(256, 256), 150, Scalar(255,0,0), 10);
    circle(img, Point(256, 256), 50, Scalar(255,0,0), FILLED);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 0, 0), 3);
    line(img, Point(0,0), Point(512, 512), Scalar(0, 255, 255), 20);
    
    putText(img, "well hello there...", Point(50, 50), FONT_ITALIC, 0.75, Scalar(0, 0,255));
    
    imshow("Image", img);
    waitKey(0);
    
    return 0;
}
