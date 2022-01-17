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
    
    if (phasePlay) { playGame(initPlayerList()); }
}


vector<string> GameManager::initPlayerList()
{
    vector<string> playerList;
    
    if (numberOfPlayers >= 1) { playerList.insert(playerList.end(), PLAYER_ONE); }
    if (numberOfPlayers >= 2) { playerList.insert(playerList.end(), PLAYER_TWO); }
    if (numberOfPlayers >= 3) { playerList.insert(playerList.end(), PLAYER_THREE); }
    return playerList;
}


void GameManager::playGame(vector<string> playerList)
{
    cout << "PLAY" << endl;
    WindowBowling windowBowling;
    windowBowling.changeCurrentRank(playerList);
    CameraFeed cameraFeed(windowBowling);
}


void GameManager::exitGame()
{
    WindowAlert windowAlert(ALERT_EXIT);
    
    int keyPressed = waitKey(0);
    switch (keyPressed)
    {
        case 121:    // y
            phaseInitialize = false;
            break;
        case 110:   // n
            break;
    }
    destroyWindow(WINDOW_ALERT);
}
