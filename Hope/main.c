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
#include "HAL/LM35/LM35.h"

volatile int x = 105;
int main(void)
{
	//sei();
	LCD_Init();
	
	GPIO_init_pin(GPIO_A , PIN_2 , GPIO_PIN_INPUT);
	GPIO_init_pin(GPIO_A , PIN_6 , GPIO_PIN_INPUT);
	//GPIO_enable_pull_up_res(GPIO_A , PIN_2);
	TIMER_Init(NORMAL , PRESCALER_8 );
	LM53_Temp_Sensor_Init(Channel_6_ADC6);
	TIMER0_OV_interrupt_enable();
	LCD_write_string("Lm35 test :");
	ADC_init(Channel_2_ADC2,ADC_prescaler_128,Internal_2560mV);
	ADC_set_auto_triggering(Free_Running_Mode);
    while (1) 
    {
		
		LCD_go_to(2 , 0);
		LCD_write_string("value : ");
		LCD_write_number(LM35_Get_Temperature());
		LCD_write_string("oC");
		LCD_clear_next_chars(1);
		_delay_ms(100);
    }
}

