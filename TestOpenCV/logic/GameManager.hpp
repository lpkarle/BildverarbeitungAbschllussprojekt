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

using namespace std;


class GameManager
{
private:
    int numberOfPlayers;
    int numberOfThrows;
    int currentPlayer;
    int currentThrow;
    int currentRound;
    
    bool phaseThrow;
    bool phaseGameFinished;
    
    void initializeGame();
    
public:
    GameManager();
    ~GameManager();
    
    void setNumberOfPlayers(int numberOfPlayers) { this->numberOfPlayers = numberOfPlayers; }
    void setNumberOfThrows(int numberOfThrows) { this->numberOfThrows = numberOfThrows; }
    
    void startGameWith(int numberOfPlayers, int numberOfThrows);
    void endGame();
};

#endif /* GameManager_hpp */
