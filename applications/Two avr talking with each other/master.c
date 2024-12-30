/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include "SERVICES/UART_Services/UART_Services.h"
#include "MCAL/UART/UART.h"
#include "util/delay.h"
#include "HAL/LCD/LCD.h"


int main(void)
{
	LCD_Init();
	UART_init();
	GPIO_init_pin(GPIO_D , PIN_0 , GPIO_PIN_INPUT);
	GPIO_init_pin(GPIO_D , PIN_1 , GPIO_PIN_OUTPUT);
	sint8 data[20];
	uint8 status;
	while(1)
	{
		serialRead(data);
		serialWrite_SUM(data);
	}
}