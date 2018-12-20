/*
 * LabGPIO.cpp
 *
 *  Created on: 09-Sep-2018
 *      Author: Kartik Chakravarty
 */


#include "LabGPIO.hpp"
#include "uart0_min.h"
#include <stdio.h>

// Macro definitions
#define TRUE  (1)
#define FALSE (0)
#define PINSEL_SINGLE_REG_LIMIT   (15)
#define CONFIGURE_GPIO        (3)

// constructor to initialize objects for each gpio switch/LED
LabGPIO :: LabGPIO(uint8_t port, uint8_t pin, uint8_t dir)
{
    volatile uint32_t *pinsel_reg;

    portnum = port;
    pinnum  = pin;

    switch (port)
    {
        default:
        case 0:
            gpio_reg_ptr = LPC_GPIO0; //(LPC_GPIO_TypeDef*)LPC_GPIO0_BASE;
            pinsel_reg = ((pin <= PINSEL_SINGLE_REG_LIMIT) ?
                      (&(LPC_PINCON->PINSEL0)) :
                      (&(LPC_PINCON->PINSEL1)));
            break;

        case 1:
            gpio_reg_ptr = LPC_GPIO1; //(LPC_GPIO_TypeDef*)LPC_GPIO1_BASE;
            pinsel_reg = ((pin <= PINSEL_SINGLE_REG_LIMIT) ?
                      (&(LPC_PINCON->PINSEL2)) :
                      (&(LPC_PINCON->PINSEL3)));
            break;

        case 2:
            gpio_reg_ptr = LPC_GPIO2; //(LPC_GPIO_TypeDef*)LPC_GPIO2_BASE;
            pinsel_reg = &(LPC_PINCON->PINSEL4); // PORT 2 pins 16 :31 not used!
            break;
    }

    // configure the pin functionality as GPIO
    // 2 bits control functionality of each port pin hence pin number is multiplied by 2.
    *pinsel_reg &= ~(CONFIGURE_GPIO << (2 * ((pin <= PINSEL_SINGLE_REG_LIMIT) ? pin : (pin % 16))));

    (void)(dir ? this->setAsOutput() : this->setAsInput());
}

 //Destructor
LabGPIO :: ~LabGPIO()
{
    // Do nothing
}

void LabGPIO :: setAsInput()
{
    gpio_reg_ptr->FIODIR &= ~(1 << pinnum);
}

void LabGPIO :: setAsOutput()
{
    gpio_reg_ptr->FIODIR |= (1 << pinnum);
}

void LabGPIO :: setDirection(bool output)
{
    gpio_reg_ptr->FIODIR = ((output) ?
                            (gpio_reg_ptr->FIODIR | (1 << pinnum)) :
                            (gpio_reg_ptr->FIODIR &= ~(1 << pinnum)));
}

void LabGPIO :: setHigh()
{
    gpio_reg_ptr->FIOSET = (1 << pinnum);
}

void LabGPIO :: setLow()
{
    gpio_reg_ptr->FIOCLR = (1 << pinnum);
}

void LabGPIO :: set(bool high)
{
    if (high)
    {
        gpio_reg_ptr->FIOSET = (1 << pinnum);
    }
    else
    {
        gpio_reg_ptr->FIOCLR = (1 << pinnum);
    }
}

bool LabGPIO :: getLevel()
{
    if (gpio_reg_ptr->FIOPIN & (1 << pinnum))
    {
        return(TRUE);
    }
    else
    {
        return(FALSE);
    }
}




