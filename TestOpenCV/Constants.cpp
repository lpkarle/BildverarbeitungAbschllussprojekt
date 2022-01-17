//
//  Constants.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 07.01.22.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

// ---------------------------------- Game
const int MAX_NR_OF_PLAYERS = 3;
const int MIN_NR_OF_PLAYERS = 1;
const int MAX_NR_OF_ROUNDS = 2;
const int MIN_NR_OF_ROUNDS = 1;
const int ROUNDS_TO_PLAY = 1;


// ---------------------------------- Strings
// Window Welcome
const string WINDOW_WELCOME = "Window Welcome";
const string WINDOW_BOWLING = "Window Bowling";
const string WINDOW_CAMERA = "Window Camera";
const string WINDOW_ALERT = "Window Alert";
const string LBL_WELCOME = "Welcome to OpenCV-Bowling";
const string LBL_PLAYERS = "Nr of Players:";
const string LBL_ROUNDS = "Nr of Rounds:";
const string BTN_CANCEL = "Cancel";
const string BTN_PLAY = "Play";
const string ALERT_EXIT = "Do you realy want to exit the game?";

// Window Bowlilng
const string CURRENT_PLAYER = "Current Player:";
const string THOWS = "Throw:";
const string POINTS = "Points:";


// ---------------------------------- Colors
const Scalar WHITE = Scalar(255, 255, 255);
const Scalar BLACK = Scalar(0, 0, 0);
const Scalar BLUE = Scalar(255, 150, 0);
const Scalar RED = Scalar(0, 0, 255);
const Scalar GREY = Scalar(200, 200, 200);
const Scalar GREY_DARK = Scalar(43, 43, 43);


