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
    const Point locationBtnCancel[ 2 ] = { Point(10, 205), Point(250, 245) };
    const Point locationBtnPlay[ 2 ]   = { Point(262, 205), Point(502, 245) };
    
    Mat window;
    const int WINDOW_WIDH = 512;
    const int WINDOW_HEIGHT = 255;
    
    string msg;
    
    void placeStaticElements();
    
public:
    WindowAlert(string msg);
    ~WindowAlert();
    
    void showResult(vector<pair<string, int>> playerRank);
    void updateWindow();
};

#endif /* WindowAlert_hpp */
