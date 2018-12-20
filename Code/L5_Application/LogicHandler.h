/*
 * LogicHandler.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef LOGICHANDLER_H_
#define LOGICHANDLER_H_

#include "InputHandler.h"
#include "Basket.h"
#include "Game.h"
#include "Objects.h"
#include "Water.h"
#include <math.h>
#include <stdio.h>
#include "CONSTANTS.hpp"

class LogicHandler {

    private:
        void slideBasket(InputHandler& ipObj,Basket& bskObj,Game & gameObj);
        void stopSlidingAtEdge(Basket& bskObj,Game & gameObj);
        void checkIfGameOver(Game & gameObj,Basket& bskObj, Water& waterObj);
        void updateBskHeightAsPerWaterLevel(Basket& bskObj,Water& waterObj);
        void objectFreeFallLogic(Objects(&obj)[OBJECT_ARRAY_SIZE],Game& gameObj);
        void genearateRandomObjects(Game & gameObj);//call it periodically not always
        void checkifCaughtMiss(Objects(&obj)[OBJECT_ARRAY_SIZE],Basket& bskObj,Game& gameObj,Water& waterObj,SemaphoreHandle_t &musicHandle);
        void upgradeGameLevel(InputHandler& ipObj, Basket& bskObj, Game& gameObj, Water& waterObj,SemaphoreHandle_t &musicHandle);
        void resetGameToDefault(InputHandler& ipObj,Basket& bskObj,Water& waterObj,Game& gameObj);
        void makeGameOver(Game& gameObj);
        void objCaught(Objects(&obj),Basket& bskObj,Game& gameObj,Water& waterObj,SemaphoreHandle_t &musicHandle);
        void objMiss(Objects &obj,Basket &bskObj,Game &gameObj,Water &waterObj);
        void objectFormation(Game & gameObj,Objects &obj_temp);
        void changeNature(Game &gameObj);

    public:
        void  hit_sound_level(SemaphoreHandle_t &musicHandle);
        void fire_sound_level(SemaphoreHandle_t &musicHandle);
        int playSoundTrack;//1:CatchSound|2:Miss Sound|3:LevelUpgrade
        Objects objArr[OBJECT_ARRAY_SIZE];//Array to hold Eggs::Multiple Eggs
        LogicHandler();
        void callLogicManager(InputHandler& ipObj, Basket& bskObj, Game& gameObj, Water& waterObj,Objects(&obj)[OBJECT_ARRAY_SIZE],SemaphoreHandle_t &musicHandle);
        bool objCatch,objMissed,levelUpgraded,displayLevelUpgrade;
        virtual ~LogicHandler();
};

#endif /* LOGICHANDLER_H_ */
