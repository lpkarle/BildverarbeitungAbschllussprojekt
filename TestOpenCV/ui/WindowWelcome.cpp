//
//  WindowWelcome.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 08.01.22.
//

#include "WindowWelcome.hpp"
#include "../Constants.cpp"


WindowWelcome::WindowWelcome(void)
{
    placeStaticElements();
    updateWindow();
}

WindowWelcome::~WindowWelcome(void) {}

void WindowWelcome::placeStaticElements()
{
    window = Mat(260, 512, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, LBL_WELCOME, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
        
    // Label and buttons -> Amount Players
    putText(window, LBL_PLAYER_AMOUNT, Point(10, 100), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, "2", Point(350, 100), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, Point(290, 80), Point(330, 105), GREY, FILLED);
    putText(window, "-", Point(298, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, Point(385, 80), Point(425, 105), GREY, FILLED);
    putText(window, "+", Point(393, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    // Label and buttons -> Rounds
    putText(window, LBL_ROUNDS, Point(10, 150), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, "1", Point(350, 150), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, Point(290, 130), Point(330, 155), GREY, FILLED);
    putText(window, "-", Point(298, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, Point(385, 130), Point(425, 155), GREY, FILLED);
    putText(window, "+", Point(393, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    rectangle(window, Point(10, 200), Point(250, 240), BLUE);
    putText(window, BTN_CANCEL, Point(75, 230), FONT_HERSHEY_DUPLEX, 1, BLUE);
    rectangle(window, Point(272, 200), Point(502, 240), BLUE, FILLED);
    putText(window, BTN_PLAY, Point(350, 230), FONT_HERSHEY_DUPLEX, 1, WHITE);

    
}

void WindowWelcome::updateWindow()
{
    imshow(windowName, window);
}
