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


/**
 * Phase initialize of the bowling game.
 *
 * Initializes a WelcomeWindow object and waits until the configuration is finished.
 * Waits until 'return' or 'esc' is pressed.
 *
 * 'return' -> Next phase play.
 * 'esc' -> Opens a close game dialog.
 */
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


/**
 * Initializes the player list with name and points.
 */
void GameManager::initPlayerList()
{
    playersWithPoints.clear();
    if (numberOfPlayers >= 1) { playersWithPoints.emplace_back(PLAYER_ONE, 0); }
    if (numberOfPlayers >= 2) { playersWithPoints.emplace_back(PLAYER_TWO, 0); }
    if (numberOfPlayers >= 3) { playersWithPoints.emplace_back(PLAYER_THREE, 0); }
}


/**
 * Sorts the player list for award ceremony.
 */
void GameManager::sortPlayerList()
{
    sort(playersWithPoints.begin(), playersWithPoints.end(), sortBySec);
}


/**
 * Compares two pair values. Used for sorting the playersWithPoints vector.
 *
 * @param a value a of the vector
 * @param b value a of the vector
 * @return true if a is greater than b
 */
bool GameManager::sortBySec(const pair<string,int> &a, const pair<string,int> &b)
{
    return (a.second > b.second);
}


/**
 * Phase play of the bowling game.
 *
 * Initializes a WindowBowling object for displaying the result and a CamerFeed object for showing and processing
 * the camera feed. Waits until 'n' or 'esc' is pressed.
 *
 * 'n' -> Next throw.
 * 'esc' -> Opens a close game dialog.
 */
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


/**
 * Increases the currentThrow if there are throws left.
 */
void GameManager::nextThrow()
{
    if (currentThrow <= NR_OF_THROWS) { currentThrow++; }
}


/**
 * Check if its the next players turn.
 * If so increase currentPlayer and reset currentThrow to 1.
 */
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


/**
 * Check if the round is finished.
 * return false if the game is finised.
 */
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


/**
 * Opens a restart window alert.
 *
 * Waits until 'n' or 'y' is pressed.
 * 'n' -> Back to current window.
 * 'y' -> Opens a close game dialog.
 */
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


/**
 * Opens a exit game window alert.
 *
 * Waits until 'n' or 'y' is pressed.
 * 'n' -> Back to current window.
 * 'y' -> Closes the program.
 */
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
