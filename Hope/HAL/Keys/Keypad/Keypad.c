/*
 * Keypad.c
 *
 * Created: 9/22/2021 11:01:14 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "Keypad.h"
#include "util/delay.h"

static uint8 key_codes[16] = {
	
						0b11101110 , 0b11011110 , 0b10111110 , 0b01111110, 
						0b11101101 , 0b11011101 , 0b10111101 , 0b01111101,
						0b11101011 , 0b11011011 , 0b10111011 , 0b01111011,
						0b11100111 , 0b11010111 , 0b10110111 , 0b01110111	
						
						};


static uint8 keys[16] = {
						'7' , '8' , '9' , '/',
						'4' , '5' , '6' , 'X',
						'1' , '2' , '3' , '-',
						'c' , '0' , '=' , '+'

};

static uint8 detect_row(Keypad *keypad , uint8 col)
{
	uint8 code ,mask;
	GPIO_init_port(keypad->port , 0xf0);
	GPIO_write_port(keypad->port , 0x0f);
	_delay_us(5);
	mask = (~(1<<(col)))&0xf0;
	GPIO_port_set_mask(keypad->port , mask) ;
	code = GPIO_read_port(keypad->port)&0x0f;
	if(code != 0x0f)
	{
		return mask|code;
	}

	return 0xff;
}
				
uint8 Keypad_listen(Keypad *keypad){
	uint8 key = 0xff;
	uint8 code = 'E';
	
	//Detect Key
	for(uint8 col = 4 ; col < 8 ; col++)
	{
		uint8 val = detect_row(keypad , col); 
		if(  val != 0xff)
		{
			key = val;
		}
	}

		
		for(uint8 i = 0 ; i <16 ; i++)
		{
			if(key == key_codes[i])
				{code = keys[i];break;}
		}
	switch(keypad->current_state)
	{
		
		case NOT_PRESSED:
			if(key != 0xff)
			{
				keypad->current_state = MAYBE_PRESSED;
			}
		break;
		
		case MAYBE_PRESSED:
				if(key != 0xff)
				{
					keypad->current_state = NOT_RELEASED;
					if(keypad->evt == ON_KEY_DOWN)
							keypad->callback(code);
					
				}
				else
					keypad->current_state = NOT_PRESSED;
		break;
			
		case NOT_RELEASED:
				if(key != 0xff)
				{
					if(keypad->evt == ON_KEY_PRESSED)
							{
								keypad->callback(code);
								_delay_ms(COOL_DOWN_MS);
							}
						
				}
				else 
					keypad->current_state = MAYBE_RELEASED;
		break;
		
		case MAYBE_RELEASED:
				if(key != 0xff)
				{
					keypad->current_state = NOT_PRESSED;
					if(keypad->evt == ON_KEY_UP)
							keypad->callback(code);
						
				}
				else 
					keypad->current_state = NOT_RELEASED;
		break;
	}
	
	
	for(uint8 i = 0 ; i <16 ; i++)
	{
		if(key == key_codes[i])
			return keys[i];
	}
	return 'Z';
}

void Keypad_config(Keypad *keypad , GPIO_port_name_t port ,Button_event evnt, void (*callback)(uint8))
{
	GPIO_init_port(keypad->port , 0xf0);
	GPIO_write_port(keypad->port , 0x0f);
	keypad->port = port;
	keypad->current_state = NOT_PRESSED;
	keypad->evt =  evnt;
	keypad->callback = callback;
}