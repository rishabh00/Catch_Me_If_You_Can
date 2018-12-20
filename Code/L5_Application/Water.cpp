/*
 * Water.cpp
 *
 *  Created on: 12-Nov-2018
 *      Author: scsap
 */

#include <Water.h>

Water::Water(Game& gameObj)
{
    initState(gameObj);
}

Water::~Water()
{
    // TODO Auto-generated destructor stub
}

void Water::initState(Game& gameObj)
{
    waterLevel=0;
    waterThreshold=1;
    r=0;
    g=7;
    b=7;

}
