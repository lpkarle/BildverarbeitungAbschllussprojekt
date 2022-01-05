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

int main(int argc, const char * argv[]) {
    
    string path = "/Users/lukaskarle/Dev/C++/OpenCV/TestOpenCV/TestOpenCV/assets/rabbit.jpeg";
    Mat img = imread(path);
    
    if (img.empty()) {
        cout << "Image not found or empty!" << endl;
        return 0;
    }
    
    imshow("Image", img);
    waitKey(0);
    
    return 0;
}
