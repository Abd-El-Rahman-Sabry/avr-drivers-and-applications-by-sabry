/*
 * TIMER0.c
 *
 * Created: 9/16/2021 7:58:22 PM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "TIMER0.h"

void TIMER_Init(TIMER_Mode_t mode , TIMER_Precaler_t pre)
{
	switch(mode)
	{
		case NORMAL:
			CLEAR_BIT(TCCR0 , WGM00);
			CLEAR_BIT(TCCR0 , WGM01);
		break;
		
		case PHASE_CORRECTION_PWM:
			SET_BIT(TCCR0 , WGM00);
			CLEAR_BIT(TCCR0 , WGM01);
		break;
		
		case CTC:
			CLEAR_BIT(TCCR0 , WGM00);
			SET_BIT(TCCR0 , WGM01);
		break;
		
		case FAST_PWM:
			SET_BIT(TCCR0 , WGM00);
			SET_BIT(TCCR0 , WGM01);
		break;
	}
	
	WRITE_BIT(TCCR0 , CS00 , GET_BIT((uint8)pre , 0));
	WRITE_BIT(TCCR0 , CS01 , GET_BIT((uint8)pre , 1));
	WRITE_BIT(TCCR0 , CS02 , GET_BIT((uint8)pre , 2));
}
void TIMER0_OV_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE0);
}
void TIMER0_OV_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TOIE0);
}