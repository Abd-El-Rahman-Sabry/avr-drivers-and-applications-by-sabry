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
#include "HAL/Keys/Keypad/Keypad.h"


void keypad_callback(uint8 key);


int main(void)
{
	LCD_Init();
	Keypad keypad;
	Keypad_config(&keypad , GPIO_A , ON_KEY_PRESSED , keypad_callback);
	while(1)
	{
		Keypad_listen(&keypad);
	}
}