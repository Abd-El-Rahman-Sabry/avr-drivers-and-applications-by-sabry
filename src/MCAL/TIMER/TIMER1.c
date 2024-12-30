/*
 * TIMER1.c
 *
 * Created: 10/2/2021 3:50:57 PM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "TIMER1.h"

static void (*timer1_overflow_isr)(void) = NULLPTR;
static void (*timer1_compare_a_isr)(void)  = NULLPTR;
static void (*timer1_compare_b_isr)(void)  = NULLPTR;
static void (*timer1_input_capture_isr)(void)  = NULLPTR;




/********************* TIMER 1 ***************************/


void TIMER1_init(TIMER1_mode_t mode , SYNC_TMR_Precaler_t pres , TMR_OC_mode_t oca , TMR_OC_mode_t ocb)
{

	TIMER1_PRESCALAR_ADJ(pres);
	
	
	//setting mode
	WRITE_BIT(TCCR1A ,WGM10 , GET_BIT( (mode) , 0 ));
	WRITE_BIT(TCCR1A ,WGM11 , GET_BIT( (mode) , 1 ));
	WRITE_BIT(TCCR1B ,WGM12 , GET_BIT( (mode) , 2 ));
	WRITE_BIT(TCCR1B ,WGM13 , GET_BIT( (mode) , 3 ));
	
	
	
	switch(oca)
	{
		case DISCONNECTED:
		CLEAR_BIT(TCCR1A , COM1A0);
		CLEAR_BIT(TCCR1A , COM1A1);
		break;
		
		case TOGGLE:
		SET_BIT(TCCR1A , COM1A0);
		CLEAR_BIT(TCCR1A , COM1A1);
		break;
		
		case NON_INVERTING:
		CLEAR_BIT(TCCR1A , COM1A0);
		SET_BIT(TCCR1A , COM1A1);
		break;
		
		case INVERTING:
		SET_BIT(TCCR1A , COM1A0);
		SET_BIT(TCCR1A , COM1A1);
		break;
	}
	
	switch(ocb)
	{
		case DISCONNECTED:
		CLEAR_BIT(TCCR1A , COM1B0);
		CLEAR_BIT(TCCR1A , COM1B1);
		break;
			
		case TOGGLE:
		SET_BIT(TCCR1A , COM1B0);
		CLEAR_BIT(TCCR1A , COM1B1);
		break;
			
		case NON_INVERTING:
		CLEAR_BIT(TCCR1A , COM1B0);
		SET_BIT(TCCR1A , COM1B1);
		break;
			
		case INVERTING:
		SET_BIT(TCCR1A , COM1B0);
		SET_BIT(TCCR1A , COM1B1);
		break;
	}
}


void TIMER1_set_value(uint16 val){
	TCNT1 = val;
}


void TIMERA_set_OC(uint16 val)
{
	OCR1A = val;
}


void TIMERB_set_OC(uint16 val)
{
	OCR1B= val;
}


void TIMER1_set_ICR(uint16 val)
{
	ICR1= val;
}


void TIMER1_stop()
{
	TIMER1_PRESCALAR_ADJ(0);
}


uint16 TIMER1_get_value()
{
	return (TCNT1H*256+TCNT1L);
}


void TIMER1_OF_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE1);
}


void TIMER1_OF_interrupt_disable()
{
	CLEAR_BIT(TIMSK ,TOIE1);
}


void TIMER1_CTC_interrupt_enable()
{
	SET_BIT(TIMSK , OCIE1A);
	SET_BIT(TIMSK , OCIE1B);
}


void TIMER1_CTC_interrupt_disable()
{
	CLEAR_BIT(TIMSK , OCIE1A);
	CLEAR_BIT(TIMSK , OCIE1B);
}


void TIMER1_ICU_interrupt_enable()
{
	SET_BIT(TIMSK , TICIE1);
}


void TIMER1_ICU_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TICIE1);
}


void TIMER1_ICU_triggering(TIMER1_icu_triggering trig)
{
	
	if(trig == ICU_RISING_EDGE)
	SET_BIT(TCCR1B , ICES1);
	
	else if(trig == ICU_FALLING_EDGE)
	CLEAR_BIT(TCCR1B , ICES1);
}


void TIMER1_set_OF_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_overflow_isr = isr;
	}
}


void TIMERA_set_CTC_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_compare_a_isr = isr;
	}
}


void TIMERB_set_CTC_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_compare_b_isr = isr;
	}
}
void TIMER1_set_ICU_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_input_capture_isr = isr;
	}
}


