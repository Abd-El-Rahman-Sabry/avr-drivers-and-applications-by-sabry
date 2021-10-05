/*
 * UART.h
 *
 * Created: 9/21/2021 12:27:18 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef UART_H_
#define UART_H_

#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"
#include "UART_config.h"

#define BAUD_CALC ( CPU_F/SPEED_MODE/BAUD_RATE - 1 )
#define UART_DATA_RECEIVED 1
#define UART_NO_DATA_RECEIVED 0


void	UART_init();
void	UART_send_byte(uint8 data);
uint8	UART_receive_byte();


void	UART_send_byte_NOBLOCK(uint8 data);
uint8	UART_receive_byte_NOBLOCK(uint8 *pdata); 

void	UART_rx_interrupt_enable();
void	UART_rx_interrupt_disable();


void	UART_tx_interrupt_enable();
void	UART_tx_interrupt_disable();

void	UART_tx_set_callback(void (*txCallback)(void));
void	UART_rx_set_callback(void (*rxCallback)(void));


uint8 UART_receive_byte_direct(void);
void UART_send_byte_direct(uint8 data);
#endif /* UART_H_ */