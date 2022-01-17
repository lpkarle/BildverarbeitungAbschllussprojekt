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

const vector<Point> pinLocations = {
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

const int shadowOffset = 1;
const int pinRadius = 20;
const int pinCoverRadius = 8;
const int pinShadowRadius = 21;
const int pinKnockDownRadius = 22;
const int pinBackgroundRadius = 25;
const double fontScale = 0.75;

class WindowBowling
{
private:
    
    const int OFFSET_TEXT_X = 25;
    const int OFFSET_TEXT_Y = 20;
        
    Mat window;
    void initPins();
    void updateWindow();
    
public:
    WindowBowling(int amountPlayers, int amountRounds);
    ~WindowBowling();
    
    void staticElements(int amountPlayers, int amountRounds);
    void changeCurrentPlayer(int currPlayer);
    void changeCurrentThrow(int currThrow);
    void changeCurrentPoints(int currPoints);
    void changeCurrentRank(string rankNames[]);
    void showPinUp(int pinNr);
    void showPinDown(int pinNr);
    void allPinsDown();
};

#endif /* Window_Bowling_hpp */
