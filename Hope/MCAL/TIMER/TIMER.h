/*
 * TIMER.h
 *
 * Created: 9/11/2021 5:48:27 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER0.h"
#include "TIMER1.h"
#include "TIMER2.h"



// validation MACROS
#define  NOT_VALID_TMR0_MODE(mode) (( mode > 3)||(mode < 0 ))
#define  NOT_VALID_TMR0_COM(com)   ((com > 3)|| (com < 0))
#define  NOT_VALID_TMR0_PRES(pre)  ((pre > 7)|| (com < 0))
#endif /* TIMER_H_ */