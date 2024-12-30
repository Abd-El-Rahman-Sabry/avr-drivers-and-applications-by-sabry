/*
 * LM35.c
 *
 * Created: 9/18/2021 7:52:34 PM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "LM35.h"
static ADC_channel_t lm_channel = -1;

void LM53_Temp_Sensor_Init(ADC_channel_t channel)
{
	lm_channel = channel;
}
uint16 LM35_Get_Temperature()
{
	if(lm_channel == -1)
		return -1;
	
	
	ADC_voltage_reference_t vr = ADC_get_current_vref();
	
	uint16 data = ADC_read(lm_channel);
	
	if(vr == AVCC_pin_External_Cap_At_AREF_pin)
	{
		return (data*4.88/10);
	}
	else if(vr == Internal_2560mV)
	{
		return (data*2.5/10);
	}
}