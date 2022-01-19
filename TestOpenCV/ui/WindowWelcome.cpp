//
//  WindowWelcome.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 08.01.22.
//

#include "WindowWelcome.hpp"
#include "../Constants.cpp"

WindowWelcome::WindowWelcome()
{
    nrOfPlayers = MIN_NR_OF_PLAYERS;
    nrOfRounds = MIN_NR_OF_ROUNDS;
    
    placeStaticElements();
    updateWindow();
    setMouseCallback(WINDOW_WELCOME, onMouse, this);
}

WindowWelcome::~WindowWelcome(void) {}

void WindowWelcome::placeStaticElements()
{
    window = Mat(255, 512, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, LBL_WELCOME, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
        
    // Label and buttons -> Amount Players
    putText(window, LBL_PLAYERS, Point(10, 100), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, to_string(nrOfPlayers), Point(350, 100), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, locationBtnMinusNrOfPlayers[0], locationBtnMinusNrOfPlayers[1], GREY, FILLED);
    putText(window, "-", Point(298, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, locationBtnPlusNrOfPlayers[0], locationBtnPlusNrOfPlayers[1], GREY, FILLED);
    putText(window, "+", Point(393, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    // Label and buttons -> Rounds
    putText(window, LBL_ROUNDS, Point(10, 150), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, to_string(nrOfRounds), Point(350, 150), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, locationBtnMinusNrOfRounds[0], locationBtnMinusNrOfRounds[1], GREY, FILLED);
    putText(window, "-", Point(298, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, locationBtnPlusNrOfRounds[0], locationBtnPlusNrOfRounds[1], GREY, FILLED);
    putText(window, "+", Point(393, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    rectangle(window, locationBtnCancel[0], locationBtnCancel[1], BLUE);
    putText(window, BTN_CANCEL, Point(50, 232), FONT_HERSHEY_DUPLEX, 0.8, BLUE);
    rectangle(window, locationBtnPlay[0], locationBtnPlay[1], BLUE, FILLED);
    putText(window, BTN_PLAY, Point(300, 232), FONT_HERSHEY_DUPLEX, 0.8, WHITE);
}

void WindowWelcome::changePlayerAmount()
{
    if ( nrOfPlayers <= MAX_NR_OF_PLAYERS && nrOfPlayers >= MIN_NR_OF_PLAYERS)
    {
        rectangle(window, locationBtnMinusNrOfPlayers[1], locationBtnPlusNrOfPlayers[0], WHITE, FILLED);
        putText(window, to_string(nrOfPlayers), Point(350, 100), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
        updateWindow();
    }
}


void WindowWelcome::changeThrowRounds()
{
    if ( nrOfRounds <= MAX_NR_OF_ROUNDS && nrOfRounds >= MIN_NR_OF_ROUNDS)
    {
        rectangle(window, locationBtnMinusNrOfRounds[1], locationBtnPlusNrOfRounds[0], WHITE, FILLED);
        putText(window, to_string(nrOfRounds), Point(350, 150), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
        updateWindow();
    }
}


void WindowWelcome::onMouse(int event, int x, int y, int, void* userdata)
{
    WindowWelcome* windowWelcome = reinterpret_cast<WindowWelcome*>(userdata);
    windowWelcome->onMouse(event, x, y);
}

int WindowWelcome::onMouse(int event, int x, int y)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        // check the button positions
        if (x >= locationBtnMinusNrOfPlayers[0].x && x <= locationBtnMinusNrOfPlayers[1].x &&
            y >= locationBtnMinusNrOfPlayers[0].y && y <= locationBtnMinusNrOfPlayers[1].y)
        {
            if (nrOfPlayers > MIN_NR_OF_PLAYERS)
            {
                nrOfPlayers--;
                changePlayerAmount();
            }
        }
        else if (x >= locationBtnPlusNrOfPlayers[0].x && x <= locationBtnPlusNrOfPlayers[1].x &&
                 y >= locationBtnPlusNrOfPlayers[0].y && y <= locationBtnPlusNrOfPlayers[1].y)
        {
            if (nrOfPlayers < MAX_NR_OF_PLAYERS)
            {
                nrOfPlayers++;
                changePlayerAmount();
            }
        }
        else if (x >= locationBtnMinusNrOfRounds[0].x && x <= locationBtnMinusNrOfRounds[1].x &&
                 y >= locationBtnMinusNrOfRounds[0].y && y <= locationBtnMinusNrOfRounds[1].y)
        {
            if (nrOfRounds > MIN_NR_OF_ROUNDS)
            {
                nrOfRounds--;
                changeThrowRounds();
            }
        }
        else if (x >= locationBtnPlusNrOfRounds[0].x && x <= locationBtnPlusNrOfRounds[1].x &&
                 y >= locationBtnPlusNrOfRounds[0].y && y <= locationBtnPlusNrOfRounds[1].y)
        {
            if (nrOfRounds < MAX_NR_OF_ROUNDS)
            {
                nrOfRounds++;
                changeThrowRounds();
            }
        }
    }
    return 1;

}


void WindowWelcome::updateWindow()
{
    imshow(WINDOW_WELCOME, window);
}


