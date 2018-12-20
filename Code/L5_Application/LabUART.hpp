/*
 * LabUART.hpp
 *
 *  Created on: 05-Oct-2018
 *      Author: Kailash Chakravarty
 */

#ifndef LABUART_HPP_
#define LABUART_HPP_

#include "LPC17xx.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "uart0_min.h"

class LabUart
{
 public:
    //LabUart();
    //~LabUart();

    void Init(IRQn_Type uart_port_IRQn, uint8_t port);
    void Transmit(uint8_t data, uint8_t port);
    void ReceiveHandler(QueueHandle_t& rxqueue, uint8_t port);

    // Optional: For the adventurous types, you may inherit from "CharDev" class
    // to get a lot of functionality for free
 private:

};



#endif /* LABUART_HPP_ */
