//
//  Window_Bowling.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include "WindowBowling.hpp"
#include "../Constants.cpp"


WindowBowling::WindowBowling()
{
    staticElements(1,1);
    initPins();
    updateWindow();
}

WindowBowling::~WindowBowling() {}


void WindowBowling::initPins()  
{
    int pinNr = 1;
    
    for (auto pin : pinLocations)
    {
        circle(window, {pin.x + shadowOffset, pin.y + shadowOffset}, pinShadowRadius, GREY, FILLED);    // shadow
        circle(window, pin, pinRadius, WHITE, FILLED);                                                  // pin
        circle(window, pin, pinCoverRadius, RED, FILLED);                                               // cover
        putText(window, to_string(pinNr), {pin.x + OFFSET_TEXT_X, pin.y + OFFSET_TEXT_Y }, FONT_HERSHEY_COMPLEX, fontScale, GREY_DARK);
        pinNr++;
    }
}


void WindowBowling::allPinsDown()
{
    for (auto pin : pinLocations)
    {
        circle(window, pin, pinKnockDownRadius, GREY, FILLED);
    }
}


void WindowBowling::showPinUp(int pinNr)
{
    if (pinNr < 1 || pinNr > 9) return;
    
    auto pin = pinLocations[pinNr - 1];
    
    circle(window, pin, pinBackgroundRadius, WHITE, FILLED);                                        // background
    circle(window, {pin.x + shadowOffset, pin.y + shadowOffset}, pinShadowRadius, GREY, FILLED);    // shadow
    circle(window, pin, pinRadius, WHITE, FILLED);                                                  // pin
    circle(window, pin, pinCoverRadius, RED, FILLED);                                               // cover
    
    //updateWindow();
}

void WindowBowling::changeCurrentPlayer(int currPlayer)
{
    
    if (currPlayer <= 0) return;
    
    rectangle(window, Point(250, 0), Point(305, 50), BLUE, FILLED);
    putText(window, to_string(currPlayer), Point(260, 38), FONT_HERSHEY_COMPLEX, 1.2, WHITE);
    
    //updateWindow();
}

void WindowBowling::changeCurrentThrow(int currThrow)
{
    rectangle(window, Point(100, 550), Point(200, 590), WHITE, FILLED);
    putText(window, to_string(currThrow), Point(100, 580), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    //updateWindow();
}

void WindowBowling::changeCurrentPoints(int currPoints)
{
    rectangle(window, Point(100, 600), Point(200, 640), WHITE, FILLED);
    putText(window, to_string(currPoints), Point(100, 630), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    //updateWindow();
}

void WindowBowling::changeCurrentRank(string rankNames[])
{
    rectangle(window, Point(295, 550), Point(500, 690), WHITE, FILLED);
    putText(window, rankNames[0], Point(300, 580), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    putText(window, rankNames[1], Point(300, 630), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    putText(window, rankNames[2], Point(300, 680), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
   // updateWindow();
}

void WindowBowling::staticElements(int amountPlayers, int amountRounds)
{
    window = Mat(750, 512, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, CURRENT_PLAYER, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
    
    line(window, Point(10, 540), Point(502, 540), GREY);
    line(window, Point(256, 550), Point(256, 690), GREY);
    
    putText(window, THOWS, Point(10, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, POINTS, Point(10, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    putText(window, "1.", Point(266, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    if (amountPlayers >= 2) putText(window, "2.", Point(266, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    if (amountPlayers == 3) putText(window, "3.", Point(266, 680), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    rectangle(window, Point(10, 700), Point(150, 730), BLUE, FILLED);
}


void WindowBowling::onMouse(int event, int x, int y, int, void* userdata)
{
    WindowBowling* windowBowling = reinterpret_cast<WindowBowling*>(userdata);
    windowBowling->onMouse(event, x, y);
}


void WindowBowling::onMouse(int event, int x, int y)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Yes Mouse Callback" << endl;
    }
}


void WindowBowling::updateWindow()
{
    imshow(WINDOW_BOWLING, window);
}
