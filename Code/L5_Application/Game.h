/*
 * Game.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef GAME_H_
#define GAME_H_
#include <stdint.h>
#include <stdlib.h>
#include "CONSTANTS.hpp"


//#include "Objects.h"
class Game {
public:
    Game(uint8_t boardX,uint8_t boardY);
    //Dimensions of game
    uint8_t x;
    uint8_t y;

    //Properties of Game:
    uint8_t totalObj;
    uint8_t totalObjCaught;
    uint8_t missPenalty;
    uint8_t score;
    int8_t level;
    int8_t gameStatus;//::GAMEOVER-1|WIN-2|PLAYGAME-3|PAUSEGAME-4
   // bool isGameOver,isWin,isPause; //:: True-GameOver| False-Play

    bool isGameOver;
    virtual ~Game();

   void initState(uint8_t boardX,uint8_t boardY,int8_t level,int8_t score);
};

#endif /* GAME_H_ */
