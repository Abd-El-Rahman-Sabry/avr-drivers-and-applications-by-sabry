/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include "SERVICES/UART_Services/UART_Services.h"
#include "MCAL/UART/UART.h"
#include "MCAL/TIMER/TIMER1.h"
#define   F_CPU 8000000UL
#include "util/delay.h"
#include "HAL/LCD/LCD.h"
#include "HAL/Keys/Button/button.h"
#include "MCAL/TIMER/TIMER0.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/INT/EXT_INT.h"
#include "SERVICES/PwmMangement/PwmManager.h"
volatile uint8 flag = 10;
uint8 ton , toff; 
SoftwarePwm_t software_pwm;
void ext_int(){
	(software_pwm.duty)=(software_pwm.duty + 9)%100;	
}


int main(void)
{
	sei();
	LCD_Init();
	//PWM_init();
	SoftwarePwm_t software_pwm_2;
	SoftwarePwm_t software_pwm_3;

	SW_PWM_config(&software_pwm , GPIO_A , PIN_5 , 50 ,20);
	SW_PWM_config(&software_pwm_2 , GPIO_D , PIN_7 , 50 , 40);
	SW_PWM_config(&software_pwm_3 , GPIO_D , PIN_6 , 50 , 60);
	Button button ;
	Button_config(&button , GPIO_D , PIN_2 , ON_KEY_DOWN , ext_int , Button_pull_up);
	GPIO_init_pin(GPIO_D , PIN_2 , GPIO_PIN_INPUT);
	GPIO_enable_pull_up_res(GPIO_D , PIN_2);
	
	

	while(1)
	{
		Button_listen(&button);
	
		_delay_ms(2);
	}
}