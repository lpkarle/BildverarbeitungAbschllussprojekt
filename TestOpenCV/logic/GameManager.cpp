//
//  GameManager.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 12.01.22.
//

#include "GameManager.hpp"
#include "../Constants.cpp"


GameManager::GameManager() { }

GameManager::~GameManager() { }

/**
 
 */
void GameManager::startGameWith(int numberOfPlayers, int numberOfThrows)
{
    this->numberOfPlayers = numberOfPlayers;
    this->numberOfThrows = numberOfThrows;
    
    initializeGame();
}

void GameManager::initializeGame()
{
    currentRound = 1;
    currentPlayer = 0;
    currentThrow = 1;
}
