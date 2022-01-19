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
    putText(window, msg, Point(10, 35), FONT_HERSHEY_DUPLEX, 0.75, WHITE);
    
    rectangle(window, locationBtnCancel[0], locationBtnCancel[1], BLUE);
    putText(window, BTN_YES, Point(90, 232), FONT_HERSHEY_DUPLEX, 0.8, BLUE);
    rectangle(window, locationBtnPlay[0], locationBtnPlay[1], BLUE, FILLED);
    putText(window, BTN_NO, Point(340, 232), FONT_HERSHEY_DUPLEX, 0.8, WHITE);
}


void WindowAlert::updateWindow()
{
    imshow(WINDOW_ALERT, window);
}
