/*
 * LabGPIO_INT.hpp
 *
 *  Created on: 16-Sep-2018
 *  Author: Kailash Chakravarty
 */

#ifndef LABGPIO_INT_HPP_
#define LABGPIO_INT_HPP_

#include "FreeRTOS.h"
#include "semphr.h"

/*****************************************************
         User defined data types
*****************************************************/
typedef enum
{
    Rising,
    Falling,
    Both
}EDGE;

typedef void (*IsrPtr)(void);

/*****************************************************
         Class declarations
******************************************************/

class LabGpioInterrupts
{
  public:
    /**
     * Optional: LabGpioInterrupts could be a singleton class, meaning, only one instance can exist at a time.
     * Look up how to implement this. It is best to not allocate memory in the constructor and leave complex
     * code to the Initialize() that you call in your main()
     */
    //LabGpioInterrupts();

    /**
     * This should configure NVIC to notice EINT3 IRQs; use NVIC_EnableIRQ()
     */
    void Initialize(void);

    /**
     * This handler should place a function pointer within the lookup table for the HandleInterrupt() to find.
     *
     * @param[in] port         specify the GPIO port, and 1st dimension of the lookup matrix
     * @param[in] pin          specify the GPIO pin to assign an ISR to, and 2nd dimension of the lookup matrix
     * @param[in] pin_isr      function to run when the interrupt event occurs
     * @param[in] condition    condition for the interrupt to occur on. RISING, FALLING or BOTH edges.
     * @return should return true if valid ports, pins, isrs were supplied and pin isr insertion was successful
     */
    bool AttachInterruptHandler(uint8_t port, uint32_t pin, IsrPtr pin_isr, EDGE condition);

    /**
     * This function is invoked by the CPU (through Eint3Handler) asynchronously when a Port/Pin
     * interrupt occurs. This function is where you will check the Port status, such as IO0IntStatF,
     * and then invoke the user's registered callback and find the entry in your lookup table.
     *
     * VERY IMPORTANT!
     *  - Be sure to clear the interrupt flag that caused this interrupt, or this function will be called
     *    repetitively and lock your system.
     *  - NOTE that your code needs to be able to handle two GPIO interrupts occurring at the same time.
     */
    void HandleInterrupt(void);

 private:
    /**
     * Allocate a lookup table matrix here of function pointers (avoid dynamic allocation)
     * Upon AttachInterruptHandler(), you will store the user's function callback
     * Upon the EINT3 interrupt, you will find out which callback to invoke based on Port/Pin status.
     */
    IsrPtr pin_isr_map[2][32];
};



extern SemaphoreHandle_t sem_Internal_LED;
extern SemaphoreHandle_t sem_External_LED;


extern void p0_0handler(void);
extern void p2_7handler(void);
extern void p2_6handler(void);

#endif /* LABGPIO_INT_HPP_ */
