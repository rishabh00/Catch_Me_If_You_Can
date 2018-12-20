/*
 * Objects.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#include <Objects.h>

//This Constructor is used only when initializing array of Objects/Eggs| Used other constructot
Objects::Objects()
{
    isAlive=false;
    natureChanged=true;
}

Objects::~Objects()
{
    // TODO Auto-generated destructor stub
}

Objects::Objects(bool validObjs)
{
    isAlive=true;
    natureChanged=false;
    x= xArray[rand()%EGG_X_POS_ARR_SIZE];//Assigns Random X position to Eggs from Array

    y=BOARDWIDTH_Y-1;//Objects should Fall from Top of Matrix Board ;hence y=31;

    r=0;
    g=0;
    b=0;


    speed=EGG_SPEED_SLOW;       //Speed :: 1X|2X|3X

    //Assign Randomly any EggPower Between value 1-3
    magicalPow=(rand()%3)+1;  //Power :: 1-WHITE_EGGS|2-YELLOW_EGGS Player|3-RED_EGGS
    //prevX=x;

}
