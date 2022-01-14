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

const Point locationBtnMinusNrOfPlayers[ 2 ] = { Point(290, 80), Point(330, 105) };
const Point locationBtnPlusNrOfPlayers[ 2 ]  = { Point(385, 80), Point(425, 105) };
const Point locationBtnMinusNrOfRounds[ 2 ] = { Point(290, 130), Point(330, 155) };
const Point locationBtnPlusNrOfRounds[ 2 ]  = { Point(385, 130), Point(425, 155) };
const Point locationBtnCancel[ 2 ] = { Point(10, 200), Point(250, 240) };
const Point locationBtnPlay[ 2 ]   = { Point(272, 200), Point(502, 240) };


class WindowWelcome
{
private:
    string windowName = "window_welcome";
    Mat window;
    int nrOfPlayers = 2;
    int nrOfRounds  = 1;
    bool cancelClicked = false;
    bool playClicked = false;
    
    void(*callbackCancel)();
    
    int onMouse(int event, int x, int y);
    static void onMouse(int event, int x, int y, int, void* userdata);
        
    void placeStaticElements();
    
    
public:
    void updateWindow();
    // WindowWelcome(void);
    WindowWelcome(void(*func)());
    ~WindowWelcome(void);
    
    //void mouseCallback(int event, int x, int y, int flags, void* userdata);
    void changePlayerAmount();
    void changeThrowRounds();
    Mat getWindow() { return window; };
    int getNrOfPlayers() { return nrOfPlayers; };
    int getNrOfRounds() { return nrOfRounds; };
    bool getCancelClicked() { return cancelClicked; };
    bool getPlayClicked() { return playClicked; };
};


enum Buttons { PLAYER_PLUS, PLAYER_MINUS, ROUND_PLUS, ROUND_MINUS, CANCEL, PLAY};


#endif /* WindowWelcome_hpp */
