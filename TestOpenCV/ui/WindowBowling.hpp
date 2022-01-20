//
//  Window_Bowling.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#ifndef Window_Bowling_hpp
#define Window_Bowling_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class WindowBowling
{
private:
    const int WINDOW_WIDTH = 512;
    const int WINDOW_HEIGHT = 750;
    
    // Pin constants
    const vector<Point> PIN_LOCATIONS = {
        Point(256, 488),
        Point(160, 392),
        Point(352, 392),
        Point( 64, 296),
        Point(256, 296),
        Point(448, 296),
        Point(160, 200),
        Point(352, 200),
        Point(256, 104)
    };
    const int SHADOW_OFFSET = 1;
    const int PIN_RADIUS = 20;
    const int PIN_COVER_RADIUS = 8;
    const int PIN_SHADOW_RADIUS = 21;
    const int PIN_KNOCKED_DOWN_RADIUS = 22;
    const int PIN_BACKGROUND_RADIUS = 25;
    const double FONT_SCALE = 0.75;
    const int OFFSET_TEXT_X = 25;
    const int OFFSET_TEXT_Y = 20;

    Mat window;
    void placeStaticElements();
    void initPins();
    
public:
    WindowBowling();
    ~WindowBowling();
    
    void changeCurrentPlayer(string currPlayer);
    void changeCurrentRound(int currRound, int numberOfRounds);
    void changeCurrentThrow(int currThrow);
    void changeCurrentPoints(int currPoints);
    void changeCurrentRank(vector<pair<string, int>> playerRank);
    void showPinUp(int pinNr);
    void showAllPinsDown();
    void updateWindow();
};


#endif /* Window_Bowling_hpp */
