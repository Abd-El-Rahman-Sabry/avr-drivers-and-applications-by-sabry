/*
 * TIMER.c
 *
 * Created: 9/11/2021 5:50:08 PM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "TIMER.h"
static volatile uint16 t1 ,t2 , t3 , flag = 0;
static volatile uint16 scaler0;
static volatile uint16 scaler1;


static void(*functions[STACK_SIZE])(void);
static uint8 stk_pointer = 0;


static void (*timer0_overflow_isr)(void) = NULLPTR;
static void (*timer0_compare_isr)(void)  = NULLPTR;
static void (*timer1_overflow_isr)(void) = NULLPTR;
static void (*timer1_compare_a_isr)(void)  = NULLPTR;
static void (*timer1_compare_b_isr)(void)  = NULLPTR;
static void (*timer1_input_capture_isr)(void)  = NULLPTR;


void TIMER0_init(TIMER0_mode_t mode , TIMER0_prescale_t pres , TIMER0_compare_output_mode_t com)
{
	if(NOT_VALID_TMR0_MODE(mode) || NOT_VALID_TMR0_COM(com) || NOT_VALID_TMR0_PRES(pres))
	{
		return;
	}
	
	// Setting prescaler
	TIMER0_PRESCALAR_ADJ(pres);
	scaler0 = pres;
	
	/*setting timer0 mode 
	0 0 Overflow
	0 1 Phase correction PWM
	1 0 CTC mode 
	1 1 Fast PWM mode 
	*/

	switch(mode)
	{
		case TIMER0_OVERFLOW:
		CLEAR_BIT(TCCR0 , WGM00);
		CLEAR_BIT(TCCR0 , WGM01);
		break;
		
		case TIMER0_PHASE_CORRECTION_PWM:
		SET_BIT(TCCR0 , WGM00);
		CLEAR_BIT(TCCR0 , WGM01);
		break;
		
		case TIMER0_CTC:
		CLEAR_BIT(TCCR0 , WGM00);
		SET_BIT(TCCR0 , WGM01);
		break;
		
		case TIMER0_FAST_PWM:
		SET_BIT(TCCR0 , WGM00);
		SET_BIT(TCCR0 , WGM01);
		break;
	}
	switch(com)
	{
		case TIMER0_OCO_DISCONNECTED:
		CLEAR_BIT(TCCR0 , COM00);
		CLEAR_BIT(TCCR0 , COM01);
		break;
		
		case TIMER0_OCO_TOGGLE:
		SET_BIT(TCCR0 , COM00);
		CLEAR_BIT(TCCR0 , COM01);
		break;
		
		case TIMER0_OCO_NON_INVERTING:
		CLEAR_BIT(TCCR0 , COM00);
		SET_BIT(TCCR0 , COM01);
		break;
		
		case TIMER0_OCO_INVERTING:
		SET_BIT(TCCR0 , COM00);
		SET_BIT(TCCR0 , COM01);
		break;
	}

}
void TIMER0_reload(uint8 val){
	TCNT0 = val;
}
void TIMER0_compare_reload(uint8 com_val)
{
	OCR0 = com_val;
}
void TIMER0_stop(){
	PORT_CLEAR_MASK(TCCR0 , TMR0_STP);
}
uint8 TIMER0_get_current_count()
{
	return TCNT0;
}
void TIMER0_overflow_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE0);
}
void TIMER0_overflow_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TOIE0);
}
void TIMER0_output_compare_interrupt_enable()
{
	SET_BIT(TIMSK , OCIE0);
}
void TIMER0_output_compare_interrupt_disable()
{
	CLEAR_BIT(TIMSK , OCIE0);
}

void TIMER0_set_overflow_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer0_overflow_isr = isr;
	} 
}
void TIMER0_set_compare_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer0_compare_isr = isr;
	}
}


/********************* TIMER 1 ***************************/


void TIMER1_init(TIMER0_mode_t mode , TIMER1_prescale_t pres)
{
	//setting mode 
	WRITE_BIT(TCCR1A ,WGM10 , GET_BIT( (mode) , 0 ));
	WRITE_BIT(TCCR1A ,WGM11 , GET_BIT( (mode) , 1 ));
	WRITE_BIT(TCCR1B ,WGM12 , GET_BIT( (mode) , 2 ));
	WRITE_BIT(TCCR1B ,WGM13 , GET_BIT( (mode) , 3 ));
	
	TIMER1_PRESCALAR_ADJ(pres);
	scaler1 = pres;
	
}


