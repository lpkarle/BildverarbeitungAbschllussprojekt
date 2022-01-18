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


vector<string> GameManager::initPlayerList()
{
    vector<string> playerList;
    
    if (numberOfPlayers >= 1) { playerList.insert(playerList.end(), PLAYER_ONE); }
    if (numberOfPlayers >= 2) { playerList.insert(playerList.end(), PLAYER_TWO); }
    if (numberOfPlayers >= 3) { playerList.insert(playerList.end(), PLAYER_THREE); }
    return playerList;
}


void GameManager::playGame()
{
    destroyWindow(WINDOW_WELCOME);
    
    phasePlay = true;
    currentRound = 1;
    currentPlayer = 1;
    currentThrow = 1;
    auto playerList = initPlayerList();
    
    WindowBowling windowBowling;
    windowBowling.changeCurrentPlayer(playerList[0]);
    windowBowling.changeCurrentRound(currentRound);
    windowBowling.changeCurrentThrow(currentThrow);
    windowBowling.changeCurrentPoints(0);
    windowBowling.changeCurrentRank(playerList);
    
    CameraFeed cameraFeed;
    
    while (phasePlay)
    {
        windowBowling.allPinsDown();
        
        for (auto pin : cameraFeed.start())
        {
            windowBowling.showPinUp(pin);
            
        }
        
        int keyPressed = waitKey(10);
        switch (keyPressed)
        {
            case 27:    // esc
                exitGame();
                break;
            case 99:    // c
                exitGame();
                break;
            case 110:   // n
                phasePlay = nextThrowPossible();
                break;
        }
        
        if (!phasePlay) break;
        
        windowBowling.changeCurrentThrow(currentThrow);
        windowBowling.changeCurrentPlayer(playerList[ (currentPlayer - 1) % numberOfPlayers ]);
        windowBowling.changeCurrentRound(currentRound);
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
