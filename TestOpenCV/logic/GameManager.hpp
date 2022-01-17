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
#include "../ui/WindowAlert.hpp"

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
    
    
    void initializeGame();
    void playGame();
    void exitGame();
    void endGame();
    
public:
    GameManager();
    ~GameManager();
};

#endif /* GameManager_hpp */
