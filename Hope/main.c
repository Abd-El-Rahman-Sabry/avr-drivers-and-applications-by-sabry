/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include <util/delay.h>
#include "MCAL/INT/EXT_INT.h"

void isr(){
	GPIO_write_pin(GPIO_A , PIN_5 , HIGH);
	_delay_ms(500);
	GPIO_write_pin(GPIO_A , PIN_5 , LOW);
	_delay_ms(500);
}
int main(void)
{
	GPIO_init_pin(GPIO_A, PIN_5 ,GPIO_PIN_OUTPUT);
	GPIO_init_pin(GPIO_C, PIN_6 ,GPIO_PIN_OUTPUT);

	EXT_config_pin conf0 = {EXT_INT0 , EXT_logic_change_isc , isr};
	EXT_config_pin conf1 = {EXT_INT1 , EXT_falling_edge_isc , isr};
	EXT_config_pin conf2 = {EXT_INT2 , EXT_rising_edge_isc , isr};
	INT_error_t state0 = EXT_interrupt_init(&conf0);
	INT_error_t state1 = EXT_interrupt_init(&conf1);
	INT_error_t state2 = EXT_interrupt_init(&conf2);
	if(state2 == EXT_SUCCESS )
	{
		GPIO_write_pin(GPIO_C ,PIN_6 , HIGH);
	}
	GPIO_enable_pull_up_res(GPIO_D , PIN_2);
	GPIO_enable_pull_up_res(GPIO_D , PIN_3);
	GPIO_enable_pull_up_res(GPIO_B , PIN_2);

	sei();
    while (1) 
    {
		
		
    }
}

