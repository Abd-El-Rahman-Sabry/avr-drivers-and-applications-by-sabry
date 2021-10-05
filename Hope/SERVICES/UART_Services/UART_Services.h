/*
 * UART_Services.h
 *
 * Created: 9/23/2021 5:23:19 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "../../MCAL/UART/UART.h"

#define RX_ASYNC_BUFFER_SIZE 20

void serialWrite(const sint8 *str);
void serialRead(sint8 *str);
void serialWrite_SUM(const sint8 *str);
uint8 serialRead_SUM( sint8 *str);
void serialWrite_async(const sint8 *str);
uint8 serialRead_async(sint8 *str);
uint8 asyncRxCompleteFlag();
void setRxBufferSize(uint8 size);
#endif /* UART_SERVICES_H_ */