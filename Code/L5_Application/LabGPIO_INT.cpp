/*
 * LabGPIO_INT.cpp
 *
 *  Created on: 16-Sep-2018
 *  Author: Kailash Chakravarty
 */


#include "LabGPIO_INT.hpp"
#include "LPC17xx.h"
#include "tasks.hpp"
#include "uart0_min.h"
#include "printf_lib.h"

#define PORTS    (2)
#define PINS     (32)

SemaphoreHandle_t sem_Internal_LED = NULL;
SemaphoreHandle_t sem_External_LED = NULL;
signed long xHigherPriorityTaskWoken;


void p0_0handler(void)
{
    u0_dbg_printf("isr p0.0\n");
    xSemaphoreGiveFromISR(sem_Internal_LED, &xHigherPriorityTaskWoken);
    LPC_GPIOINT->IO0IntClr |= (1 << 0); // clear interrupt source
}

void p2_6handler(void)
{
    u0_dbg_printf("isr p2.6\n");
    xSemaphoreGiveFromISR(sem_External_LED, &xHigherPriorityTaskWoken);
    LPC_GPIOINT->IO2IntClr |= (1 << 6); // clear interrupt source
}

void p2_7handler(void)
{
    u0_dbg_printf("isr p2.7");
    xSemaphoreGiveFromISR(sem_External_LED, &xHigherPriorityTaskWoken);
    LPC_GPIOINT->IO2IntClr |= (1 << 7); // clear interrupt source
}

void LabGpioInterrupts :: Initialize()
{
    uint8_t ii, jj;

    NVIC_EnableIRQ(EINT3_IRQn);

    for (ii = 0; ii < PORTS; ii++)
    {
        for (jj = 0; jj < PINS; jj++)
        {
            pin_isr_map[ii][jj] = NULL;
        }
    }
}


bool LabGpioInterrupts :: AttachInterruptHandler(uint8_t port,
                                                 uint32_t pin,
                                                 IsrPtr pin_isr,
                                                 EDGE condition)
{
    if (((port != 0) && (port != 2)) || // Error pre-checks
          (pin > 31)                 ||
          (pin_isr == NULL)          ||
          (condition > 2))
    {
        return(false);
    }
    else
    {
        port = ((port == 2) ? 1 : port); // mapping actual port number to array index.

        pin_isr_map[port][pin] = pin_isr;

        if (condition == Rising)
        {
            if (port == 0)
            {
                LPC_GPIOINT->IO0IntEnR |= (1<<pin);
            }
            else
            {
                LPC_GPIOINT->IO2IntEnR |= (1<<pin);
            }
        }
        else if (condition == Falling)
        {
            if (port == 0)
            {
                LPC_GPIOINT->IO0IntEnF |= (1<<pin);
            }
            else
            {
                LPC_GPIOINT->IO2IntEnF |= (1<<pin);
            }
        }
        else // (condition == both edges)
        {
            if (port == 0)
            {
                LPC_GPIOINT->IO0IntEnF |= (1<<pin);
                LPC_GPIOINT->IO0IntEnR |= (1<<pin);
            }
            else
            {
                LPC_GPIOINT->IO2IntEnF |= (1<<pin);
                LPC_GPIOINT->IO2IntEnR |= (1<<pin);
            }
        }
        return(true);
    }
}

void LabGpioInterrupts :: HandleInterrupt()
{
    uint8_t  ii;

    // Read status registers for port 0 and port 2 to find out which port pin press
    // triggered the interrupt
    for (ii = 0; ii < PINS; ii++)
    {
        if (LPC_GPIOINT->IO0IntStatR & (1 << ii))
        {
            pin_isr_map[0][ii]();
        }


        if (LPC_GPIOINT->IO0IntStatF & (1 << ii))
        {
            pin_isr_map[0][ii]();
        }


        if (LPC_GPIOINT->IO2IntStatR & (1 << ii))
        {
            pin_isr_map[1][ii]();
        }


        if (LPC_GPIOINT->IO2IntStatF & (1 << ii))
        {
            pin_isr_map[1][ii]();
        }
    }
}
