/*
 * PwmManager.c
 *
 * Created: 10/4/2021 7:05:39 PM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "PwmManager.h"
#define STACK_SIZE 10
static SoftwarePwm_t *pins[STACK_SIZE];
static uint8 pointer = 0;
static uint8 initilaized = 0;
#define OV_value  200
#define PRESCALE 8
#define F_CPU 8000000UL


static SW_PWM_ERROR add_sw_pwm( SoftwarePwm_t *swp)
{
	if(pointer < STACK_SIZE)
	{
		pointer++;
		pins[pointer] = swp;
		return SWP_SUCCESS;
	}
	else if(swp->freq <= 0 || swp->freq > 800) 
	{
		return SWP_FREQ_ERROR;
	}
	else 
	{
		return SWP_STACK_FULL;
	}
}

static void pwm_func(){
	//LCD_write_string("Hello");
	uint8 i ;
	for(i = 0 ; i <= pointer ; i++)
	{
		
		
		uint32 condition = F_CPU / pins[i]->freq / OV_value / PRESCALE ;  
		
		if(pins[i]->counter ==  condition)
		{
			//LCD_string_at(1 , 0 , "Condition");
			GPIO_toggle_pin(pins[i]->port , pins[i]->pin);
			pins[i]->counter = 0;
		}
		
		
		if(pins[i]->counter == condition*pins[i]->duty/100)
		{
			//LCD_string_at(2 , 0 , "Duty");
			GPIO_toggle_pin(pins[i]->port ,pins[i]->pin);
		}
		
		
		pins[i]->counter++;
	
	
	
	
	}
}

void PWM_init()
{
	TIMER0_Init(CTC , SYNC_TMR_PRESCALER_8 , DISCONNECTED);
	TIMER0_CTC_interrupt_enable();
	TIMER0_set_OC(OV_value);
	TIMER0_CTC_set_callback(pwm_func);
	initilaized = 1;
}
 SW_PWM_ERROR SW_PWM_config(SoftwarePwm_t *swp , GPIO_port_name_t port , uint8 pin , uint16 freq , uint8 duty)
{


	if(!initilaized)
		PWM_init();
	swp->port = port ;
	swp->duty = duty;
	swp->freq = freq;
	swp->pin = pin;
	swp->counter = 0;	
	GPIO_init_pin(swp->port , swp->pin , GPIO_PIN_OUTPUT);
	SW_PWM_ERROR err = add_sw_pwm(swp);
	if(err!= SWP_SUCCESS)
	{
		/*
		if(err == SWP_STACK_FULL)
			{
				LCD_go_to(2,0);
				LCD_write_string("Stack");
			}
		else if(err == SWP_FREQ_ERROR)
		{
			
			LCD_go_to(2 , 0);
			LCD_write_string("Freq ");
				
		}*/
		return err;
	}
	/*
	LCD_go_to(1,5);
	LCD_write_string("NO error");
	*/
	GPIO_write_pin(swp->port , swp->pin, HIGH);
	return SWP_SUCCESS;

}
