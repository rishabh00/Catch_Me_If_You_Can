/*
 * InputHandler.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "i2c2_device.hpp"
#include "Basket.h"
#include "Game.h"
#include "acceleration_sensor.hpp"
#include "wireless/wireless.h"

#define   AS    Acceleration_Sensor::getInstance()

enum eorientation{
    invalid=0,
    up,
    down,
    left,
    right
};

enum eDirections{
    STOP=0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class InputHandler {
    private:
        void getBoardOrientation(Basket& bskObj);
        void getInput(Basket& bskObj);


    public:
        int16_t x_coordiante,y_coordiante,z_coordiante,px_coordiante,py_coordiante,pz_coordiante,buttonPressed,pbuttonPressed;
        bool isplayPausePressed,isExitButtonPressed;
        eorientation boardOrientation;
        eDirections dir;

        InputHandler(Basket& bskObj);
        void callInputManager(Basket& bskObj);//Calls all the method
        void init(Basket& bskObj);
        virtual ~InputHandler();
};

#endif /* INPUTHANDLER_H_ */
