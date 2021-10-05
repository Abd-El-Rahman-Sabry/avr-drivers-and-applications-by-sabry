/*
 * TIMER1.h
 *
 * Created: 10/2/2021 3:51:09 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

#include "TIMERS_SHARED.h"


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


typedef enum
{
	ICU_RISING_EDGE,
	ICU_FALLING_EDGE
}TIMER1_icu_triggering;

#define TIMER1_PRESCALAR_ADJ(scaler)  (TCCR1B = (TCCR1B &~(0x07)) | scaler)


void TIMER1_init(TIMER1_mode_t mode , SYNC_TMR_Precaler_t pres , TMR_OC_mode_t oca , TMR_OC_mode_t ocb);

void TIMER1_set_value(uint16 val);


void TIMERA_set_OC(uint16 val);
void TIMERB_set_OC(uint16 val);
void TIMER1_set_ICR(uint16 val);


void TIMER1_stop();

uint16 TIMER1_get_value();


void TIMER1_OF_interrupt_enable();
void TIMER1_OF_interrupt_disable();


void TIMER1_CTC_interrupt_enable();
void TIMER1_CTC_interrupt_disable();
void TIMER1_ICU_interrupt_enable();
void TIMER1_ICU_interrupt_disable();
void TIMER1_ICU_triggering(TIMER1_icu_triggering trig);

void TIMER1_set_OF_callback(void (*isr)(void));
void TIMERA_set_CTC_callback(void (*isr)(void));
void TIMERB_set_CTC_callback(void (*isr)(void));
void TIMER1_set_ICU_callback(void (*isr)(void));
void TIMER1_periodic_ms(uint16 time ,void (*fp)(void));


#endif /* TIMER1_H_ */