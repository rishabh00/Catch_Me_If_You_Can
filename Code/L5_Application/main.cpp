
/*
 * Project Name: Catch Me If You Can - Game logic
 * Group:2
 * Below is the DriverFile
 *
 * */

#include "tasks.hpp"
#include "examples/examples.hpp"
#include <stdint.h>
#include <stdio.h>
#include <time.h>

//Libraries Used for Project
#include "lpc_pwm.hpp"
#include "Adafruit_mfGFX.h"
#include "RGBmatrixPanel.h"
#include "lpc_rit.h"
#include "utilities.h"
#include "Water.h"
#include "Objects.h"
#include "Basket.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "LogicHandler.h"
#include "CONSTANTS.hpp"
#include "LabPWM.hpp"


//------------XXXXXXX---Global Objects ---XXXXXXX------------

SemaphoreHandle_t musicHandler,resetGameHandler,playPauseHandler,gameWinHandler;
LabPwm pwm;
Game myGame(boardLength_x,boardWidth_y);// Replace with CONSTANT
Water waterObj(myGame);
Objects obj;
Basket bskObj(myGame,waterObj);
InputHandler iphObj(bskObj);
DisplayHandler dspObj;
LogicHandler lhObj;
bool buttonDisabled=false;
//------------XXXXXXX---Global Objects ENDS---XXXXXXX------------

//PINCONFIG FOR RGB MATRIX BOARD

LabGPIO  P_addrA(0,0,1);     //ADDRA
LabGPIO  P_addrB(0,1,1);     //ADDRB
LabGPIO  P_addrC(2,6,1);     //ADDRC
LabGPIO  P_addrD(2,7,1);     //ADDRD
LabGPIO  P_LATCH(1,29,1);    //LATCH
LabGPIO  P_OE(1,28,1);       //OE
LabGPIO  P_CLOCK(1,19,1);    //CLOCK
LabGPIO  P_R1(1,22,1);       //R1
LabGPIO  P_G1(0,26,1);       //G1
LabGPIO  P_B1(1,23,1);       //B1
LabGPIO  P_R2(1,30,1);       //R2
LabGPIO  P_G2(1,31,1);       //G2
LabGPIO  P_B2(2,5,1);        //B2

RGBmatrixPanel matrix(true, 32);

// Initialize LED Matrix
void setup()
{
    //--------------------Initializing LED Board Settings:-----------------------------------
    P_addrA.setAsOutput();
    P_addrB.setAsOutput();
    P_addrC.setAsOutput();
    P_addrD.setAsOutput();
    P_LATCH.setAsOutput();
    P_OE.setAsOutput();
    P_CLOCK.setAsOutput();
    P_R1.setAsOutput();
    P_G1.setAsOutput();
    P_B1.setAsOutput();
    P_R2.setAsOutput();
    P_G2.setAsOutput();
    P_B2.setAsOutput();

    //--------------------Initializing LED Board Settings ENDS-----------------------------------
    matrix.begin();

}

// Function Rx acc_Coordinates from Nordic: |priority::4
void wirelessRx(void* p)
{
    while(1)
    {
        mesh_packet_t rcvPkt;

        if(wireless_get_rx_pkt(&rcvPkt, portMAX_DELAY)){

            iphObj.x_coordiante = (int16_t)(*((uint16_t*)(rcvPkt.data+0)));
            iphObj.y_coordiante = (int16_t)(*((uint16_t*)(rcvPkt.data+2)));
            iphObj.z_coordiante = (int16_t)(*((uint16_t*)(rcvPkt.data+4)));
            iphObj.buttonPressed= (int16_t)(*((uint16_t*)(rcvPkt.data+6)));
            if(iphObj.buttonPressed==1 ){
                xSemaphoreGive(playPauseHandler);
            }
            else if(iphObj.buttonPressed==2 ){

                xSemaphoreGive(resetGameHandler);
            }
        }
        vTaskDelay(50);

    }


}

// Function to display Start Screens
void displayStartScreen(){
    //PLAY SONG
    lhObj.playSoundTrack=welcomeTune;
    xSemaphoreGive(musicHandler);
    dspObj.scr_welcome(matrix);//Display Catch It!
    delay_ms(1500);
    dspObj.avoid_red_egg(matrix);
    delay_ms(1500);

    dspObj.catch_4_eggs(matrix);
    delay_ms(1500);

    dspObj.scr_start(matrix);// Display Start Game
    delay_ms(1500);

}
//On Button 2 Press
void resetGameTask(void *p){
    while(1){
        if(xSemaphoreTake(resetGameHandler,portMAX_DELAY)){
            if(!buttonDisabled && (myGame.gameStatus==PAUSEGAME || myGame.gameStatus==ONLYREPLAY) ){
                myGame.gameStatus=REPLAY;
            }
        }
    }
}
//On Button 1 Press
void pauseGame(void *p){
    while(1){
        if(xSemaphoreTake(playPauseHandler,portMAX_DELAY)){
            if(myGame.gameStatus==PLAYGAME && !myGame.isGameOver)
                myGame.gameStatus=PAUSEGAME;
            else if(!buttonDisabled && !myGame.isGameOver){
                myGame.gameStatus=PLAYGAME;
            }



        }

    }
}

void resetGame(){
    myGame.initState(BOARDLENGTH_X,BOARDWIDTH_Y,LEVEL,0);
    waterObj.initState(myGame);
    bskObj.initState(myGame,waterObj);
    iphObj.init(bskObj);
}


