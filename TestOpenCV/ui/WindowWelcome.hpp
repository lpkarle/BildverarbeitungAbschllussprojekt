//
//  WindowWelcome.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 08.01.22.
//

#ifndef WindowWelcome_hpp
#define WindowWelcome_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class WindowWelcome
{
private:
    string windowName = "window_welcome";
    Mat window;
    
    void placeStaticElements();
    void updateWindow();
    
public:
    WindowWelcome(void);
    ~WindowWelcome(void);
    
    void changePlayerAmount(int playerAmount);
    void changeThrowRounds(int throwRounds);
    void changeCurrentPoints(int currPoints);    
};


#endif /* WindowWelcome_hpp */
