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
    int numberOfRounds;
    int currentPlayer;
    int currentThrow;
    int currentPoints;
    int currentRound;
    bool firstRound;
    bool lastRound;
    vector<pair<string, int>> playersWithPoints;
    
    bool phaseInitialize;
    bool phasePlay;
    
    bool phaseThrow;
    bool phaseGameFinished;
    
    
    void initGame();
    void playGame();
    void initPlayerList();
    void sortPlayerList();
    static bool sortBySec(const pair<string,int> &a,
                   const pair<string,int> &b);
    
    void nextThrow();
    void nextPlayer();
    bool checkNextRound();
    
    void restartGame();
    void exitGame();
    
public:
    GameManager();
    ~GameManager();
};

#endif /* GameManager_hpp */