// Game Function: |priority::2
void gameBegin(void *p)
{
    setup();
    displayStartScreen();
    myGame.gameStatus=ONLYPLAY_PAUSE;//HomeScreen with only PlayPause
    while (1){
//STATES and SCREEN
        switch(myGame.gameStatus){

            case WIN:
                lhObj.playSoundTrack=welcomeTune;
                xSemaphoreGive(musicHandler);
                buttonDisabled=true;
                myGame.isGameOver=true;
                lhObj.playSoundTrack=welcomeTune;
                dspObj.scr_you_win(matrix);
                vTaskDelay(2000);
                myGame.gameStatus=ONLYREPLAY;//RePlay Game Only
                break;

            case GAMEOVER:
                lhObj.playSoundTrack=welcomeTune;
                xSemaphoreGive(musicHandler);
                buttonDisabled=true;
                myGame.isGameOver=true;
                lhObj.playSoundTrack=welcomeTune;
                dspObj.scr_over(matrix);
                vTaskDelay(1500);
                myGame.gameStatus=ONLYREPLAY;//RePlay Game Only
                break;

            case REPLAY:
                resetGame();
                buttonDisabled=true;
                myGame.isGameOver=false;
                dspObj.scr_start(matrix);// Display Start Game
                delay_ms(1500);
                dspObj.scr_lvl_countdown(1,3,matrix);
                delay_ms(1000);
                dspObj.scr_lvl_countdown(1,2,matrix);
                delay_ms(1000);
                dspObj.scr_lvl_countdown(1,1,matrix);
                delay_ms(1000);
                myGame.gameStatus=PLAYGAME;
                break;


            case PAUSEGAME:
                dspObj.play_pause_end(matrix);
                buttonDisabled=false;
                break;

            case ONLYREPLAY:
                myGame.isGameOver=true;
                dspObj.scr_corners_borders(matrix);
                dspObj.string_print(press, 0, 1, 5,matrix);
                dspObj.string_print(two, 0, 10, 1,matrix);
                matrix.drawPixel(31-7, 31-17, matrix.Color333(7, 7, 7));
                matrix.drawBitmap(31-(9+5), 31-(10+7), repeat, 5,7, matrix.Color333(7, 0, 0));
                matrix.swapBuffers(false);
                buttonDisabled=false;
                break;

            case ONLYPLAY_PAUSE:
                dspObj.scr_corners_borders(matrix);
                dspObj.string_print(press, 0, 1, 5,matrix);
                dspObj.string_print(one, 0, 10, 1,matrix);
                matrix.drawPixel(31-7, 31-17, matrix.Color333(7, 7, 7));
                matrix.drawBitmap(31-(9+5), 31-(10+7), play, 5,7, matrix.Color333(0, 7, 0));
                dspObj.string_print(slash, 15, 10, 1,matrix);
                matrix.drawBitmap(31-(21+5), 31-(10+7), pause, 5,7, matrix.Color333(7, 7, 0));
                matrix.swapBuffers(false);
                buttonDisabled=false;
                myGame.isGameOver=false;
                break;

            case PLAYGAME:
            default: //PLAYGAME
                buttonDisabled=false;
                if(!myGame.isGameOver){
                    iphObj.callInputManager(bskObj);
                    lhObj.callLogicManager(iphObj,bskObj,myGame,waterObj,lhObj.objArr,musicHandler);
                    dspObj.callDisplayManager(waterObj,bskObj, lhObj,myGame,matrix);
                    vTaskDelay(20);
                }
                break;
        }

    }
}
// Music Task::| PRIORITY:5::Blocked by Semaphore
void musicTask(void *p){
    pwm.PwmSelectPin(pwm.k2_1);
    pwm.PwmInitSingleEdgeMode(1);
    while(1){
        if( xSemaphoreTake(musicHandler,50)){

            while(--lhObj.playSoundTrack){
                for(int i = 0;i < 9;i++)
                {
                    uint8_t tempo = 40;
                    while(tempo)
                    {
                        //pwm.PwmEnableMode(true);
                        pwm.SetFrequency(fire[i]*2);
                        pwm.SetDutyCycle(pwm.k2_1,50);
                        pwm.PwmEnableMode(true);
                        tempo--;
                        delay_ms(5);
                    }
                }
            }
            while(++lhObj.playSoundTrack<=3){
                for(int i = 0;i < 8;i++)
                {
                    uint8_t tempo = 40;
                    while(tempo)
                    {
                        pwm.SetFrequency(hit[i]*2);
                        pwm.SetDutyCycle(pwm.k2_1,50);
                        pwm.PwmEnableMode(true);
                        tempo--;
                        delay_ms(5);
                    }
                }
            }

            pwm.PwmEnableMode(false);

        }
    }
}



int main(void)
{
    musicHandler=xSemaphoreCreateBinary();//Release this semaphore whenever you wish to play sound
    resetGameHandler=xSemaphoreCreateBinary();
    playPauseHandler=xSemaphoreCreateBinary();
    gameWinHandler=xSemaphoreCreateBinary();
    srand(time(NULL));
    wireless_init();
    wireless_service();

    xTaskCreate(musicTask,"unplugged",256,NULL,7,NULL);
    xTaskCreate(wirelessRx,"wirelessRx",256,NULL,6,NULL);
    xTaskCreate(resetGameTask,"GameReset",256,NULL,4,NULL);
    xTaskCreate(pauseGame,"PauseGame",256,NULL,3,NULL);
    xTaskCreate(gameBegin,"catchmeIfUcan",4096,NULL,2,NULL);


    scheduler_add_task(new wirelessTask(8));


    scheduler_start();
    return -1;
}
