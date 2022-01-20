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
            case 13:    // enter
                phaseInitialize = false;
                phasePlay = true;
                numberOfPlayers = windowWelcome.getNrOfPlayers();
                numberOfRounds = windowWelcome.getNrOfRounds();
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
    sort(playersWithPoints.begin(), playersWithPoints.end(), sortBySec);
}


bool GameManager::sortBySec(const pair<string,int> &a, const pair<string,int> &b)
{
    return (a.second > b.second);
}


void GameManager::playGame()
{
    phasePlay = true;
    currentRound = 1;
    firstRound = true;
    
    currentPlayer = 1;
    currentThrow = 1;
    currentPoints = 0;
    initPlayerList();
    
    WindowBowling windowBowling;
    windowBowling.changeCurrentPlayer(playersWithPoints[0].first);
    windowBowling.changeCurrentRound(currentRound, numberOfRounds);
    windowBowling.changeCurrentThrow(currentThrow);
    windowBowling.changeCurrentPoints(currentPoints);
    windowBowling.changeCurrentRank(playersWithPoints);
    
    CameraFeed cameraFeed;
    vector<int> pinsUp;
    
    while (phasePlay)
    {
        windowBowling.showAllPinsDown();
        pinsUp = cameraFeed.startReceivingPinsUp();
        
        for (auto pin : pinsUp)
        {
            windowBowling.showPinUp(pin);
        }
        currentPoints = 9 - (int) pinsUp.size();
        windowBowling.changeCurrentPoints(currentPoints);
        
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
        
        windowBowling.changeCurrentThrow(currentThrow);
        windowBowling.changeCurrentPlayer(playersWithPoints[ (currentPlayer - 1) % numberOfPlayers ].first);
        windowBowling.changeCurrentRound(currentRound, numberOfRounds);
        windowBowling.changeCurrentRank(playersWithPoints);
        windowBowling.updateWindow();

        if (!phasePlay) break;
    }
    
    destroyWindow(WINDOW_BOWLING);
    destroyWindow(WINDOW_CAMERA);
    
    restartGame();
}


void GameManager::nextThrow()
{
    if (currentThrow <= NR_OF_THROWS) { currentThrow++; }
}


void GameManager::nextPlayer()
{
    if (currentThrow > NR_OF_THROWS)
    {
        phasePlay = checkNextRound();
        
        auto playerIndex = (currentPlayer - 1) % numberOfPlayers;
        playersWithPoints[ playerIndex ].second += currentPoints;
        currentPoints = 0;
        
        if (phasePlay)
        {
            currentPlayer++;
            currentThrow = 1;
        }
    }
}


bool GameManager::checkNextRound()
{
    if (currentRound == numberOfRounds && currentPlayer % numberOfPlayers == 0)
    {
        return false;
    }
    
    if (currentPlayer % numberOfPlayers == 0)
    {
        currentRound++;
    }
    return true;
}


void GameManager::restartGame()
{
    WindowAlert windowAlert(ALERT_GAME_FINISHED);
    sortPlayerList();
    windowAlert.showResult(playersWithPoints);
    
    int keyPressed = waitKey(0);
    switch (keyPressed)
    {
        case 121:   // y
            destroyWindow(WINDOW_ALERT);
            initGame();
            break;
        case 110:   // n
            destroyWindow(WINDOW_ALERT);
            break;
    }
    phaseInitialize = false;
    phasePlay = false;
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
