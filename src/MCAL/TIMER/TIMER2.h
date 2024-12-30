/*
 * TIMER2.h
 *
 * Created: 10/1/2021 8:49:49 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef TIMER2_H_
#define TIMER2_H_

#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

#include "TIMERS_SHARED.h"


void	TIMER2_Init(TMR_8BIT_Mode_t mode , SYNC_TMR_Precaler_t pre ,TMR_OC_mode_t oc);
void	TIMER2_OV_interrupt_enable();
void	TIMER2_OV_interrupt_disable();
void	TIMER2_OV_set_callback(void (*isr)(void));

void	TIMER2_CTC_interrupt_enable();
void	TIMER2_CTC_interrupt_disable();
void	TIMER2_CTC_set_callback(void (*isr)(void));

void	TIMER2_set_value(uint8 val);
void	TIMER2_set_OC(uint8 val);
uint8	TIMER2_get_value();


#endif /* TIMER2_H_ */