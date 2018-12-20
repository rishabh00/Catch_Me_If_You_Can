/*
 * Basket.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef BASKET_H_
#define BASKET_H_
#include <stdint.h>
#include <stdlib.h>
#include "Game.h"
#include "Water.h"
#include "CONSTANTS.hpp"
class Basket {
public:
    Basket(Game &gameObj,Water &waterObj);
    bool isBasketalive; //::true-basket visible | false-basket invisible
    //Position of Basket
    int16_t x;
    int16_t y;
    //properties of Basket
    int8_t offsetFrmCenter; // length of Basket= offset+....x....-offset
    int8_t speed; //Speed of Basket :: sensitivity |1X|2X|3X :: changes based on Input;
    //Basket Color
    uint8_t r;
    uint8_t g;
    uint8_t b;

    //Previous Position of Basket
    int8_t prevX;
    int8_t prevY;

    virtual ~Basket();
//private:
    void initState(Game &gameObj,Water &waterObj);
};

#endif /* BASKET_H_ */
