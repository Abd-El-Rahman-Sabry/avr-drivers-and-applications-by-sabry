/*
 * GPIO.c
 *
 * Created: 9/10/2021 4:42:03 PM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "GPIO.h"

volatile  uint8 *direction_regisers[MAX_PORT +1] = {
	&DDRA,
	&DDRB,
	&DDRC,
	&DDRD
};

volatile uint8 *input_registers[MAX_PORT + 1] = {
	&PINA,
	&PINB,
	&PINC,
	&PIND
};

volatile uint8 *output_registers[MAX_PORT +1] = {
	&PORTA,
	&PORTB,
	&PORTC,
	&PORTD
};

GPIO_state_t GPIO_init_pin(GPIO_port_name_t reg , uint8 pin , uint8 dir){
	GPIO_state_t state = SUCCESS;
	if( NOT_VALID_PORT(reg) || NOT_VALID_PIN(pin) || NOT_VALID_DIR(dir) )
	{
		state = FAIL;
	}
	else
	{
		WRITE_BIT( (*(direction_regisers[reg])) , pin , dir);	
	}
	return state;
}
void GPIO_init_port(GPIO_port_name_t reg , uint8 dir){
	
	if(NOT_VALID_PORT(reg)){
		return;
	}
	else {
		WRITE_PORT((*(direction_regisers[reg])), dir);
	}
	
}
void GPIO_init_port_set_mask(GPIO_port_name_t reg , uint8 mask){
	if( NOT_VALID_PORT(reg) )
	{
		return;
	}
	else 
	{
		PORT_SET_MASK((*(direction_regisers[reg])),mask);
	}
}
void GPIO_init_port_clear_mask(GPIO_port_name_t reg , uint8 mask){
		if( NOT_VALID_PORT(reg) )
		{
			return;
		}
		else
		{
			PORT_CLEAR_MASK((*(direction_regisers[reg])),mask);
		}
}

//write functions

GPIO_state_t GPIO_write_pin(GPIO_port_name_t reg , uint8 pin , uint8 data)
{
		GPIO_state_t state = SUCCESS;
		if( NOT_VALID_PORT(reg) || NOT_VALID_PIN(pin) )
		{
			state = FAIL;
		}
		else
		{
			WRITE_BIT( (*(output_registers[reg])) , pin , data);
		}
		return state;
}

GPIO_state_t GPIO_toggle_pin(GPIO_port_name_t reg , uint8 pin )
{
	GPIO_state_t state = SUCCESS;
	if( NOT_VALID_PORT(reg) || NOT_VALID_PIN(pin) )
	{
		state = FAIL;
	}
	else
	{
		TOGGLE_BIT( (*(output_registers[reg])) , pin);
	}
	return state;
}

void GPIO_write_port(GPIO_port_name_t reg , uint8 data)
{
	if(NOT_VALID_PORT(reg))
	{
		return ;
	}
	WRITE_PORT((*(output_registers[reg])) , data);
}
void GPIO_port_set_mask(GPIO_port_name_t reg , uint8 mask){
	if(NOT_VALID_PORT(reg))
	{
		return;
	}
	else 
	{
		PORT_SET_MASK((*(output_registers[reg])) , mask);	
	}
}
void GPIO_port_clear_mask(GPIO_port_name_t reg , uint8 mask){
		if(NOT_VALID_PORT(reg))
		{
			return;
		}
		else
		{
			PORT_CLEAR_MASK((*(output_registers[reg])) , mask);
		}
}
//read functions

uint8 GPIO_read_pin(GPIO_port_name_t reg , uint8 pin){
	if( NOT_VALID_PORT(reg) || NOT_VALID_PIN (pin))
	{
		return NOT_VALID_PIN_CODE;	
	}
	else 
	{
		return GET_BIT( (*(input_registers[reg])) , pin);
	}
}
uint8 GPIO_read_port(GPIO_port_name_t reg)
{
	if(NOT_VALID_PORT(reg))
	{
		return 255;
	}
	else
	{
		return ((*(input_registers[reg])));
	}
}

//PULL up and PULL down internal resistors

GPIO_state_t GPIO_enable_pull_up_res(GPIO_port_name_t reg , uint8 pin)
{
	GPIO_state_t state = SUCCESS;
	if( NOT_VALID_PORT(reg)){
		state = FAIL;
	}
	else if ( PIN_IS_OUTPUT((*(direction_regisers[reg])), pin) )
	{
		state = FAIL;
	}	
	else
	{
		SET_BIT(  (*(output_registers[reg])) ,pin);	
	}
	return state;
}
GPIO_state_t GPIO_disable_pull_up_res(GPIO_port_name_t reg , uint8 pin)
{
		GPIO_state_t state = SUCCESS;
		if( NOT_VALID_PORT(reg)){
			state = FAIL;
		}
		else if ( PIN_IS_OUTPUT((*(direction_regisers[reg])), pin) )
		{
			state = FAIL;
		}
		else
		{
			CLEAR_BIT(  (*(output_registers[reg])) ,pin);
		}
		return state;
}

void GPIO_disable_all_pull_up_res()
{
	SET_BIT(SFIOR , PUD);
}
void GPIO_enable_all_pull_up_res()
{
	CLEAR_BIT(SFIOR , PUD);
}