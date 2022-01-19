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
    currentPlayer = 1;
    currentThrow = 1;
    currentPoints = 0;
    initPlayerList();
    
    WindowBowling windowBowling;
    windowBowling.changeCurrentPlayer(playersWithPoints[0].first);
    windowBowling.changeCurrentRound(currentRound);
    windowBowling.changeCurrentThrow(currentThrow);
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
            windowBowling.showPinUp(pin);
            windowBowling.changeCurrentPoints(9 - (int) pinsUp.size());
        }
        
        int keyPressed = waitKey(10);
        switch (keyPressed)
        {
            case 27:    // esc
                exitGame();
                break;
            case 110:   // n
                phasePlay = nextThrowPossible();
                break;
        }
        
        if (!phasePlay) break;
        
        windowBowling.changeCurrentThrow(currentThrow);
        windowBowling.changeCurrentPlayer(playersWithPoints[ (currentPlayer - 1) % numberOfPlayers ].first);
        windowBowling.changeCurrentRound(currentRound);
        sortPlayerList();
        windowBowling.changeCurrentRank(playersWithPoints);
        windowBowling.updateWindow();
    }
    
    if (currentRound > ROUNDS_TO_PLAY) restartGame();
    
    destroyWindow(WINDOW_BOWLING);
    destroyWindow(WINDOW_CAMERA);
    
    if (currentRound > ROUNDS_TO_PLAY) exitGame();
}


bool GameManager::nextThrowPossible()
{
    
    // increase throws if numberOf throws is not reached yet
    if (currentThrow < numberOfThrows)
    {
        currentThrow++;
    }
    // if numberOf throws is reached set it backa and switch to the next player
    else
    {
        currentThrow = 1;   // reset throws
        currentPlayer++;
        
        // if the first player is active increase the round count
        if ( (currentPlayer - 1) % numberOfPlayers == 0)
        {
            currentRound++;
        }
        
        if (currentRound > MAX_NR_OF_ROUNDS)
        {
            return false;
        }
    }
    return true;
}


void GameManager::restartGame()
{
    WindowAlert windowAlert(ALERT_GAME_FINISHED);
    
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
