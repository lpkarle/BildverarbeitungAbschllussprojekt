//
//  WindowWelcome.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 08.01.22.
//

#ifndef WindowWelcome_hpp
#define WindowWelcome_hpp

#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


class WindowWelcome
{
private:
    const int WINDOW_WIDTH = 512;
    const int WINDOW_HEIGHT = 255;
    const Point BTN_LOC_PLAYER_MINUS[ 2 ] = { Point(290, 80), Point(330, 105) };
    const Point BTN_LOC_PLAYER_PLUS[ 2 ]  = { Point(385, 80), Point(425, 105) };
    const Point BTN_LOC_ROUNDS_MINUS[ 2 ] = { Point(290, 130), Point(330, 155) };
    const Point BTN_LOC_ROUNDS_PLUS[ 2 ]  = { Point(385, 130), Point(425, 155) };
    const Point BTN_LOC_CANCEL[ 2 ] = { Point(10, 205), Point(250, 245) };
    const Point BTN_LOC_PLAY[ 2 ]   = { Point(262, 205), Point(502, 245) };
    
    Mat window;
    int nrOfPlayers;
    int nrOfRounds;
        
    void placeStaticElements();
    void onMouse(int event, int x, int y);
    static void onMouse(int event, int x, int y, int, void* userdata);
    
public:
    WindowWelcome();
    ~WindowWelcome();
    
    void changePlayerAmount();
    void changeRoundAmount();
    int getNrOfPlayers() { return nrOfPlayers; };
    int getNrOfRounds() { return nrOfRounds; };
    void updateWindow();
};


#endif /* WindowWelcome_hpp */
