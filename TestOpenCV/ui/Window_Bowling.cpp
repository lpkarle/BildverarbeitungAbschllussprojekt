//
//  Window_Bowling.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "Window_Bowling.hpp"
#include "../Constants.cpp"

WindowBowling::WindowBowling(void)
{
    initPins();
    staticElements();
    showWindow();
}

WindowBowling::~WindowBowling(void) {}

void WindowBowling::initPins()
{
    window = Mat(700, 512, CV_8UC3, WHITE);
    
    circle(window, Point(257, 105), 21, Scalar(200, 200, 200), FILLED);  // shadow
    circle(window, Point(256, 104), 20, Scalar(255, 255, 255), FILLED);  // kegel
    circle(window, Point(256, 104), 8, Scalar(0, 0, 255), FILLED);       // deckel
    putText(window, "1", Point(256+OFFSET_TEXT_X, 104+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(161, 201), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(160, 200), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(160, 200), 8, Scalar(0,0,255), FILLED);
    putText(window, "2", Point(160+OFFSET_TEXT_X, 200+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(353, 201), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(352, 200), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(352, 200), 8, Scalar(0,0,255), FILLED);
    putText(window, "3", Point(352+OFFSET_TEXT_X, 200+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(65, 297), 21, Scalar(200, 200, 200), FILLED);
    circle(window, Point(64, 296), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(64, 296), 8, Scalar(0, 0, 255), FILLED);
    putText(window, "4", Point(64+OFFSET_TEXT_X, 296+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(257, 297), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(256, 296), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(256, 296), 8, Scalar(0,0,255), FILLED);
    putText(window, "5", Point(256+OFFSET_TEXT_X, 296+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(449, 297), 21, Scalar(200, 200, 200), FILLED);
    circle(window, Point(448, 296), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(448, 296), 8, Scalar(0, 0, 255), FILLED);
    putText(window, "6", Point(448+OFFSET_TEXT_X, 296+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(161, 393), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(160, 392), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(160, 392), 8, Scalar(0,0,255), FILLED);
    putText(window, "7", Point(160+OFFSET_TEXT_X, 392+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(353, 393), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(352, 392), 20, Scalar(255,255,255), FILLED);
    circle(window, Point(352, 392), 8, Scalar(0,0,255), FILLED);
    putText(window, "8", Point(352+OFFSET_TEXT_X, 392+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
    circle(window, Point(257, 489), 21, Scalar(200,200,200), FILLED);
    circle(window, Point(256, 488), 20, Scalar(255, 255, 255), FILLED);
    circle(window, Point(256, 488), 8, Scalar(0,0,255), FILLED);
    putText(window, "9", Point(256+OFFSET_TEXT_X, 488+OFFSET_TEXT_Y), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0));
    
}

void WindowBowling::knockDownPin(int pinNr)
{
    
    if (pinNr <= 0 || pinNr > 9) return;
    
    cout << "Knockdown " << pinNr << endl;
    
    switch (pinNr)
    {
        case 1:
            circle(window, Point(256, 104), 22, GREY, FILLED);
            break;
        case 2:
            circle(window, Point(160, 200), 22, GREY, FILLED);
            break;
        case 3:
            circle(window, Point(352, 200), 22, GREY, FILLED);
            break;
        case 4:
            circle(window, Point(64, 296), 22, GREY, FILLED);
            break;
        case 5:
            circle(window, Point(256, 296), 22, GREY, FILLED);
            break;
        case 6:
            circle(window, Point(448, 296), 22, GREY, FILLED);
            break;
        case 7:
            circle(window, Point(160, 392), 22, GREY, FILLED);
            break;
        case 8:
            circle(window, Point(352, 392), 22, GREY, FILLED);
            break;
        case 9:
            circle(window, Point(256, 488), 22, GREY, FILLED);
            break;
    }
    
    showWindow();
}

void WindowBowling::changeCurrentPlayer(int player)
{
    
    if (player <= 0) return;
    
    rectangle(window, Point(250, 0), Point(305, 50), BLUE, FILLED);
    putText(window, to_string(player), Point(260, 38), FONT_HERSHEY_COMPLEX, 1.2, WHITE);
    
    showWindow();
}

void WindowBowling::staticElements()
{
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, CURRENT_PLAYER, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
    
    line(window, Point(10, 540), Point(502, 540), GREY);
    line(window, Point(256, 550), Point(256, 690), GREY);
    
    putText(window, THOWS, Point(10, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, POINTS, Point(10, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    putText(window, "1.", Point(266, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, "2.", Point(266, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, "3.", Point(266, 680), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
}

void WindowBowling::showWindow()
{
    imshow("Bowling Pins", window);
}
