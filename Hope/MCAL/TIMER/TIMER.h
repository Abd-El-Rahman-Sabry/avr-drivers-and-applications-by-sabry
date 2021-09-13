/*
 * TIMER.h
 *
 * Created: 9/11/2021 5:48:27 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

#define STACK_SIZE 10

typedef enum{
	
	TIMER0,
	TIMER1,
	TIMER2	

}TMR_name_t;




/*****************************TIMER0*********************************************/
typedef enum{
	
	TIMER0_OVERFLOW,
	TIMER0_PHASE_CORRECTION_PWM,
	TIMER0_CTC,	
	TIMER0_FAST_PWM

}TIMER0_mode_t;

typedef enum {

	TIMER0_STOP,
	TIMER0_PRESCALER_NORMAL,
	TIMER0_PRESCALER_8,
	TIMER0_PRESCALER_64,
	TIMER0_PRESCALER_256,
	TIMER0_PRESCALER_1024,
	EXTERNAL_FALLING,
	EXTERNAL_RISING

}TIMER0_prescale_t;

typedef enum{

	TIMER0_OCO_DISCONNECTED,
	TIMER0_OCO_TOGGLE,
	TIMER0_OCO_NON_INVERTING,
	TIMER0_OCO_INVERTING

}TIMER0_compare_output_mode_t;

#define TMR0_STP 0x07
/*

	(TCCR0 = (TCCR0 &~(0x07)) | scaler)
	
	
	X X X X X X X X   ==> This the TCCR register
	&
	1 1 1 1 1 0 0 0   ==> AND with The ones complement of 0x07
	_________________
	X X X X X 0 0 0
	|
	0 0 0 0 0 a b c   ==> OR with a 3bit scaler a b c
	_________________
	X X	X X X a b c

*/
#define TIMER0_PRESCALAR_ADJ(scaler)  (TCCR0 = (TCCR0 &~(0x07)) | scaler)


void TIMER0_init(TIMER0_mode_t mode , TIMER0_prescale_t pres , TIMER0_compare_output_mode_t com);
void TIMER0_reload(uint8 val);
void TIMER0_compare_reload(uint8 com_val);
void TIMER0_stop();
uint8 TIMER0_get_current_count();
void TIMER0_overflow_interrupt_enable();
void TIMER0_overflow_interrupt_disable();
void TIMER0_output_compare_interrupt_enable();
void TIMER0_output_compare_interrupt_disable();

void TIMER0_set_overflow_callback(void (*isr)(void));
void TIMER0_set_compare_callback(void (*isr)(void));


/*********************************TIMER1***************************************/
typedef enum {

	TIMER1_STOP,
	TIMER1_PRESCALER_NORMAL,
	TIMER1_PRESCALER_8,
	TIMER1_PRESCALER_64,
	TIMER1_PRESCALER_256,
	TIMER1_PRESCALER_1024,
	TIMER1_EXTERNAL_FALLING,
	TIMER1_EXTERNAL_RISING

}TIMER1_prescale_t;

typedef enum {
	TIMER1_OVERFLOW,
	TIMER1_PHASE_CORRECT_PWM_8b,
	TIMER1_PHASE_CORRECT_PWM_9b,
	TIMER1_PHASE_CORRECT_PWM_10b,
	TIMER1_CTC,
	TIMER1_FAST_PWM_8b,
	TIMER1_FAST_PWM_9b,
	TIMER1_FAST_PWM_10b,
	TIMER1_PHASE_CORR_FREQ_PWM_ICU,
	TIMER1_PHASE_CORR_FREQ_PWM,
	TIMER1_PHASE_CORR_ICU,
	TIMER1_PHASE_CORR_OCRA,
	TIMER1_CTC_ICU,
	TIMER1_FAST_PWM_ICU = 14,
	TIMER1_FAST_PWM_OCRA
}TIMER1_mode_t;

typedef enum{

	TIMER1_OCO_DISCONNECTED,
	TIMER1_OCO_TOGGLE,
	TIMER1_OCO_NON_INVERTING,
	TIMER1_OCO_INVERTING

}TIMER1_compare_output_mode_t;


typedef enum
{
	ICU_RISING_EDGE,
	ICU_FALLING_EDGE	
}TIMER1_icu_triggering;

void TIMER1_init(TIMER0_mode_t mode , TIMER1_prescale_t pres);
void TIMER1A_set_compare_output_mode(TIMER1_compare_output_mode_t mode);
void TIMER1B_set_compare_output_mode(TIMER1_compare_output_mode_t mode);
void TIMER1_reload(uint16 val);
void TIMER1_compare_A_reload(uint16 val);
void TIMER1_compare_B_reload(uint16 val);
void TIMER1_icu_reload(uint16 val);
void TIMER1_stop();
uint16 TIMER1_get_current_count();
void TIMER1_overflow_interrupt_enable();
void TIMER1_overflow_interrupt_disable();
void TIMER1_output_compare_interrupt_enable();
void TIMER1_output_compare_interrupt_disable();
void TIMER1_input_capture_interrupt_enable();
void TIMER1_input_capture_interrupt_disable();
void TIMER1_set_icu_triggering(TIMER1_icu_triggering trig);

void TIMER1_set_overflow_callback(void (*isr)(void));
void TIMER1_set_compare_a_callback(void (*isr)(void));
void TIMER1_set_compare_b_callback(void (*isr)(void));
void TIMER1_set_input_compare_callback(void (*isr)(void));
void TIMER1_periodic_ms(uint16 time ,void (*fp)(void));

#define TIMER1_PRESCALAR_ADJ(scaler)  (TCCR1B = (TCCR1B &~(0x07)) | scaler)
// validation MACROS
#define  NOT_VALID_TMR0_MODE(mode) (( mode > 3)||(mode < 0 ))
#define  NOT_VALID_TMR0_COM(com)   ((com > 3)|| (com < 0))
#define  NOT_VALID_TMR0_PRES(pre)  ((pre > 7)|| (com < 0))
#endif /* TIMER_H_ */