void TIMER1A_set_compare_output_mode(TIMER1_compare_output_mode_t mode)
{
	switch(mode)
	{
		case TIMER1_OCO_DISCONNECTED:
		CLEAR_BIT(TCCR1A , COM1A0);
		CLEAR_BIT(TCCR1A , COM1A1);
		break;
		
		case TIMER1_OCO_TOGGLE:
		SET_BIT(TCCR1A , COM1A0);
		CLEAR_BIT(TCCR1A , COM1A1);
		break;
		
		case TIMER1_OCO_NON_INVERTING:
		CLEAR_BIT(TCCR1A , COM1A0);
		SET_BIT(TCCR1A , COM1A1);
		break;
		
		case TIMER1_OCO_INVERTING:
		SET_BIT(TCCR1A , COM1A0);
		SET_BIT(TCCR1A , COM1A1);
		break;
	}
}


void TIMER1B_set_compare_output_mode(TIMER1_compare_output_mode_t mode)
{
		switch(mode)
		{
			case TIMER1_OCO_DISCONNECTED:
			CLEAR_BIT(TCCR1A , COM1B0);
			CLEAR_BIT(TCCR1A , COM1B1);
			break;
			
			case TIMER1_OCO_TOGGLE:
			SET_BIT(TCCR1A , COM1B0);
			CLEAR_BIT(TCCR1A , COM1B1);
			break;
			
			case TIMER1_OCO_NON_INVERTING:
			CLEAR_BIT(TCCR1A , COM1B0);
			SET_BIT(TCCR1A , COM1B1);
			break;
			
			case TIMER1_OCO_INVERTING:
			SET_BIT(TCCR1A , COM1B0);
			SET_BIT(TCCR1A , COM1B1);
			break;
		}
}


void TIMER1_reload(uint16 val){
	TCNT1L = val;
	TCNT1H = val>>8;
}


void TIMER1_compare_A_reload(uint16 val)
{
	OCR1AL = val;
	OCR1AH = val>>8;
}


void TIMER1_compare_B_reload(uint16 val)
{
		OCR1BL = val;
		OCR1BH = val>>8;
}


void TIMER1_icu_reload(uint16 val)
{
	ICR1L = val;
	ICR1H = val>>8;
	
}


void TIMER1_stop()
{
	TIMER1_PRESCALAR_ADJ(0);
}


uint16 TIMER1_get_current_count()
{
	return (TCNT1H*256+TCNT1L);
}


void TIMER1_overflow_interrupt_enable()
{
	SET_BIT(TIMSK , TOIE1);
}


void TIMER1_overflow_interrupt_disable()
{
	CLEAR_BIT(TIMSK ,TOIE1);
}


void TIMER1_output_compare_interrupt_enable()
{
	SET_BIT(TIMSK , OCIE1A);
	SET_BIT(TIMSK , OCIE1B);
}


void TIMER1_output_compare_interrupt_disable()
{
	CLEAR_BIT(TIMSK , OCIE1A);
	CLEAR_BIT(TIMSK , OCIE1B);
}


void TIMER1_input_capture_interrupt_enable()
{
	SET_BIT(TIMSK , TICIE1);
}


void TIMER1_input_capture_interrupt_disable()
{
	CLEAR_BIT(TIMSK , TICIE1);
}


void TIMER1_set_icu_triggering(TIMER1_icu_triggering trig)
{
	if(trig == ICU_RISING_EDGE)
		SET_BIT(TCCR1B , ICES1);
	else if(trig == ICU_FALLING_EDGE)
		CLEAR_BIT(TCCR1B , ICES1);
}


void TIMER1_set_overflow_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_overflow_isr = isr;
	}
}


void TIMER1_set_compare_a_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_compare_a_isr = isr;
	}
}


void TIMER1_set_compare_b_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_compare_b_isr = isr;
	}
}
void TIMER1_set_input_compare_callback(void (*isr)(void))
{
	if(isr != NULLPTR)
	{
		timer1_input_capture_isr = isr;
	}
}


ISR(TIMER0_OVF)
{
	if(timer0_overflow_isr != NULLPTR)
	{	
		timer0_overflow_isr();
	}
}
ISR(TIMER0_COMP)
{
	if(timer0_compare_isr != NULLPTR)
	{
		timer0_compare_isr();
	}
}


ISR(TIMER1_OVF)
{
	if(timer1_overflow_isr != NULLPTR)
	{
		timer1_overflow_isr();
	}
}

ISR(TIMER1_COMPA)
{
	if(timer1_compare_a_isr != NULLPTR)
	{
		timer1_compare_a_isr();
	}
}

ISR(TIMER1_COMPB)
{
	if(timer1_compare_b_isr != NULLPTR)
	{
		timer1_compare_b_isr();
	}
}

ISR(TIMER1_CAPT)
{
	if(timer1_input_capture_isr != NULLPTR)
	{
		timer1_input_capture_isr();
	}
}


/*********************************INERRUPT DELAY***************************************/ 
void TIMER1_periodic_ms(uint16 time,void (*fp)(void))
{
	TIMER1_reload(0);
	TIMER1_init(TIMER1_CTC , TIMER1_PRESCALER_NORMAL);
	TIMER1_compare_A_reload((uint16)(time*1000));
	TIMER1_set_compare_a_callback(fp);
}

                                                                     