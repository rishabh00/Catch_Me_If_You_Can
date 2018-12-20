/*
 * Water.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef WATER_H_
#define WATER_H_
#include "Game.h"
class Water {
public:

    Water(Game &gameObj);
    int8_t waterLevel;
    int8_t waterThreshold;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    virtual ~Water();
    void initState(Game &gameObj);
};

#endif /* WATER_H_ */
