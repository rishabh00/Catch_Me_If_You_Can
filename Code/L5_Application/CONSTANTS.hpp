
/*
 * Project Name: Catch Me If You Can
 * Group:2
 * File Defines All the Constants
 *
 * */

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_
#include "LabGPIO.hpp"

//Matrix Board Dimentions
const uint8_t boardLength_x=32;
const uint8_t boardWidth_y=32;

#define PI  3.14159265
#define BOARDLENGTH_X   32
#define BOARDWIDTH_Y    32
#define PI              3.14159265

#define EGG_X_POS_ARR_SIZE 4
#define EGG_SPEED_SLOW     1
#define EGG_SPEED_MEDIUM   2
#define EGG_SPEED_FAST     3
#define WHITE_EGGS         1
#define YELLOW_EGGS        2
#define RED_EGGS           3

#define BASKET_SIZE_DEFAULT      3
#define BASKET_SPEED             2
#define BASKET_SPEED_MAX         2

#define OBJECT_ARRAY_SIZE 15
#define CONSOLE_SENSITIVITY (30)
#define CONSOLE_TILT_RANGE (700)
#define LEVEL 1
#define MAX_GAME_LEVEL 3
#define MIN_OBJ_TO_PROGRESS 6
#define GAMEOVER 1
#define WIN 2
#define PLAYGAME 3
#define PAUSEGAME 4
#define REPLAY 5
#define ONLYREPLAY 6
#define ONLYPLAY_PAUSE 7
#define welcomeTune 3
//Frequencies used for Buzzer
const int hit[5] = {800,785,770,755,740};
const int fire[9]=
   {
           550,/*twice the freq of this and use always tempo as 40 */
           404,
           315,
           494,
           182,
           260,
           455,
           387,
           340
   };

//------------XXXXXXX---LED_Board Configurations---XXXXXXX------------


//------------XXXXXXX---LED_Board Configurations ENDS---XXXXXXX------------



#endif /* CONSTANTS_HPP_ */
