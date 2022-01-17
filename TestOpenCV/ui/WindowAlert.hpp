//
//  WindowAlert.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 17.01.22.
//

#ifndef WindowAlert_hpp
#define WindowAlert_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class WindowAlert
{
private:
    Mat window;
    const int WINDOW_WIDH = 512;
    const int WINDOW_HEIGHT = 256;
    
    string msg;
    
    void placeStaticElements();
    
public:
    
    WindowAlert(string msg);
    ~WindowAlert();
    
    void updateWindow();
};

#endif /* WindowAlert_hpp */
