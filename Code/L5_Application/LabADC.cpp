/*
 * LabADC.cpp
 *
 *  Created on: 28-Sep-2018
 *      Author: Kailash Chakravarty
 */

#include "LPC17xx.h"
#include "tasks.hpp"
#include "uart0_min.h"
#include "printf_lib.h"
#include "LabADC.hpp"


void LabAdc :: AdcInitBurstMode()
{
    LPC_SC->PCONP |= (1 << 12);
    LPC_SC->PCLKSEL0 &= ~(3 << 24);
    LPC_ADC->ADCR |= ((3 << 8) | (1 << 16) | (1 << 21));
    LPC_ADC->ADCR &= ~(7 << 24);
}


void LabAdc :: AdcSelectPin(Pin pin)
{
    switch (pin)
    {
        case k0_25:
                LPC_PINCON->PINSEL1 &= ~(3 << 18); // ADC 0.2 channel
                LPC_PINCON->PINSEL1 |= (1 << 18);
                LPC_PINCON->PINMODE1 &= ~(3 << 18);
                LPC_PINCON->PINMODE1 |= (1 << 19);
                LPC_ADC->ADCR |= (1 << 2);
            break;

        case k0_26:
                LPC_PINCON->PINSEL1 &= ~(3 << 20); // ADC 0.3 channel
                LPC_PINCON->PINSEL1 |= (1 << 20);
                LPC_PINCON->PINMODE1 &= ~(3 << 20);
                LPC_PINCON->PINMODE1 |= (1 << 21);
                LPC_ADC->ADCR |= (1 << 3);
            break;

        case k1_30:
                LPC_PINCON->PINSEL3 |= (3 << 28); // ADC 0.4 channel
                LPC_PINCON->PINMODE3 &= ~(3 << 28);
                LPC_PINCON->PINMODE3 |= (1 << 29);
                LPC_ADC->ADCR |= (1 << 4);
            break;

        case k1_31:
                LPC_PINCON->PINSEL3 |= (3 << 30); // ADC 0.5 channel
                LPC_PINCON->PINMODE3 &= ~(3 << 30);
                LPC_PINCON->PINMODE3 |= (1 << 31);
                LPC_ADC->ADCR |= (1 << 5);
            break;

        default :
            break;

    }
}


float LabAdc :: ReadAdcVoltageByChannel(uint8_t channel, uint16_t* raw)
{
    float voltage;

    switch (channel)
    {
        case 2:
            *raw = ((LPC_ADC->ADDR2 >> 4) & 0xFFF);
            break;
        case 3:
            *raw = ((LPC_ADC->ADDR3 >> 4) & 0xFFF);
            break;
        case 4:
            *raw = ((LPC_ADC->ADDR4 >> 4) & 0xFFF);
            break;
        case 5:
            *raw = ((LPC_ADC->ADDR5 >> 4) & 0xFFF);
            break;
    }
    voltage = ((ADC_VREF / (1 << ADC_RESOLUTION)) * (*raw));
    return (voltage);
}


