/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include "MCAL/INT/EXT_INT.h"
#include "MCAL/TIMER/TIMER0.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/ADC/ADC.h"
volatile int x = 105;
int main(void)
{
	//sei();
	LCD_Init();
	GPIO_init_pin(GPIO_A , PIN_5 , GPIO_PIN_INPUT);
	GPIO_enable_pull_up_res(GPIO_A , PIN_5);
	TIMER_Init(NORMAL , PRESCALER_8 );
	TIMER0_OV_interrupt_enable();
	LCD_write_string("5 + 6 = ??");
	ADC_init(Single_Ended_Input_On_Channel_1_ADC1 , ADC_prescaler_8 ,VrefAt_Internal_2560mV);
	ADC_set_auto_triggering(Free_Running_Mode);
    while (1) 
    {
		
		uint16 data = ADC_read();
		LCD_go_to(2 , 0);
		LCD_write_string("LOL ");
		LCD_write_number(data);
		LCD_clear_next_chars(1);
		_delay_ms(100);
    }
}

