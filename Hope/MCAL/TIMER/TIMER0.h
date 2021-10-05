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
#include "TIMERS_SHARED.h"


void	TIMER0_Init(TMR_8BIT_Mode_t mode , SYNC_TMR_Precaler_t pre ,TMR_OC_mode_t oc);
void	TIMER0_OV_interrupt_enable();
void	TIMER0_OV_interrupt_disable();
void	TIMER0_OV_set_callback(void (*isr)(void));

void	TIMER0_CTC_interrupt_enable();
void	TIMER0_CTC_interrupt_disable();
void	TIMER0_CTC_set_callback(void (*isr)(void));

void	TIMER0_set_value(uint8 val);
void	TIMER0_set_OC(uint8 val);
uint8	TIMER0_get_value();
#endif /* TIMER0_H_ */