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

uint8 op1[5] , sign , op2[5];
uint8 i = 0, j = 0 ;
uint8 next_flag = 0;
void keypad_callback(uint8 key)
{
	static uint8 pos  = 0;
	if(key == 'c')
	{
		LCD_clear();
		pos = 0;
		i = 0;
		j = 0;
	}
	else
	{
		if(next_flag)
		{
			LCD_clear();
			next_flag = 0;
		}
		LCD_write_char(key);
		if(key >= '0' && key <= '9' && pos == 0 )
		{

			op1[i] = key -'0';
			i++;
		}
		else if(key <= '/' && key>= '+' || key == 'X')
		{
			sign = key;
			pos = 2;
		}
		else if(key >= '0' && key <= '9' && pos == 2)
		{
			op2[j] = key - '0';
			j++;
		}
		 
		 if(key == '=' )
		{
			uint16 o1 = 0 , o2 = 0 , s = 1;
			
			for(uint8 x = i ; x > 0 ; x--)
			{
				o1 += op1[x-1]*s;
				s*=10;
			}
			s = 1;
			for(uint8 x = j ; x > 0 ; x--)
			{
				o2 += op2[x-1]*s;
				s*=10;
			}
			uint16 r ;
			switch(sign)
			{
				case '+':
					r = o1+o2;
					break;
				case '-':
					r = o1 - o2;
					break;
				case 'X':
					r = o1*o2;
					break;
				case '/':
					r = o1/o2;
					break;
			}
			LCD_go_to(2,0);
			LCD_write_number(r);
			next_flag = 1;
			pos = 0;
			i = 0 ;
			j = 0;
		}
	}
	
}



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