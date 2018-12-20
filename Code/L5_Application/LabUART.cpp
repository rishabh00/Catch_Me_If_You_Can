/*
 * LabUART.cpp
 *
 *  Created on: 05-Oct-2018
 *      Author: Kailash Chakravarty
 */

#include "LabUART.hpp"

#define   RECEIVE_DATA_AVAILABLE   (0x04)

void LabUart :: Init(IRQn_Type uart_port_IRQn, uint8_t port)
{
    switch (port)
    {
        case 2:
            NVIC_EnableIRQ(uart_port_IRQn);
            LPC_SC->PCONP |= (1<<24);
            LPC_SC->PCLKSEL1 &= ~(3 << 16);
            LPC_SC->PCLKSEL1 |= (1 << 16);
            LPC_UART2->LCR |= (1<<7); // DLAB bit 1
            LPC_UART2->DLM = 0x02; // 9600 baud rate
            LPC_UART2->DLL = 0x71;
            LPC_UART2->LCR = 0x03 ; // DLAB bit 0, 8 bit data
            LPC_UART2->IER = 1;
            LPC_PINCON->PINSEL4 &= ~(0xf<<16);
            LPC_PINCON->PINSEL4 |= ((1<<17) | (1<<19));
            LPC_PINCON->PINMODE0 &= ~(3<<18);
            LPC_PINCON->PINMODE0 |= (1<<19);
            break;

        case 3:
            NVIC_EnableIRQ(uart_port_IRQn);
            LPC_SC->PCONP |= (1<<25);
            LPC_SC->PCLKSEL1 &= ~(3 << 18);
            LPC_SC->PCLKSEL1 |= (1 << 18);
            LPC_UART3->LCR |= (1<<7); // DLAB bit 1
            LPC_UART3->DLM = 0x02; // 9600 baud rate
            LPC_UART3->DLL = 0x71;
            LPC_UART3->LCR = 0x03 ; // DLAB bit 0, 8 bit data
            LPC_UART3->IER = 1;
            LPC_PINCON->PINSEL9 |= (0xf<<24);
            LPC_PINCON->PINMODE9 &= ~(3<<26);
            LPC_PINCON->PINMODE9 |= (1<<27);
            break;

        default :
            break;
    }

}


void LabUart :: Transmit(uint8_t data, uint8_t port)
{
    LPC_UART_TypeDef *uart_ptr;
    uart_ptr = (port == 2 ? LPC_UART2 : LPC_UART3);
    uart_ptr->THR = (uint8_t)data;
    while(! (uart_ptr->LSR & (1 << 6)));
}

void LabUart :: ReceiveHandler(QueueHandle_t& rxqueue, uint8_t port)
{
    uint8_t rxbyte;
    BaseType_t xHigherPriorityTaskWoken = 0;
    uint32_t IIRReg = 0;
    uint32_t LSRReg = 0;
    LPC_UART_TypeDef *uart_ptr;

    uart_ptr = (port == 2 ? LPC_UART2 : LPC_UART3);

    IIRReg = uart_ptr->IIR;

    if ((IIRReg & 0xe) == RECEIVE_DATA_AVAILABLE)
    {
        rxbyte = (uint8_t)uart_ptr->RBR;
        uart0_putchar(rxbyte);
        xQueueSendFromISR(rxqueue, &rxbyte, &xHigherPriorityTaskWoken);
    }

    LSRReg = uart_ptr->LSR; // Clear interrupt by reading LSR
}
