/*
 * SevenSegment.c
 *
 * Created: 9/22/2021 11:02:46 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "SevenSegment.h"

static uint8 seg_num[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};



void SevenSegment_init(GPIO_port_name_t port , SS_type mode)
{
	if(mode == CC_BCD || mode == CA_BCD)
	{
		GPIO_init_pin(port , SS_BCD_0 , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_BCD_1 , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_BCD_2 , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_BCD_3 , GPIO_PIN_OUTPUT);
	}
	else if (mode == CC_NORMAL || mode == CC_BCD)
	{
		GPIO_init_pin(port , SS_NORMAL_A , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_B , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_C , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_D , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_E , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_F , GPIO_PIN_OUTPUT);
		GPIO_init_pin(port , SS_NORMAL_G , GPIO_PIN_OUTPUT);
	}
}
void SevenSegment_write(GPIO_port_name_t port, SS_type mode, uint8 digit)
{
	switch(mode)
	{
		case CC_BCD:
		GPIO_write_pin(port , SS_BCD_0 , GET_BIT(digit , 0));
		GPIO_write_pin(port , SS_BCD_1 , GET_BIT(digit , 1));
		GPIO_write_pin(port , SS_BCD_2 , GET_BIT(digit , 2));
		GPIO_write_pin(port , SS_BCD_3 , GET_BIT(digit , 3));
		break;

		case CA_BCD:
		break;
		
		case CC_NORMAL:
		break;
		
		case CA_NORMAL:
		break;
	}
}
