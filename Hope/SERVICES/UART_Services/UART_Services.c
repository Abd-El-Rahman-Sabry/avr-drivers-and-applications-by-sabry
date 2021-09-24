/*
 * UART_Services.c
 *
 * Created: 9/23/2021 5:23:35 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
/************	Synchoronous Functions	*************/

#include "UART_Services.h"

void UART_send_string(const uint8 *str)
{
	uint8 i = 0;
	while(str[i])
	{
		UART_send_byte(str[i]);
	}
}

void UART_receive_string(uint8 *str)
{
	uint8 i = 0;
	str[i] = UART_receive_byte();
	while(str[i] != '\t')
	{
		i++;
		str[i] = UART_receive_byte();
	}
	str[i] = 0;
}


void UART_send_string_SUM(const uint8 *str)
{
	uint8 lenght = 0;
	uint16 sum = 0;
	while (str[lenght])
	{
		sum+=str[lenght];
		lenght++;
	}
	UART_send_byte(lenght);
	UART_send_string(str);
	UART_send_byte((uint8)sum);
	UART_send_byte((uint8)(sum>>8));
}

uint8 UART_receive_string_SUM( uint8 *str)
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
