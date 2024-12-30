/*
 * TIMER0.c
 *
 * Created: 9/16/2021 7:58:22 PM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "TIMER0.h"
static void (*timer0_of_isr)(void) = NULLPTR;
static void (*timer0_ctc_isr)(void) = NULLPTR;

void TIMER0_Init(TMR_8BIT_Mode_t mode , SYNC_TMR_Precaler_t pre ,TMR_OC_mode_t oc)
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
	/*
	WRITE_BIT(TCCR0 , CS00 , GET_BIT((uint8)pre , 0));
	WRITE_BIT(TCCR0 , CS01 , GET_BIT((uint8)pre , 1));
	WRITE_BIT(TCCR0 , CS02 , GET_BIT((uint8)pre , 2));
	*/
	
	TCCR0 = TMR_8BIT_PRESCALE(0,pre);
	
	WRITE_BIT(TCCR0 , COM00  , GET_BIT(oc , 0));
	WRITE_BIT(TCCR0 , COM01  , GET_BIT(oc , 1));

}
void TIMER0_OV_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE0);
}
void TIMER0_OV_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TOIE0);
}
void TIMER0_OV_set_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	timer0_of_isr = isr;
}







void	TIMER0_CTC_interrupt_enable()
{
	SET_BIT(TIMSK , OCIE0);
}
void	TIMER0_CTC_interrupt_disable()
{
	CLEAR_BIT(TIMSK , OCIE0);
}
void	TIMER0_CTC_set_callback(void (*isr)(void))
{
		if(isr != NULLPTR)
			timer0_ctc_isr = isr;
}












void	TIMER0_set_value(uint8 val)
{
	TCNT0 = val;
}
void	TIMER0_set_OC(uint8 val)
{
	OCR0 = val;
}
uint8	TIMER0_get_value()
{
	return TCNT0;
}










ISR(TIMER0_OVF)
{
	if(timer0_of_isr!= NULLPTR)
		timer0_of_isr();
}

ISR(TIMER0_COMP)
{
	if(timer0_ctc_isr!= NULLPTR)
		timer0_ctc_isr();
}