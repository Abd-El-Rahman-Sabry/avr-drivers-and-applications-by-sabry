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



uint16 temp;
uint8 critical_flag = LOW;



int main(void)
{
	//Initialize LCD for debugging
	LCD_Init();
	//Set input for the push button
	GPIO_init_pin(GPIO_B , PIN_1 , GPIO_PIN_INPUT);
	//set output for the LEDs and the buzzer 
	GPIO_init_port_set_mask(GPIO_D,0xf0);
	
	//Initialize the ADC
	ADC_init(Channel_2_ADC2,ADC_prescaler_128,Internal_2560mV);
	ADC_set_auto_triggering(Free_Running_Mode);
	
	//Initialize the sensor
	LM53_Temp_Sensor_Init(Channel_6_ADC6);
	
	
	
	LCD_write_string("Lm35 test :");
	//Initialize the timer to be used with PWM mode
	TIMER0_init(TIMER0_PHASE_CORRECTION_PWM,TIMER0_PRESCALER_1024,TIMER0_OCO_NON_INVERTING);

    while (1) 
    {
		
		LCD_go_to(2 , 0);
		LCD_write_string("temp : ");
		//Read Temperature
		temp = LM35_Get_Temperature();
		
		
		LCD_write_number(temp);
		LCD_write_string("oC");
		LCD_clear_next_chars(1);
		
		if(!critical_flag)
			if(temp < 20)
			{
				GPIO_write_port(GPIO_D , 1<<4);
				TIMER0_compare_reload(0);
			}
			else if(temp >= 20 && temp < 40)
			{
				GPIO_write_port(GPIO_D , 1<<5);
				TIMER0_compare_reload((temp - 20)*255/20);
			}
		
		
		
		if( temp >= 40 || critical_flag)
		{
			critical_flag = HIGH;
			/*
			3<<6
			00000011  
			<<<   
			11000000 
			*/
			GPIO_write_port(GPIO_D , 3<<6);	
		}
		
		
		if(GPIO_read_pin(GPIO_B , PIN_1) && temp < 40 )
		{
			critical_flag = LOW;
		}
	
	
	}
}

