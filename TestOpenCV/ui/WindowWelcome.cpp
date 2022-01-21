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


WindowWelcome::~WindowWelcome(void) { }


/**
 * Initialize the window Mat and place the static UI elements.
 */
void WindowWelcome::placeStaticElements()
{
    window = Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, LBL_WELCOME, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
        
    // Label and buttons -> Amount Players
    putText(window, LBL_PLAYERS, Point(10, 100), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, to_string(nrOfPlayers), Point(350, 100), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, BTN_LOC_PLAYER_MINUS[0], BTN_LOC_PLAYER_MINUS[1], GREY, FILLED);
    putText(window, "-", Point(298, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, BTN_LOC_PLAYER_PLUS[0], BTN_LOC_PLAYER_PLUS[1], GREY, FILLED);
    putText(window, "+", Point(393, 102), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    // Label and buttons -> Rounds
    putText(window, LBL_ROUNDS, Point(10, 150), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, to_string(nrOfRounds), Point(350, 150), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
    
    rectangle(window, BTN_LOC_ROUNDS_MINUS[0], BTN_LOC_ROUNDS_MINUS[1], GREY, FILLED);
    putText(window, "-", Point(298, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    rectangle(window, BTN_LOC_ROUNDS_PLUS[0], BTN_LOC_ROUNDS_PLUS[1], GREY, FILLED);
    putText(window, "+", Point(393, 152), FONT_HERSHEY_DUPLEX, 1, GREY_DARK);
    
    rectangle(window, BTN_LOC_CANCEL[0], BTN_LOC_CANCEL[1], BLUE);
    putText(window, BTN_CANCEL, Point(50, 232), FONT_HERSHEY_DUPLEX, 0.8, BLUE);
    rectangle(window, BTN_LOC_PLAY[0], BTN_LOC_PLAY[1], BLUE, FILLED);
    putText(window, BTN_PLAY, Point(300, 232), FONT_HERSHEY_DUPLEX, 0.8, WHITE);
}


/**
 * Changes the player amount by printing a white rectangle over the current value and create a new
 * text element at the same position.
 */
void WindowWelcome::changePlayerAmount()
{
    if ( nrOfPlayers <= MAX_NR_OF_PLAYERS && nrOfPlayers >= MIN_NR_OF_PLAYERS)
    {
        rectangle(window, Point(332, 105), Point(383, 80), WHITE, FILLED);
        putText(window, to_string(nrOfPlayers), Point(350, 100), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
        updateWindow();
    }
}


/**
 * Changes the round amount by printing a white rectangle over the current value and create a new
 * text element at the same position.
 */
void WindowWelcome::changeRoundAmount()
{
    if ( nrOfRounds <= MAX_NR_OF_ROUNDS && nrOfRounds >= MIN_NR_OF_ROUNDS)
    {
        rectangle(window, Point(332, 155), Point(383, 130), WHITE, FILLED);
        putText(window, to_string(nrOfRounds), Point(350, 150), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
        updateWindow();
    }
}


/**
 * Static mouse callback.
 */
void WindowWelcome::onMouse(int event, int x, int y, int, void* userdata)
{
    WindowWelcome* windowWelcome = reinterpret_cast<WindowWelcome*>(userdata);
    windowWelcome->onMouse(event, x, y);
}


/**
 * Mouse callback listening on the left mouse down event.
 *
 * Handels the decrease and increase of the player and round amount.
 * Checks if left mouse is down and if the coordinates match with the button areas.
 *
 * @param event Mouse event (left)
 * @param x coordinate of the click
 * @param y coordinate of the click
 */
void WindowWelcome::onMouse(int event, int x, int y)
{
    if  ( event == EVENT_LBUTTONDOWN )
    {
        // check the button positions
        if (x >= BTN_LOC_PLAYER_MINUS[0].x && x <= BTN_LOC_PLAYER_MINUS[1].x &&
            y >= BTN_LOC_PLAYER_MINUS[0].y && y <= BTN_LOC_PLAYER_MINUS[1].y)
        {
            if (nrOfPlayers > MIN_NR_OF_PLAYERS)
            {
                nrOfPlayers--;
                changePlayerAmount();
            }
        }
        else if (x >= BTN_LOC_PLAYER_PLUS[0].x && x <= BTN_LOC_PLAYER_PLUS[1].x &&
                 y >= BTN_LOC_PLAYER_PLUS[0].y && y <= BTN_LOC_PLAYER_PLUS[1].y)
        {
            if (nrOfPlayers < MAX_NR_OF_PLAYERS)
            {
                nrOfPlayers++;
                changePlayerAmount();
            }
        }
        else if (x >= BTN_LOC_ROUNDS_MINUS[0].x && x <= BTN_LOC_ROUNDS_MINUS[1].x &&
                 y >= BTN_LOC_ROUNDS_MINUS[0].y && y <= BTN_LOC_ROUNDS_MINUS[1].y)
        {
            if (nrOfRounds > MIN_NR_OF_ROUNDS)
            {
                nrOfRounds--;
                changeRoundAmount();
            }
        }
        else if (x >= BTN_LOC_ROUNDS_PLUS[0].x && x <= BTN_LOC_ROUNDS_PLUS[1].x &&
                 y >= BTN_LOC_ROUNDS_PLUS[0].y && y <= BTN_LOC_ROUNDS_PLUS[1].y)
        {
            if (nrOfRounds < MAX_NR_OF_ROUNDS)
            {
                nrOfRounds++;
                changeRoundAmount();
            }
        }
    }
}


/**
 * Show / update the window.
 */
void WindowWelcome::updateWindow()
{
    imshow(WINDOW_WELCOME, window);
}


