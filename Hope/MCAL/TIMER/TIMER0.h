/*
 * TIMER0.h
 *
 * Created: 9/16/2021 7:58:09 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

typedef enum{
	STOP_TIMER,
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	EXTERNAL_CLOCK_FALLING,
	EXTERNAL_CLOCK_RAISING		
}TIMER_Precaler_t;

typedef enum
{
	NORMAL,
	PHASE_CORRECTION_PWM,
	CTC,
	FAST_PWM	
}TIMER_Mode_t;

typedef enum{
	DISCONNECTED,
	TOGGLE,
	NON_INVERTING,
	INVERTING
}TIMER0_OC_mode_t;
void TIMER_Init(TIMER_Mode_t mode , TIMER_Precaler_t pre);
void TIMER0_OV_interrupt_enable();
void TIMER0_OV_interrupt_disable();


#endif /* TIMER0_H_ */