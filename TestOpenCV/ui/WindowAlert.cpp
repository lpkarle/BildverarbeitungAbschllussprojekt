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


/**
 * Initialize the window Mat and place the static UI elements.
 */
void WindowAlert::placeStaticElements()
{
    window = Mat(WINDOW_HEIGHT, WINDOW_WIDH, CV_8UC3, WHITE);
    rectangle(window, Point(0, 0), Point(WINDOW_WIDH, 50), BLUE, FILLED);
    putText(window, msg, Point(10, 35), FONT_HERSHEY_DUPLEX, 0.75, WHITE);
    
    rectangle(window, BTN_LOC_YES[0], BTN_LOC_YES[1], BLUE);
    putText(window, BTN_YES, Point(90, 232), FONT_HERSHEY_DUPLEX, 0.8, BLUE);
    rectangle(window, BTN_LOC_NO[0], BTN_LOC_NO[1], BLUE, FILLED);
    putText(window, BTN_NO, Point(340, 232), FONT_HERSHEY_DUPLEX, 0.8, WHITE);
}


/**
 * Show the game result.
 *
 * @param playerRank a vector of tuples (player and  points)
 */
void WindowAlert::showResult(vector<pair<string, int>> playerRank)
{
    rectangle(window, Point(10, 55), Point(500, 200), WHITE, FILLED);
    
    if (playerRank.size() >= 1)
    {
        string firstPlace = "1. " + playerRank[0].first + " (" + to_string(playerRank[0].second) + ")";
        putText(window, firstPlace, Point(50, 85), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    }
    if (playerRank.size() >= 2)
    {
        string secondPlace = "2. " + playerRank[1].first + " (" + to_string(playerRank[1].second) + ")";
        putText(window, secondPlace, Point(50, 135), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    }
    if (playerRank.size() == 3)
    {
        string thirdPlace = "3. " + playerRank[2].first + " (" + to_string(playerRank[2].second) + ")";
        putText(window, thirdPlace, Point(50, 185), FONT_HERSHEY_DUPLEX, 0.8, GREY_DARK);
    }
    updateWindow();
}


/**
 * Show / update the window.
 */
void WindowAlert::updateWindow()
{
    imshow(WINDOW_ALERT, window);
}
