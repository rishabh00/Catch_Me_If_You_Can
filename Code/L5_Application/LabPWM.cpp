/*
 * LabPWM.cpp
 *
 *  Created on: 28-Sep-2018
 *      Author: Kailash Chakravarty
 */

#include"LabPWM.hpp"

#define CPUCLK     (96000000)
#define PWMCLK     (CPUCLK / 4)
#define PRESCALE   (24-1)
#define TC_TICK    (PWMCLK / (PRESCALE + 1))

void LabPwm :: PwmSelectAllPins(void)
{
    LPC_SC->PCONP |= (1 << 6);
    LPC_SC->PCLKSEL0 &= ~(3 << 12); // PWM CLOCK = 96/4 = 24MHZ
    // ********all pins ***********
    LPC_PINCON->PINSEL4 &= ~(3 << 0);
    LPC_PINCON->PINSEL4 |= (1 << 0);
    LPC_PINCON->PINMODE4 &= ~(3 << 0);
    LPC_PINCON->PINMODE4 |= (1 << 1);

    LPC_PINCON->PINSEL4 &= ~(3 << 2);
    LPC_PINCON->PINSEL4 |= (1 << 2);
    LPC_PINCON->PINMODE4 &= ~(3 << 2);
    LPC_PINCON->PINMODE4 |= (1 << 3);

    LPC_PINCON->PINSEL4 &= ~(3 << 4);
    LPC_PINCON->PINSEL4 |= (1 << 4);
    LPC_PINCON->PINMODE4 &= ~(3 << 4);
    LPC_PINCON->PINMODE4 |= (1 << 5);

    LPC_PINCON->PINSEL4 &= ~(3 << 6);
    LPC_PINCON->PINSEL4 |= (1 << 6);
    LPC_PINCON->PINMODE4 &= ~(3 << 6);
    LPC_PINCON->PINMODE4 |= (1 << 7);

    LPC_PINCON->PINSEL4 &= ~(3 << 8);
    LPC_PINCON->PINSEL4 |= (1 << 8);
    LPC_PINCON->PINMODE4 &= ~(3 << 8);
    LPC_PINCON->PINMODE4 |= (1 << 9);

    LPC_PINCON->PINSEL4 &= ~(3 << 10);
    LPC_PINCON->PINSEL4 |= (1 << 10);
    LPC_PINCON->PINMODE4 &= ~(3 << 10);
    LPC_PINCON->PINMODE4 |= (1 << 11);
    // ********************

}


void LabPwm :: PwmSelectPin(PWM_PIN pwm_pin_arg)
{
    LPC_SC->PCONP |= (1 << 6);
    LPC_SC->PCLKSEL0 &= ~(3 << 12); // PWM CLOCK = 96/4 = 24MHZ

    switch (pwm_pin_arg)
    {
        case k2_0:
            LPC_PINCON->PINSEL4 &= ~(3 << 0);
            LPC_PINCON->PINSEL4 |= (1 << 0);
            LPC_PINCON->PINMODE4 &= ~(3 << 0);
            LPC_PINCON->PINMODE4 |= (1 << 1);
            break;

        case k2_1:
            LPC_PINCON->PINSEL4 &= ~(3 << 2);
            LPC_PINCON->PINSEL4 |= (1 << 2);
            LPC_PINCON->PINMODE4 &= ~(3 << 2);
            LPC_PINCON->PINMODE4 |= (1 << 3);
            break;

        case k2_2:
            LPC_PINCON->PINSEL4 &= ~(3 << 4);
            LPC_PINCON->PINSEL4 |= (1 << 4);
            LPC_PINCON->PINMODE4 &= ~(3 << 4);
            LPC_PINCON->PINMODE4 |= (1 << 5);
            break;

        case k2_3:
            LPC_PINCON->PINSEL4 &= ~(3 << 6);
            LPC_PINCON->PINSEL4 |= (1 << 6);
            LPC_PINCON->PINMODE4 &= ~(3 << 6);
            LPC_PINCON->PINMODE4 |= (1 << 7);
            break;

        case k2_4:
            LPC_PINCON->PINSEL4 &= ~(3 << 8);
            LPC_PINCON->PINSEL4 |= (1 << 8);
            LPC_PINCON->PINMODE4 &= ~(3 << 8);
            LPC_PINCON->PINMODE4 |= (1 << 9);
            break;

        case k2_5:
            LPC_PINCON->PINSEL4 &= ~(3 << 10);
            LPC_PINCON->PINSEL4 |= (1 << 10);
            LPC_PINCON->PINMODE4 &= ~(3 << 10);
            LPC_PINCON->PINMODE4 |= (1 << 11);
            break;

        default:
            break;
    }

}


void LabPwm :: PwmInitSingleEdgeMode(uint32_t frequency_Hz)
{
    LPC_PWM1->PCR &= ~(127);
    LPC_PWM1->PR = PRESCALE;
    LPC_PWM1->MCR |= (1<<1);
    LPC_PWM1->MR0 = 0;
    LPC_PWM1->LER |= (1<<0);
    LPC_PWM1->PCR &= ~(1 << 9);
    LPC_PWM1->PCR &= ~(1 << 10);
    LPC_PWM1->PCR |= (1 << 11);
    LPC_PWM1->PCR |= (1 << 12);
    LPC_PWM1->PCR |= (1 << 13);
    LPC_PWM1->PCR |= (1 << 14);
    LPC_PWM1->TCR |= ((1<<0));
}
void LabPwm ::PwmEnableMode(bool mode)
{
	if( mode == true)
	{
		LPC_PWM1->PCR |= (1 << 10);
		LPC_PWM1->TCR |= (1<<3);
	}
	else
	{
		LPC_PWM1->TCR &=~(1<<3);
		LPC_PWM1->PCR &= ~(1 << 10);
	}

}


void LabPwm :: SetDutyCycle(PWM_PIN pwm_pin_arg, float duty_cycle_percentage)
{
    switch (pwm_pin_arg)
    {
        case k2_0:
            LPC_PWM1->MR1 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<1);
            break;

        case k2_1:
            LPC_PWM1->MR2 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<2);
            break;

        case k2_2:
            LPC_PWM1->MR3 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<3);
            break;

        case k2_3:
            LPC_PWM1->MR4 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<4);
            break;

        case k2_4:
            LPC_PWM1->MR5 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<5);
            break;

        case k2_5:
            LPC_PWM1->MR6 = ((LPC_PWM1->MR0 * duty_cycle_percentage) / 100);
            LPC_PWM1->LER |= (1<<6);
            break;

        default:
            break;
    }
}


void LabPwm :: SetFrequency(uint32_t frequency_Hz)
{
	if(frequency_Hz == 0)
	{
		frequency_Hz = 1;
	}

    LPC_PWM1->MR0 = (TC_TICK / frequency_Hz)/2;
    LPC_PWM1->LER |= (1<<0);

  // printf("frequency  %d \n",frequency_Hz);

}





