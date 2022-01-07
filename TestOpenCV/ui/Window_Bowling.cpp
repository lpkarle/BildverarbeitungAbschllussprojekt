//
//  Window_Bowling.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "Window_Bowling.hpp"

WindowBowling::WindowBowling(void)
{
    initPins();
    showWindow();
}

WindowBowling::~WindowBowling(void) {}

void WindowBowling::initPins()
{
    window = Mat(700, 512, CV_8UC3, Scalar(225, 225, 225));
    
    circle(window, Point(257, 65), 21, Scalar(200, 200, 200), FILLED);  // shadow
    circle(window, Point(256, 64), 20, Scalar(255, 255, 255), FILLED);  // kegel
    circle(window, Point(256, 64), 8, Scalar(0, 0, 255), FILLED);       // deckel
    putText(window, "1", Point(256+OFFSET_TEXT_X, 64+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(161, 161), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(160, 160), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(160, 160), 8, Scalar(0,0,255), FILLED);
    putText(window, "2", Point(160+OFFSET_TEXT_X, 160+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(353, 161), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(352, 160), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(352, 160), 8, Scalar(0,0,255), FILLED);
    putText(window, "3", Point(352+OFFSET_TEXT_X, 160+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(65, 257), 21, Scalar(200, 200, 200), FILLED);
    circle(window, Point(64, 256), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(64, 256), 8, Scalar(0, 0, 255), FILLED);
    putText(window, "4", Point(64+OFFSET_TEXT_X, 256+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(257, 257), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(256, 256), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(256, 256), 8, Scalar(0,0,255), FILLED);
    putText(window, "5", Point(256+OFFSET_TEXT_X, 256+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(449, 257), 21, Scalar(200, 200, 200), FILLED);
    circle(window, Point(448, 256), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(448, 256), 8, Scalar(0, 0, 255), FILLED);
    putText(window, "6", Point(448+OFFSET_TEXT_X, 256+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(161, 353), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(160, 352), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(160, 352), 8, Scalar(0,0,255), FILLED);
    putText(window, "7", Point(160+OFFSET_TEXT_X, 352+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(353, 353), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(352, 352), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(352, 352), 8, Scalar(0,0,255), FILLED);
    putText(window, "8", Point(352+OFFSET_TEXT_X, 352+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(257, 449), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(256, 448), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(256, 448), 8, Scalar(0,0,255), FILLED);
    putText(window, "9", Point(256+OFFSET_TEXT_X, 448+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
}

void WindowBowling::knockDownPin(int pinNr)
{
    
    if (pinNr <= 0 || pinNr > 9) return;
    
    cout << "Knockdown " << pinNr << endl;
    
    switch (pinNr)
    {
        case 1:
            circle(window, Point(256, 64), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 2:
            circle(window, Point(160, 160), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 3:
            circle(window, Point(352, 160), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 4:
            circle(window, Point(64, 256), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 5:
            circle(window, Point(256, 256), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 6:
            circle(window, Point(448, 256), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 7:
            circle(window, Point(160, 352), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 8:
            circle(window, Point(352, 160), 22, Scalar(200, 200, 200), FILLED);
            break;
        case 9:
            circle(window, Point(352, 352), 22, Scalar(200, 200, 200), FILLED);
            break;
    }
    
    showWindow();
}

void WindowBowling::showWindow()
{
    imshow("Bowling Pins", window);
}
