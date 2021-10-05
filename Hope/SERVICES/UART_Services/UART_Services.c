/*
 * UART_Services.c
 *
 * Created: 9/23/2021 5:23:35 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
/************	Synchoronous Functions	*************/

#include "UART_Services.h"

static void rx_callback();
static void tx_callback();


static sint8 *async_tx_buffer;
static sint8 *async_rx_buffer;
static uint8 rx_async_flag = 0;
static uint8 rx_buffer_size;
//Synch
void serialWrite(const sint8 *str)
{
	uint8 i = 0;
	while(str[i])
	{
		UART_send_byte(str[i]);
		i++;
	}
}

void serialRead(sint8 *str)
{
	uint8 i = 0;
	str[i] = UART_receive_byte();
	while(str[i] != '\r')
	{
		i++;
		str[i] = UART_receive_byte();
	}
	str[i] = 0;
}
//Asynch

void serialWrite_async(const sint8 *str)
{
	async_tx_buffer = str;
	UART_tx_interrupt_enable();
	UART_tx_set_callback(tx_callback);
	UART_send_byte_direct(str[0]);
}


uint8 serialRead_async(sint8 *str)
{
	async_rx_buffer = str;
	UART_rx_interrupt_enable();
	UART_rx_set_callback(rx_callback);
}







static void tx_callback(){
	static uint8 i = 1;
	if( async_tx_buffer[i] != 0)
	{
		UART_send_byte_direct(async_tx_buffer[i]);
		i++;
	}
	else {
		i = 1;
		UART_tx_interrupt_disable();
	}
}

static void rx_callback()
{
	static uint8 i = 0;
	async_rx_buffer[i] = UART_receive_byte_direct();
	if(async_rx_buffer[i] == '\r')
	{
		rx_async_flag = 1;
		i = 0;
	}
	i++;	
}


uint8 asyncRxCompleteFlag()
{
	if(rx_async_flag)
	{
		rx_async_flag = 0;
		return 1;
	}
	return 0;
}




void serialWrite_SUM(const sint8 *str)
{
	uint8 lenght = 0;
	uint16 sum = 0;
	while (str[lenght])
	{
		sum+=str[lenght];
		lenght++;
	}
	UART_send_byte(lenght);
	serialWrite(str);
	UART_send_byte((uint8)sum);
	UART_send_byte((uint8)(sum>>8));
}

uint8 serialRead_SUM( sint8 *str)
{
	uint8 length , i =0;
	uint16 sum = 0 , sum_rece;
	
	length = UART_receive_byte();
	for(i = 0 ; i<length ; i++)
	{
		str[i] = UART_receive_byte();
		sum += str[i];
	}
	sum_rece = UART_receive_byte();
	sum_rece |= (UART_receive_byte()<<8);
	
	if(sum == sum_rece)
		return 1;
	return 0;
}


void setRxBufferSize(uint8 size)
{
	if(size <= 0)
		return;
	rx_buffer_size = size;
}