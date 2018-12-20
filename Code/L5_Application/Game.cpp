/*
 * Game.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */


#include <Game.h>

Game::Game(uint8_t boardX,uint8_t boardY)
{
    initState(boardX,boardY,LEVEL,0);//GAME STARTS @ LEVEL1
}

Game::~Game()
{
    // TODO Auto-generated destructor stub
}

void Game::initState(uint8_t boardX, uint8_t boardY,int8_t level,int8_t score)
{
    x=boardX;
    y=boardX;
    //Properties of Game:
    totalObj=0;
    totalObjCaught=0;
    this->score=score;
    this->level=level;
    missPenalty=1;
    isGameOver=false;
    //isWin=false;//:: True-GameOver| False-Play
    //isPause=true;
    gameStatus=PLAYGAME;

}
