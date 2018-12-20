/*
 * InputHandler.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#include <InputHandler.h>

InputHandler::InputHandler(Basket& bskObj)
{
    init(bskObj);
}

void InputHandler::getBoardOrientation(Basket& bskObj)
{
    //left
    if ((x_coordiante>px_coordiante+CONSOLE_SENSITIVITY && x_coordiante<= CONSOLE_TILT_RANGE )){
        boardOrientation=left;
        bskObj.speed=BASKET_SPEED;
        px_coordiante=x_coordiante;
    }
    //right
    else if((x_coordiante<px_coordiante-CONSOLE_SENSITIVITY && x_coordiante>=-CONSOLE_TILT_RANGE)){
        boardOrientation=right;
        bskObj.speed=BASKET_SPEED;
        px_coordiante=x_coordiante;
    }
    else if(x_coordiante>CONSOLE_TILT_RANGE ){
        boardOrientation=left;
        bskObj.speed=BASKET_SPEED;
    }
    else if(x_coordiante<-CONSOLE_TILT_RANGE ){
        boardOrientation=right;
        bskObj.speed=BASKET_SPEED;
    }
    else{
        boardOrientation=invalid;
        py_coordiante=y_coordiante;
    }
}

void InputHandler::getInput(Basket& bskObj)
{
    //--------------INPUT LOGIC--------------------
    switch(boardOrientation){

        case right:
            dir=RIGHT;
            break;

        case left:
            dir=LEFT;
            break;

        case invalid:
        default:
            dir=STOP;
            break;

 //--------------INPUT LOGIC ENDS--------------------
    }
}

void InputHandler::callInputManager(Basket& bskObj)
{
    getBoardOrientation(bskObj);
    getInput(bskObj);
}

void InputHandler::init(Basket& bskObj)
{
    dir=STOP;
    boardOrientation=invalid;

    px_coordiante=0;
    py_coordiante=0;
    pz_coordiante=0;
    z_coordiante=0;
    x_coordiante=0;
    y_coordiante=0;
    isplayPausePressed=true;
    isExitButtonPressed=false;

}

InputHandler::~InputHandler()
{

}

