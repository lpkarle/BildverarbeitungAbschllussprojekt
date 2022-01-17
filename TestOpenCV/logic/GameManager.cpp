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
    initializeGame();
}

GameManager::~GameManager() { }


void GameManager::initializeGame()
{
    phaseInitialize = true;
    
    currentRound = 1;
    currentPlayer = 0;
    currentThrow = 1;

    WindowWelcome windowWelcome;
    
    while (phaseInitialize)
    {
        int keyPressed = waitKey(10);
        switch (keyPressed)
        {
            case 27:    // esc
                phaseInitialize = false;
                break;
            case 110:   // c
                cout<<"Next Player"<<endl;
                phaseInitialize = false;
                break;
            case 13:    // enter
                cout<<"Enter Game"<<endl;
                phaseInitialize = false;
                phasePlay = true;
                break;
        }
        
        if (!phaseInitialize) break;
    }
    
    numberOfPlayers = windowWelcome.getNrOfPlayers();
    numberOfThrows = windowWelcome.getNrOfRounds();
    
    cout << "Player Amount " << numberOfPlayers << " Number of Throws " << numberOfThrows << endl;
    
    destroyWindow(WINDOW_WELCOME);
    
    if (phasePlay) { playGame(); }
    
}


void GameManager::playGame()
{
    cout << "PLAY" << endl;
    WindowBowling windowBowling;
    CameraFeed cameraFeed(windowBowling);
}
