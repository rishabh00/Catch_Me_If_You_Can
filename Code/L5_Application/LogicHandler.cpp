/*
 * LogicHandler.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#include <LogicHandler.h>


LogicHandler::LogicHandler()
{
    objCatch=false;
    objMissed=false;
    levelUpgraded=false;
    displayLevelUpgrade=false;
}

void LogicHandler::slideBasket(InputHandler& ipObj,Basket& bskObj,Game & gameObj)
{
    gameObj.level==1?bskObj.speed=2:bskObj.speed=2;
    switch(ipObj.dir){
        case LEFT:
            bskObj.x+=bskObj.speed;//gameObj.level+1;//bskObj.speed;
            ipObj.dir=STOP;
            break;

        case RIGHT:
            bskObj.x-=bskObj.speed;
            ipObj.dir=STOP;
            break;

        default:
            ipObj.dir=STOP;
            break;

    }


}

void LogicHandler::stopSlidingAtEdge(Basket& bskObj,Game & gameObj)
{

    //------Stop Movement when Basket Reaches Boarder--------------
    if((bskObj.x+bskObj.offsetFrmCenter)>gameObj.x-1){
        bskObj.x=gameObj.x-bskObj.offsetFrmCenter-1;
    }
    else if(bskObj.x-bskObj.offsetFrmCenter<0){
        bskObj.x=bskObj.offsetFrmCenter;
    }



}


void LogicHandler::updateBskHeightAsPerWaterLevel(Basket& bskObj,Water& waterObj)
{
    bskObj.y=waterObj.waterLevel+1;
}

void LogicHandler::objectFreeFallLogic(Objects(&obj)[OBJECT_ARRAY_SIZE],Game& gameObj)
{
    int delay=30-gameObj.level*10;
    for(int8_t i=0;i<OBJECT_ARRAY_SIZE;i++){
        if(obj[i].isAlive){

            obj[i].speed=1;
            //gameObj.level==1?obj[i].speed=1:obj[i].speed=1;

            obj[i].y-=obj[i].speed;
            vTaskDelay(delay);
        }
    }

}

void LogicHandler::genearateRandomObjects(Game & gameObj)
{

    if((gameObj.totalObj<1 || !(objArr[(gameObj.totalObj-1)%OBJECT_ARRAY_SIZE].isAlive))){
        Objects obj_temp(true);
        while(obj_temp.x==objArr[(gameObj.totalObj-1)%OBJECT_ARRAY_SIZE].x || obj_temp.magicalPow==objArr[(gameObj.totalObj-1)%OBJECT_ARRAY_SIZE].magicalPow ){
            obj_temp.x=obj_temp.xArray[rand()%EGG_X_POS_ARR_SIZE];
            obj_temp.magicalPow=(rand()%3)+1;
        }
        objectFormation(gameObj,obj_temp);
        objArr[(gameObj.totalObj++)%OBJECT_ARRAY_SIZE]=obj_temp;

    }

    else if(gameObj.level>=MAX_GAME_LEVEL && (gameObj.totalObj<1 || (objArr[(gameObj.totalObj-1)%OBJECT_ARRAY_SIZE].y< 20))){

        Objects multipleObj(true);
        while(multipleObj.x==objArr[(gameObj.totalObj-1)%OBJECT_ARRAY_SIZE].x){
            multipleObj.x=multipleObj.xArray[rand()%EGG_X_POS_ARR_SIZE];
        }

        objectFormation(gameObj,multipleObj);
        objArr[(gameObj.totalObj++)%OBJECT_ARRAY_SIZE]=multipleObj;


    }



}

void LogicHandler::checkifCaughtMiss(Objects (&obj)[OBJECT_ARRAY_SIZE],Basket& bskObj,Game& gameObj,Water& waterObj,SemaphoreHandle_t &musicHandle)
{

    for(int8_t i=0;i<OBJECT_ARRAY_SIZE;i++){
        if(obj[i].isAlive){
            if((obj[i].x+obj[i].speed) <= (bskObj.x+bskObj.offsetFrmCenter)
                    && (obj[i].x+obj[i].speed) >= (bskObj.x-bskObj.offsetFrmCenter)
                    && obj[i].y==bskObj.y)
            {
                //object Caught
                objCatch=true;
                objCaught(obj[i],bskObj,gameObj,waterObj,musicHandle);
            }

            else if(obj[i].y<waterObj.waterLevel){
                // Object Miss
                objMissed=true;
                objMiss(obj[i],bskObj,gameObj,waterObj);
                //waterObj.waterLevel++;
            }
        }

    }

}

void LogicHandler::resetGameToDefault(InputHandler& ipObj, Basket& bskObj,  Water& waterObj,Game& gameObj)
{
    ipObj.init(bskObj);
    bskObj.initState(gameObj,waterObj);
    waterObj.initState(gameObj);



}

void LogicHandler::makeGameOver(Game& gameObj)
{
    gameObj.isGameOver=true;
    gameObj.gameStatus=GAMEOVER;
}

void LogicHandler::checkIfGameOver(Game& gameObj, Basket& bskObj, Water& waterObj)
{
    if(waterObj.waterLevel>=10){
        makeGameOver(gameObj);
    }
}

void LogicHandler::objCaught(Objects (&obj), Basket& bskObj, Game& gameObj,Water& waterObj,SemaphoreHandle_t &musicHandle)
{

    obj.isAlive=false;//make the object dead;
    //change the Color of basket as per object caught
    bskObj.r=obj.r;
    bskObj.g=obj.g;
    bskObj.b=obj.b;
    objCatch=false;

    //check for Object's Magical Power
    switch(obj.magicalPow){
        case WHITE_EGGS:
            gameObj.score++;
            levelUpgraded=false;
            break;
        case YELLOW_EGGS:

            if(bskObj.offsetFrmCenter<10)
                bskObj.offsetFrmCenter++;
            gameObj.score++;
            levelUpgraded=false;
            break;
        case RED_EGGS://Evil Egg :: Game Over
            makeGameOver(gameObj);
            break;

    }

}

void LogicHandler::objMiss(Objects &obj, Basket& bskObj, Game& gameObj, Water& waterObj)
{

    obj.isAlive=false;
    objMissed=false;
    bskObj.r=7;
    bskObj.g=0;
    bskObj.b=7;
    bskObj.offsetFrmCenter=3;

    waterObj.r=rand()%7;
    waterObj.g=rand()%7;
    waterObj.b=rand()%7;

    //Increase the Water Level after 1 objects are sink ;
    if(gameObj.level>1){

        waterObj.waterLevel++;

    }

}

void LogicHandler::objectFormation(Game& gameObj,Objects &obj_temp)
{
    switch(obj_temp.magicalPow){

        case WHITE_EGGS:
            obj_temp.r=7;
            obj_temp.g=7;
            obj_temp.b=7;
            break;
        case YELLOW_EGGS:
            obj_temp.r=7;
            obj_temp.g=7;
            obj_temp.b=0;
            break;
        case RED_EGGS:
            obj_temp.r=7;
            obj_temp.g=0;
            obj_temp.b=0;
            break;

    }


}

void LogicHandler::hit_sound_level(SemaphoreHandle_t &musicHandle)
{
    playSoundTrack=1;
    xSemaphoreGive(musicHandle);
}


void LogicHandler::fire_sound_level(SemaphoreHandle_t &musicHandle)
{
    playSoundTrack=3;
    xSemaphoreGive(musicHandle);
}

void LogicHandler::changeNature(Game& gameObj)
{
    if(gameObj.level>=MAX_GAME_LEVEL)
        for(int i=0;i<OBJECT_ARRAY_SIZE;i++){
            if(objArr[i].isAlive && objArr[i].y<17 && !objArr[i].natureChanged){
                int8_t power=(rand()%3)+1;
                while(objArr[i].magicalPow==power){
                    power=(rand()%3)+1;
                }
                objArr[i].magicalPow=power;
                objectFormation(gameObj,objArr[i]);
                objArr[i].natureChanged=true;
            }

        }
}

LogicHandler::~LogicHandler()
{
    // TODO Auto-generated destructor stub
}

void LogicHandler::callLogicManager(InputHandler& ipObj, Basket& bskObj, Game& gameObj, Water& waterObj,Objects(&obj)[OBJECT_ARRAY_SIZE],SemaphoreHandle_t &musicHandle)
{

    slideBasket(ipObj,bskObj,gameObj);
    stopSlidingAtEdge(bskObj,gameObj);
    genearateRandomObjects(gameObj);
    objectFreeFallLogic(obj,gameObj);

    checkifCaughtMiss(obj,bskObj,gameObj,waterObj,musicHandle);
    checkIfGameOver(gameObj,bskObj,waterObj);
    updateBskHeightAsPerWaterLevel(bskObj,waterObj);//Not Fully Implemented :: waterLevelReducation Logic Remaining
    upgradeGameLevel(ipObj,  bskObj, gameObj,waterObj,musicHandle);
}

void LogicHandler::upgradeGameLevel(InputHandler& ipObj, Basket& bskObj, Game& gameObj, Water& waterObj,SemaphoreHandle_t &musicHandle)
{

    if(gameObj.score % MIN_OBJ_TO_PROGRESS == 0 && gameObj.score!=0 && !levelUpgraded){
        gameObj.level++;
        levelUpgraded=true;
        printf("LEVEL#: %i\n",gameObj.level);
        resetGameToDefault(ipObj,  bskObj, waterObj,gameObj);
        for(int8_t i=0;i<OBJECT_ARRAY_SIZE;i++){
            objArr[i].isAlive=false;
        }
        displayLevelUpgrade=true;

    }
    else if(gameObj.level==(MAX_GAME_LEVEL+1)){
        { // gameObj.isWin=true;
            gameObj.isGameOver=true;
            gameObj.gameStatus=WIN;

        }

    }
}
