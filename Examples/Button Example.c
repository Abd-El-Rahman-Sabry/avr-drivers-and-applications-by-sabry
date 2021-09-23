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
#include "HAL/Button/button.h"
#define F_CPU 1000000UL

uint16 x = 0;
uint16 y = 0;

void button_event(){
	x++;
}

int main(void)
{

	
	//GPIO_enable_pull_up_res(GPIO_A, PIN_2);
	
	//Initialize LCD for debugging
	LCD_Init();
	LCD_write_string("NOF CLICKS");
	Button button1,button2;
	
	Button_config(&button1 , GPIO_A , PIN_2 , ON_KEY_DOWN , button_event , Button_pull_up);
	Button_config(&button2 , GPIO_D , PIN_2 , ON_KEY_UP , button_event , Button_pull_down);
	
	while (1) 
    {
		Button_listen(&button1);
		Button_listen(&button2);
		LCD_go_to(2 , 0);	
		LCD_write_number(x);
	}
}

