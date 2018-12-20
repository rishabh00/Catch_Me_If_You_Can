/*
 * DisplayHandler.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#include <DisplayHandler.h>

DisplayHandler::DisplayHandler()
{
    // TODO Auto-generated constructor stub

}

void DisplayHandler::displayWater(Water& waterObj,RGBmatrixPanel& matrix)
{
    for (int i=0;i<=waterObj.waterLevel;i++){
        matrix.drawLine(0,i,32,i,matrix.Color333(7,7,7));
    }

}

void DisplayHandler::displayBasket(Basket& bskObj,RGBmatrixPanel& matrix)
{


    matrix.drawLine((bskObj.x-bskObj.offsetFrmCenter),bskObj.y,(bskObj.x+bskObj.offsetFrmCenter),bskObj.y,matrix.Color333(bskObj.r,bskObj.g,bskObj.b));

    matrix.drawPixel(bskObj.x+bskObj.offsetFrmCenter,bskObj.y+1,matrix.Color333(bskObj.r,bskObj.g,bskObj.b));
    matrix.drawPixel(bskObj.x-bskObj.offsetFrmCenter,bskObj.y+1,matrix.Color333(bskObj.r,bskObj.g,bskObj.b));


    matrix.drawPixel(bskObj.x+bskObj.offsetFrmCenter,bskObj.y+2,matrix.Color333(bskObj.r,bskObj.g,bskObj.b));
    matrix.drawPixel(bskObj.x-bskObj.offsetFrmCenter,bskObj.y+2,matrix.Color333(bskObj.r,bskObj.g,bskObj.b));



}

void DisplayHandler::displayObject(Objects (&obj)[OBJECT_ARRAY_SIZE],Game& gameObj,RGBmatrixPanel& matrix)
{

    for(int8_t i=0;i<OBJECT_ARRAY_SIZE;i++){
        if(obj[i].isAlive){//IfObject is Alive Then Display it

            drawegg(obj[i].x,obj[i].y,obj[i].r,obj[i].g,obj[i].b,matrix);

        }
    }

}

void DisplayHandler::refreshScreen(RGBmatrixPanel& matrix)
{
    matrix.fillScreen(0);
}

void DisplayHandler::drawegg(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b,RGBmatrixPanel& matrix)
{
    matrix.drawBitmap(x, y, egg, 4,5, matrix.Color333(r, g, b));
    // matrix.drawPixel(x,y,matrix.Color333(7, 0, 0));
}

void DisplayHandler::draweggoutlet(int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b,RGBmatrixPanel& matrix)
{

    matrix.fillRect(x,y,6,4,matrix.Color333(r, g, b));
}



//This Method Call All the DisplayFunctions
void DisplayHandler::callDisplayManager(Water& waterObj,Basket& bskObj,LogicHandler &lhObj,Game& gameObj,RGBmatrixPanel& matrix)
{
    refreshScreen(matrix);
    if(lhObj.levelUpgraded && lhObj.displayLevelUpgrade){
        switch(gameObj.level){
            case 1:
                scr_lvl_countdown(0,1,matrix);
                delay_ms(2000);
                lhObj.displayLevelUpgrade=false;

                break;
            case 2:
                scr_lvl_countdown(0,2,matrix);
                delay_ms(2000);
                lhObj.displayLevelUpgrade=false;

                break;
            case 3:
                scr_lvl_countdown(0,3,matrix);
                delay_ms(2000);
                lhObj.displayLevelUpgrade=false;

                break;


        }
    }



    displayWater(waterObj,matrix);
    displayBasket(bskObj,matrix);
    displayObject(lhObj.objArr,gameObj,matrix);

    draweggoutlet(25,28,0,7,0,matrix);
    draweggoutlet(17,28,0,7,0,matrix);
    draweggoutlet(9,28,0,7,0,matrix);
    draweggoutlet(1,28,0,7,0,matrix);

    drawWaterMarker(0,10,matrix);
    drawWaterMarker(31,10,matrix);

    matrix.swapBuffers(false);
}

void DisplayHandler::drawWaterMarker(int16_t x, int16_t y, RGBmatrixPanel& matrix)
{
    matrix.drawPixel(x,y,matrix.Color333(7,0,0));
}

void DisplayHandler::scr_start(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(start, 0,6, 5,matrix);
    string_print(game, 2,15,4,matrix);
    matrix.swapBuffers(false);
}

void DisplayHandler::scr_lvl_countdown(uint8_t mode, uint8_t lvl_cntdwn,RGBmatrixPanel& matrix)
{
    uint8_t offset = 0;

    scr_corners_borders(matrix);

    if (LVL == mode)
    {
        string_print(level, 0,6, 5,matrix);
    }
    else
    {
        offset = 5;
    }

    switch (lvl_cntdwn)
    {
        case 1:
            string_print(one, 12, (16-offset), 1,matrix);
            break;
        case 2:
            string_print(two, 12, (16-offset), 1,matrix);
            break;
        case 3:
            string_print(three, 12, (16-offset), 1,matrix);
            break;
        case 4:
            string_print(four, 12, (16-offset), 1,matrix);
            break;
    }

    matrix.swapBuffers(false);
}

void DisplayHandler::scr_over(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(game, 2,6, 4,matrix);
    string_print(over, 2,15,4,matrix);
    matrix.swapBuffers(false);
}

void DisplayHandler::scr_you_win(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(you, 6, 6, 3,matrix);
    string_print(win, 2, 15, 3,matrix);
    matrix.drawBitmap(31-(20+8), 31-(16+7), smiley, 8,9, matrix.Color333(7, 7, 0));
    matrix.swapBuffers(false);
}




void DisplayHandler:: scr_corners_borders(RGBmatrixPanel& matrix)
{
    matrix.fillScreen(0);
    matrix.drawPixel(0, 0, matrix.Color333(0,7,7)); //red
    matrix.drawPixel(0, 31, matrix.Color333(0,7,7)); //red
    matrix.drawPixel(31, 0, matrix.Color333(0,7,7)); //red
    matrix.drawPixel(31, 31, matrix.Color333(0,7,7)); //red
    matrix.drawLine(1, 0, 30, 0, matrix.Color333(7,0,0));
    matrix.drawLine(31, 1, 31, 30, matrix.Color333(7,0,0));
    matrix.drawLine(30, 31, 1, 31, matrix.Color333(7,0,0));
    matrix.drawLine(0, 30, 0, 1, matrix.Color333(7,0,0));
}

void DisplayHandler::string_print(const uint8_t *bm, int16_t x, int16_t y, uint8_t strlen,RGBmatrixPanel& matrix)
{
    uint8_t i = 0;

    while (strlen)
    {
        matrix.drawBitmap(31-(x+5), 31-(y+7), bm+i, 5,7, matrix.Color333(7, 7, 7));
        x += 6;
        i += 7;
        strlen--;
    }
}


void DisplayHandler::scr_welcome(RGBmatrixPanel& matrix)
{

    scr_corners_borders(matrix);
    string_print(catch_it, 0,6, 5,matrix);
    string_print(it, 4,15,4,matrix);
    matrix.swapBuffers(false);

}

void DisplayHandler::catch_4_eggs(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(catch_it, 0,6, 5,matrix);
    string_print(six, 2, 16, 1,matrix);
    matrix.drawBitmap(15, 9, egg, 4,5, matrix.Color333(7, 7, 7));
    matrix.swapBuffers(false);
}

void DisplayHandler::avoid_red_egg(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(avoid, 0,6, 5,matrix);
    matrix.drawBitmap(15, 9, egg, 4,5, matrix.Color333(7, 0, 0));
    matrix.swapBuffers(false);
}

void DisplayHandler::play_pause_end(RGBmatrixPanel& matrix)
{
    scr_corners_borders(matrix);
    string_print(press, 0, 1, 5,matrix);
    string_print(one, 0, 10, 1,matrix);
    matrix.drawPixel(31-7, 31-17, matrix.Color333(7, 7, 7));
    matrix.drawBitmap(31-(9+5), 31-(10+7), play, 5,7, matrix.Color333(0, 7, 0));
    string_print(slash, 15, 10, 1,matrix);
    matrix.drawBitmap(31-(21+5), 31-(10+7), pause, 5,7, matrix.Color333(7, 7, 0));
    string_print(two, 0, 21, 1,matrix);
    matrix.drawPixel(31-7, 31-12-16, matrix.Color333(7, 7, 7));
    matrix.drawBitmap(31-(9+5), 31-(21+7), repeat, 5,7, matrix.Color333(7, 0, 0));
    matrix.swapBuffers(false);
}



DisplayHandler::~DisplayHandler()
{
    // TODO Auto-generated destructor stub
}
