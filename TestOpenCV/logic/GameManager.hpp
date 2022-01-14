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
    int numberOfPlayers = 1;
    int numberOfThrows = 1;
    
public:
    GameManager(void);
    ~GameManager(void);
};

#endif /* GameManager_hpp */
