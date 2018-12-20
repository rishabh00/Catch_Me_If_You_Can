/*
 * DisplayHandler.h
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#ifndef DISPLAYHANDLER_H_
#define DISPLAYHANDLER_H_
#include "Water.h"
#include "Basket.h"
#include "Objects.h"
#include "RGBmatrixPanel.h"
#include "Bitmaps.hpp"
#include "LogicHandler.h"
#define LVL  0
#include "CONSTANTS.hpp"

//BITSETS of Objects
const uint8_t egg[] = {
        0x60,
        0xf0,
        0xf0,
        0xf0,
        0x60
};

class DisplayHandler {
public:
    DisplayHandler();
    void callDisplayManager(Water& waterObj,Basket& bskObj,LogicHandler &lhObj,Game& gameObj,RGBmatrixPanel& matrix);
    void displayWater(Water& waterObj,RGBmatrixPanel& matrix);
    void displayBasket(Basket& bskObj,RGBmatrixPanel& matrix);
    void displayObject(Objects (&obj)[OBJECT_ARRAY_SIZE],Game& gameObj,RGBmatrixPanel& matrix);
    void refreshScreen(RGBmatrixPanel& matrix);
    void drawegg(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b,RGBmatrixPanel& matrix);
    void draweggoutlet(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b,RGBmatrixPanel& matrix);
    void draweggbasket(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b,RGBmatrixPanel& matrix);
    void drawWaterMarker(int16_t x, int16_t y,RGBmatrixPanel& matrix);

    void scr_welcome(RGBmatrixPanel& matrix);
    void scr_corners_borders(RGBmatrixPanel& matrix);
    void string_print(const uint8_t *bm, int16_t x, int16_t y, uint8_t strlen,RGBmatrixPanel& matrix);
    void scr_start(RGBmatrixPanel& matrix);
    void scr_lvl_countdown(uint8_t mode, uint8_t lvl_cntdwn,RGBmatrixPanel& matrix);
    void scr_over(RGBmatrixPanel& matrix);
    void scr_you_win(RGBmatrixPanel& matrix);
    void catch_4_eggs(RGBmatrixPanel& matrix);
    void avoid_red_egg(RGBmatrixPanel& matrix);
    void play_pause_end(RGBmatrixPanel& matrix);


    virtual ~DisplayHandler();
};

#endif /* DISPLAYHANDLER_H_ */
