/*
 * button.c
 *
 * Created: 9/21/2021 2:33:29 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "button.h"
#include <util/delay.h>



void Button_listen(Button *btn)
{
	switch(btn->current_state)
	{
		case NOT_PRESSED:
		
		if(GPIO_read_pin(btn->port , btn->pin) == btn->sense)
			{btn->current_state = MAYBE_PRESSED;}
			
		break;
		
		case MAYBE_PRESSED:
		
		if(GPIO_read_pin(btn->port , btn->pin) == btn->sense)
			{
				btn->current_state = NOT_RELEASED;
				if(btn->evt == ON_KEY_DOWN)
					{
						btn->callback();
					}
			}
		
		else {btn->current_state = NOT_PRESSED;}
		
		break;
		
		case NOT_RELEASED:
				if(GPIO_read_pin(btn->port , btn->pin) == btn->sense)
				{
					if(btn->evt == ON_KEY_PRESSED)
					{
						btn->callback();
					}
					_delay_ms(COOL_DOWN_MS);
				}
				
				else {btn->current_state = MAYBE_RELEASED;}
		break;
		case MAYBE_RELEASED:
				if(GPIO_read_pin(btn->port , btn->pin) != btn->sense)
				{
					btn->current_state = NOT_PRESSED;
					if(btn->evt == ON_KEY_UP)
					{
						btn->callback();
					}
				}
		
				else {btn->current_state = NOT_RELEASED;}
		break;
								
	}
}

void Button_config(Button *btn , GPIO_port_name_t port_name , uint8 pin, Button_event btn_event , void (*btn_callback)(void) , Button_Sense sense)
{
	GPIO_init_pin(port_name , pin , GPIO_PIN_INPUT);
	btn->callback = btn_callback;
	btn->evt = btn_event;
	btn->port = port_name;
	btn->pin = pin;
	btn->current_state = NOT_PRESSED;
	btn->sense = sense;
}