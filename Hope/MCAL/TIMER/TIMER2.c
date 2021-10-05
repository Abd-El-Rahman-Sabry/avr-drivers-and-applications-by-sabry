/*
 * TIMER2.c
 *
 * Created: 10/1/2021 8:49:58 PM
 *  Author: Abd-El-Rahman Sabry
 */ 



#include "TIMER2.h"
static void (*timer2_of_isr)(void) = NULLPTR;
static void (*timer2_ctc_isr)(void) = NULLPTR;

void TIMER2_Init(TMR_8BIT_Mode_t mode , SYNC_TMR_Precaler_t pre ,TMR_OC_mode_t oc)
{
	switch(mode)
	{
		case NORMAL:
			CLEAR_BIT(TCCR2 , WGM20);
			CLEAR_BIT(TCCR2 , WGM21);
		break;
		
		case PHASE_CORRECTION_PWM:
			SET_BIT(TCCR2 , WGM20);
			CLEAR_BIT(TCCR2 , WGM21);
		break;
		
		case CTC:
			CLEAR_BIT(TCCR2 , WGM20);
			SET_BIT(TCCR2 , WGM21);
		break;
		
		case FAST_PWM:
			SET_BIT(TCCR2 , WGM20);
			SET_BIT(TCCR2 , WGM21);
		break;
	}
	/*
	WRITE_BIT(TCCR0 , CS00 , GET_BIT((uint8)pre , 0));
	WRITE_BIT(TCCR0 , CS01 , GET_BIT((uint8)pre , 1));
	WRITE_BIT(TCCR0 , CS02 , GET_BIT((uint8)pre , 2));
	*/
	
	TCCR2 = TMR_8BIT_PRESCALE(2,pre);
	
	WRITE_BIT(TCCR2 , COM20  , GET_BIT(oc , 0));
	WRITE_BIT(TCCR2 , COM21  , GET_BIT(oc , 1));

}
void TIMER2_OV_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE2);
}
void TIMER2_OV_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TOIE2);
}
void TIMER2_OV_set_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	timer2_of_isr = isr;
}







void	TIMER2_CTC_interrupt_enable()
{
	SET_BIT(TIMSK , OCIE2);
}
void	TIMER2_CTC_interrupt_disable()
{
	CLEAR_BIT(TIMSK , OCIE2);
}
void	TIMER2_CTC_set_callback(void (*isr)(void))
{
		if(isr != NULLPTR)
			timer2_ctc_isr = isr;
}












void	TIMER2_set_value(uint8 val)
{
	TCNT2 = val;
}
void	TIMER2_set_OC(uint8 val)
{
	OCR2 = val;
}
uint8	TIMER2_get_value()
{
	return TCNT2;
}










ISR(TIMER2_OVF)
{
	if(timer2_of_isr!= NULLPTR)
		timer2_of_isr();
}

ISR(TIMER2_COMP)
{
	if(timer2_ctc_isr!= NULLPTR)
		timer2_ctc_isr();
}