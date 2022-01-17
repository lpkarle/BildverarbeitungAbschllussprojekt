//
//  GameManager.hpp
//  TestOpenCV
//
//  Created by Lukas Karle on 12.01.22.
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include <iostream>
#include "../ui/WindowWelcome.hpp"
#include "../ui/WindowBowling.hpp"
#include "../ui/CameraFeed.hpp"

using namespace std;


class GameManager
{
private:
    int numberOfPlayers;
    int numberOfThrows;
    int currentPlayer;
    int currentThrow;
    int currentRound;
    
    bool phaseInitialize;
    bool phasePlay;
    
    bool phaseThrow;
    bool phaseGameFinished;
    
    WindowWelcome windowWelcome;
    WindowBowling windowBowling;
    
    void initializeGame();
    void playGame();
    void endGame();
    
public:
    GameManager(WindowWelcome windowWelcome, WindowBowling windowBowling);
    ~GameManager();
};

#endif /* GameManager_hpp */
