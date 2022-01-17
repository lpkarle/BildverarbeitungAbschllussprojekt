//
//  Window_Bowling.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "WindowBowling.hpp"
#include "../Constants.cpp"


WindowBowling::WindowBowling(int amountPlayers, int amountRounds)
{
    staticElements(amountPlayers, amountRounds);
    initPins();
    updateWindow();
}

WindowBowling::~WindowBowling() {}

void WindowBowling::initPins()  
{
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

void WindowBowling::showPinDown(int pinNr)
{
    
    if (pinNr <= 0 || pinNr > 9) return;
        
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
    
    updateWindow();
}

void WindowBowling::allPinsDown()
{
    circle(window, Point(256, 104), 22, GREY, FILLED);
    circle(window, Point(160, 200), 22, GREY, FILLED);
    circle(window, Point(352, 200), 22, GREY, FILLED);
    circle(window, Point(64, 296), 22, GREY, FILLED);
    circle(window, Point(256, 296), 22, GREY, FILLED);
    circle(window, Point(448, 296), 22, GREY, FILLED);
    circle(window, Point(160, 392), 22, GREY, FILLED);
    circle(window, Point(352, 392), 22, GREY, FILLED);
    circle(window, Point(256, 488), 22, GREY, FILLED);
}


void WindowBowling::showPinUp(int pinNr)
{
    
    if (pinNr <= 0 || pinNr > 9) return;
        
    switch (pinNr)
    {
        case 1:
            circle(window, Point(256, 104), 25, WHITE, FILLED);  // background
            circle(window, Point(257, 105), 21, Scalar(200, 200, 200), FILLED);  // shadow
            circle(window, Point(256, 104), 20, Scalar(255, 255, 255), FILLED);  // kegel
            circle(window, Point(256, 104), 8, Scalar(0, 0, 255), FILLED);       // deckel
            break;
        case 2:
            circle(window, Point(160, 200), 25, WHITE, FILLED);  // background
            circle(window, Point(161, 201), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(160, 200), 20, Scalar(255,255,255), FILLED);
            circle(window, Point(160, 200), 8, Scalar(0,0,255), FILLED);
            break;
        case 3:
            circle(window, Point(352, 200), 25, WHITE, FILLED);  // background
            circle(window, Point(353, 201), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(352, 200), 20, Scalar(255,255,255), FILLED);
            circle(window, Point(352, 200), 8, Scalar(0,0,255), FILLED);
            break;
        case 4:
            circle(window, Point(64, 296), 25, WHITE, FILLED);  // background
            circle(window, Point(65, 297), 21, Scalar(200, 200, 200), FILLED);
            circle(window, Point(64, 296), 20, Scalar(255, 255, 255), FILLED);
            circle(window, Point(64, 296), 8, Scalar(0, 0, 255), FILLED);
            break;
        case 5:
            circle(window, Point(256, 296), 25, WHITE, FILLED);  // background
            circle(window, Point(257, 297), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(256, 296), 20, Scalar(255,255,255), FILLED);
            circle(window, Point(256, 296), 8, Scalar(0,0,255), FILLED);
            break;
        case 6:
            circle(window, Point(448, 296), 25, WHITE, FILLED);  // background
            circle(window, Point(449, 297), 21, Scalar(200, 200, 200), FILLED);
            circle(window, Point(448, 296), 20, Scalar(255, 255, 255), FILLED);
            circle(window, Point(448, 296), 8, Scalar(0, 0, 255), FILLED);
            break;
        case 7:
            circle(window, Point(160, 392), 25, WHITE, FILLED);  // background
            circle(window, Point(161, 393), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(160, 392), 20, Scalar(255, 255, 255), FILLED);
            circle(window, Point(160, 392), 8, Scalar(0,0,255), FILLED);
            break;
        case 8:
            circle(window, Point(353, 392), 25, WHITE, FILLED);  // background
            circle(window, Point(353, 393), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(352, 392), 20, Scalar(255,255,255), FILLED);
            circle(window, Point(352, 392), 8, Scalar(0,0,255), FILLED);
            break;
        case 9:
            circle(window, Point(256, 488), 25, WHITE, FILLED);  // background
            circle(window, Point(257, 489), 21, Scalar(200,200,200), FILLED);
            circle(window, Point(256, 488), 20, Scalar(255, 255, 255), FILLED);
            circle(window, Point(256, 488), 8, Scalar(0,0,255), FILLED);
            break;
    }
    
    updateWindow();
}

void WindowBowling::changeCurrentPlayer(int currPlayer)
{
    
    if (currPlayer <= 0) return;
    
    rectangle(window, Point(250, 0), Point(305, 50), BLUE, FILLED);
    putText(window, to_string(currPlayer), Point(260, 38), FONT_HERSHEY_COMPLEX, 1.2, WHITE);
    
    updateWindow();
}

void WindowBowling::changeCurrentThrow(int currThrow)
{
    rectangle(window, Point(100, 550), Point(200, 590), WHITE, FILLED);
    putText(window, to_string(currThrow), Point(100, 580), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    updateWindow();
}

void WindowBowling::changeCurrentPoints(int currPoints)
{
    rectangle(window, Point(100, 600), Point(200, 640), WHITE, FILLED);
    putText(window, to_string(currPoints), Point(100, 630), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    updateWindow();
}

void WindowBowling::changeCurrentRank(string rankNames[])
{
    rectangle(window, Point(295, 550), Point(500, 690), WHITE, FILLED);
    putText(window, rankNames[0], Point(300, 580), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    putText(window, rankNames[1], Point(300, 630), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    putText(window, rankNames[2], Point(300, 680), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    updateWindow();
}

void WindowBowling::staticElements(int amountPlayers, int amountRounds)
{
    window = Mat(700, 512, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, CURRENT_PLAYER, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
    
    line(window, Point(10, 540), Point(502, 540), GREY);
    line(window, Point(256, 550), Point(256, 690), GREY);
    
    putText(window, THOWS, Point(10, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, POINTS, Point(10, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    putText(window, "1.", Point(266, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    if (amountPlayers >= 2) putText(window, "2.", Point(266, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    if (amountPlayers == 3) putText(window, "3.", Point(266, 680), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
}

void WindowBowling::updateWindow()
{
    imshow("Bowling Pins", window);
}
