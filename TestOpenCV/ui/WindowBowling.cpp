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
    placeStaticElements();
    initPins();
    updateWindow();
}

WindowBowling::~WindowBowling() {}


/**
 * Show all pins up when the game begins.
 */
void WindowBowling::initPins()  
{
    int pinNr = 1;
    
    for (auto pin : PIN_LOCATIONS)
    {
        circle(window, {pin.x + SHADOW_OFFSET, pin.y + SHADOW_OFFSET}, PIN_SHADOW_RADIUS, GREY, FILLED);  // shadow
        circle(window, pin, PIN_RADIUS, WHITE, FILLED);                                                   // pin
        circle(window, pin, PIN_COVER_RADIUS, RED, FILLED);                                               // cover
        putText(window, to_string(pinNr), {pin.x + OFFSET_TEXT_X, pin.y + OFFSET_TEXT_Y }, FONT_HERSHEY_COMPLEX, FONT_SCALE, GREY_DARK);
        pinNr++;
    }
}


/**
 * Show all pins knocked down by iterating over the PIN_LOCATIONS vector.
 */
void WindowBowling::showAllPinsDown()
{
    for (auto pin : PIN_LOCATIONS)
    {
        circle(window, pin, PIN_KNOCKED_DOWN_RADIUS, GREY, FILLED);
    }
}


/**
 * Show up a pin by its number.
 *
 * @param pinNr number of the pin
 */
void WindowBowling::showPinUp(int pinNr)
{
    if (pinNr < 1 || pinNr > 9) return;
    
    auto pin = PIN_LOCATIONS[pinNr - 1];
    
    circle(window, pin, PIN_BACKGROUND_RADIUS, WHITE, FILLED);                                          // background
    circle(window, {pin.x + SHADOW_OFFSET, pin.y + SHADOW_OFFSET}, PIN_SHADOW_RADIUS, GREY, FILLED);    // shadow
    circle(window, pin, PIN_RADIUS, WHITE, FILLED);                                                     // pin
    circle(window, pin, PIN_COVER_RADIUS, RED, FILLED);                                                 // cover
}


/**
 * Show current player in titlebar.
 *
 * @param currPlayer the current player
 */
void WindowBowling::changeCurrentPlayer(string currPlayer)
{
    rectangle(window, Point(255, 0), Point(512, 50), BLUE, FILLED);
    putText(window, currPlayer, Point(260, 38), FONT_HERSHEY_COMPLEX, 1.2, WHITE);
}


/**
 * Show current game round.
 *
 * @param currRound the current round
 * @param numberOfRounds the requested round amout
 */
void WindowBowling::changeCurrentRound(int currRound, int numberOfRounds)
{
    rectangle(window, Point(100, 550), Point(200, 590), WHITE, FILLED);
    putText(window, to_string(currRound) + "/" + to_string(numberOfRounds), Point(105, 580), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
}


/**
 * Show current players throw.
 *
 * @param currThrow the new points
 */
void WindowBowling::changeCurrentThrow(int currThrow)
{
    rectangle(window, Point(100, 600), Point(200, 640), WHITE, FILLED);
    putText(window, to_string(currThrow) + "/" + to_string(NR_OF_THROWS), Point(105, 630), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
}


/**
 * Show current players points.
 *
 * @param currPoints the new points
 */
void WindowBowling::changeCurrentPoints(int currPoints)
{
    rectangle(window, Point(100, 650), Point(200, 690), WHITE, FILLED);
    putText(window, to_string(currPoints), Point(105, 680), FONT_HERSHEY_COMPLEX, 0.8, GREY_DARK);
}


/**
 * Show the game score.
 *
 * @param playerRank a vector of tuples (player and  points)
 */
void WindowBowling::changeCurrentRank(vector<pair<string, int>> playerRank)
{
    rectangle(window, Point(295, 550), Point(500, 690), WHITE, FILLED);
    
    // no check needed because one player is minimum
    string firstPlace = "1. " + playerRank[0].first + " (" + to_string(playerRank[0].second) + ")";
    putText(window, firstPlace, Point(266, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    if (playerRank.size() >= 2)
    {
        string secondPlace = "2. " + playerRank[1].first + " (" + to_string(playerRank[1].second) + ")";
        putText(window, secondPlace, Point(266, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    }
    
    if (playerRank.size() == 3)
    {
        string thirdPlace = "3. " + playerRank[2].first + " (" + to_string(playerRank[2].second) + ")";
        putText(window, thirdPlace, Point(266, 680), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    }
}


/**
 * Initialize the window Mat and place the static UI elements.
 */
void WindowBowling::placeStaticElements()
{
    window = Mat(WINDOW_HEIGHT, WINDOW_WIDTH, CV_8UC3, WHITE);
    
    rectangle(window, Point(0, 0), Point(512, 50), BLUE, FILLED);
    putText(window, CURRENT_PLAYER, Point(10, 35), FONT_HERSHEY_DUPLEX, 1, WHITE);
    
    line(window, Point(10, 540), Point(502, 540), GREY);
    line(window, Point(256, 550), Point(256, 690), GREY);
    
    putText(window, ROUND, Point(10, 580), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, THOWS, Point(10, 630), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    putText(window, POINTS, Point(10, 680), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    
    rectangle(window, Point(10, 700), Point(250, 740), BLUE, 1);
    putText(window, BTN_CANCEL, Point(50, 730), FONT_HERSHEY_DUPLEX, 0.8, BLUE);
    
    rectangle(window, Point(272, 700), Point(502, 740), BLUE, FILLED);
    putText(window, BTN_NEXT, Point(340, 730), FONT_HERSHEY_DUPLEX, 0.8, WHITE);
}


/**
 * Show / update the window.
 */
void WindowBowling::updateWindow()
{
    imshow(WINDOW_BOWLING, window);
}
