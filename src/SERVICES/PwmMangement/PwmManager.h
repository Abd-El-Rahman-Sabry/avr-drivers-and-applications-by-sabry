/*
 * PwmMananger.h
 *
 * Created: 10/4/2021 7:05:10 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef PWMMANAGER_H_
#define PWMMANAGER_H_
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../HAL/LCD/LCD.h"
typedef enum{
	SW_PWM,
	HW_PWM
}PwmType;

typedef struct{
	uint16 freq;
	uint16 counter;
	uint8 port; 
	uint8 pin;
	uint8 duty;
}SoftwarePwm_t;


typedef enum{
	HW_PWM_OC0,
	HW_PWM_OCA,
	HW_PWM_OCB,
	HW_PWM_OC2	
}HardwarePwm_t;


typedef enum{
	SWP_STACK_FULL,
	SWP_FREQ_ERROR,	
	SWP_SUCCESS
}SW_PWM_ERROR;



uint8 appendSWPWM(SoftwarePwm_t *sw);
SW_PWM_ERROR SW_PWM_config(SoftwarePwm_t *swp , GPIO_port_name_t port , uint8 pin , uint16 freq , uint8 duty);

#endif /* PWMMANANGER_H_ */