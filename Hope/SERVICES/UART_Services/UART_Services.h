/*
 * UART_Services.h
 *
 * Created: 9/23/2021 5:23:19 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "../../MCAL/UART/UART.h"


void UART_send_string(const uint8 *str);
void UART_receive_string(uint8 *str);
void UART_send_string_SUM(const uint8 *str);
uint8 UART_receive_string_SUM( uint8 *str);


#endif /* UART_SERVICES_H_ */