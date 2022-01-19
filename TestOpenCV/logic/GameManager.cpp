//
//  GameManager.cpp
//  TestOpenCV
//
//  Created by Lukas Karle on 12.01.22.
//

#include "GameManager.hpp"
#include "../Constants.cpp"


GameManager::GameManager()
{
    initGame();
}

GameManager::~GameManager() { }


void GameManager::initGame()
{
    phaseInitialize = true;
    WindowWelcome windowWelcome;
    
    while (phaseInitialize)
    {
        int keyPressed = waitKey(0);
        switch (keyPressed)
        {
            case 27:    // esc
                exitGame();
                break;
            case 110:   // c
                exitGame();
                break;
            case 13:    // enter
                cout<<"Enter Game"<<endl;
                phaseInitialize = false;
                phasePlay = true;
                numberOfPlayers = windowWelcome.getNrOfPlayers();
                numberOfThrows = windowWelcome.getNrOfRounds();
                break;
        }
        if (!phaseInitialize) break;
    }
        
    destroyWindow(WINDOW_WELCOME);
    
    if (phasePlay) { playGame(); }
}


void GameManager::initPlayerList()
{
    playersWithPoints.clear();
    if (numberOfPlayers >= 1) { playersWithPoints.emplace_back(PLAYER_ONE, 0); }
    if (numberOfPlayers >= 2) { playersWithPoints.emplace_back(PLAYER_TWO, 0); }
    if (numberOfPlayers >= 3) { playersWithPoints.emplace_back(PLAYER_THREE, 0); }
}


void GameManager::sortPlayerList()
{
    for (int i = 0; i < (int) playersWithPoints.size(); i++)
    {
        auto currListEl = playersWithPoints[i]; // compare the first element
        
        for (int j = i; j < (int) playersWithPoints.size(); j++)
        {
            if (playersWithPoints[j].second > currListEl.second)
            {
                auto currentMin = playersWithPoints[j];
                playersWithPoints[i] = currentMin;
                playersWithPoints[j] = currListEl;
            }
        }
    }
}


void GameManager::playGame()
{
    destroyWindow(WINDOW_WELCOME);
    
    phasePlay = true;
    currentRound = 1;
    firstRound = true;
    currentPlayer = 1;
    currentThrow = 1;
    currentPoints = 0;
    initPlayerList();
    
    WindowBowling windowBowling;
    windowBowling.changeCurrentPlayer(playersWithPoints[0].first);
    windowBowling.changeCurrentRound(currentRound);
    windowBowling.changeCurrentThrow(currentThrow, numberOfThrows);
    windowBowling.changeCurrentPoints(currentPoints);
    sortPlayerList();
    windowBowling.changeCurrentRank(playersWithPoints);
    
    CameraFeed cameraFeed;
    vector<int> pinsUp;
    
    while (phasePlay)
    {
        windowBowling.allPinsDown();
        pinsUp = cameraFeed.start();
        
        for (auto pin : pinsUp)
        {
            currentPoints = 9 - (int) pinsUp.size();
            windowBowling.showPinUp(pin);
            windowBowling.changeCurrentPoints(currentPoints);
        }
        
        int keyPressed = waitKey(10);
        switch (keyPressed)
        {
            case 27:    // esc
                exitGame();
                break;
            case 110:   // n
                nextThrow();
                nextPlayer();
               
                break;
        }
        
        windowBowling.changeCurrentThrow(currentThrow, numberOfThrows);
        windowBowling.changeCurrentPlayer(playersWithPoints[ (currentPlayer - 1) % numberOfPlayers ].first);
        windowBowling.changeCurrentRound(currentRound);
        sortPlayerList();
        windowBowling.changeCurrentRank(playersWithPoints);
        windowBowling.updateWindow();

        if (!phasePlay) break;
    }
    
    destroyWindow(WINDOW_BOWLING);
    destroyWindow(WINDOW_CAMERA);
    
    if (currentRound >= ROUNDS_TO_PLAY) restartGame();
}


void GameManager::nextThrow()
{
    if(currentThrow <= numberOfThrows) { currentThrow++; }
    
    auto playerIndex = (currentPlayer - 1) % numberOfPlayers;
    playersWithPoints[ playerIndex ].second += currentPoints;
    currentPoints = 0;
}


void GameManager::nextPlayer()
{
    if (currentThrow > numberOfThrows)
    {
        currentPlayer++;
        currentThrow = 1;
        
        phasePlay = checkNextRound();
    }
}


bool GameManager::checkNextRound()
{
    if ( (currentPlayer - 1) % numberOfPlayers == 0)
    {
        currentRound++;
    }
                
    if (currentRound > ROUNDS_TO_PLAY)
    {
        return false;
    }
    
    return true;
}


void GameManager::restartGame()
{
    WindowAlert windowAlert(ALERT_GAME_FINISHED);
    windowAlert.showResult(playersWithPoints);
    
    int keyPressed = waitKey(0);
    switch (keyPressed)
    {
        case 121:   // y
            initGame();
            break;
        case 110:   // n
            break;
    }
    
    phaseInitialize = false;
    phasePlay = false;
    destroyWindow(ALERT_GAME_FINISHED);
}


void GameManager::exitGame()
{
    WindowAlert windowAlert(ALERT_EXIT);
    
    int keyPressed = waitKey(0);
    switch (keyPressed)
    {
        case 121:    // y
            phaseInitialize = false;
            phasePlay = false;
            break;
        case 110:   // n
            break;
    }
    destroyWindow(WINDOW_ALERT);
}
