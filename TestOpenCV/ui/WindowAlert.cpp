//
//  WindowAlert.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 17.01.22.
//

#include "WindowAlert.hpp"
#include "../Constants.cpp"


WindowAlert::WindowAlert(string msg)
{
    this->msg = msg;
    placeStaticElements();
    updateWindow();
}


WindowAlert::~WindowAlert() { }


void WindowAlert::placeStaticElements()
{
    window = Mat(WINDOW_HEIGHT, WINDOW_WIDH, CV_8UC3, WHITE);
    rectangle(window, Point(0, 0), Point(WINDOW_WIDH, 50), BLUE, FILLED);
    putText(window, msg, Point(10, 35), FONT_HERSHEY_DUPLEX, 0.5, WHITE);
}


void WindowAlert::updateWindow()
{
    imshow(WINDOW_ALERT, window);
}
