/*
 * Objects.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef OBJECTS_H_
#define OBJECTS_H_
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "CONSTANTS.hpp"
class Objects {
public:


    bool isAlive;// True::EGG alive|False:: EGG Dead
bool natureChanged;
    int16_t x;
    int16_t y;

    uint8_t r;
    uint8_t g;
    uint8_t b;

    uint8_t xArray[EGG_X_POS_ARR_SIZE]={26,18,10,2};//EGGS are allowed to be fall from positions defined in this Array

    //Properties of EGG
    int8_t speed;       //Speed :: 1X|2X|3X
    int8_t magicalPow;  //Power :: 1|2-Evil_destroy Player|3-Good
    Objects();
    Objects(bool validObjs);







    virtual ~Objects();
};

#endif /* OBJECTS_H_ */
