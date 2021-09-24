/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include "MCAL/INT/EXT_INT.h"
#include "MCAL/TIMER/TIMER.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/ADC/ADC.h"
#include "HAL/LM35/LM35.h"
#include "SERVICES/UART_Services/UART_Services.h"
#include "MCAL/UART/UART.h"



int main(void)
{
	int x = 0;
	UART_init();
	//GPIO_enable_pull_up_res(GPIO_A, PIN_2);
	LCD_Init();
	//Initialize LCD for debugging
	GPIO_init_pin(GPIO_D , PIN_0 , GPIO_PIN_INPUT);
	GPIO_init_pin(GPIO_D , PIN_1 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(GPIO_A , PIN_1 , GPIO_PIN_OUTPUT);
	LCD_write_string("RX ");
	uint8 str[100] = {0};
	while (1) 
    {
		UART_receive_string(str);
		LCD_go_to(0,0);
		LCD_write_string(str);
	}
}

