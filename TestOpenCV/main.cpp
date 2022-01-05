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
