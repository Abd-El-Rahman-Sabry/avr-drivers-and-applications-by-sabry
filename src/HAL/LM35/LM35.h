/*
 * LM35.h
 *
 * Created: 9/18/2021 7:52:44 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef LM35_H_
#define LM35_H_
#include "../../MCAL/ADC/ADC.h"
#include "../../helpers/stdtypes.h"

void LM53_Temp_Sensor_Init(ADC_channel_t channel);

/* 

This function returns the Temperature that was read by the sensor 
you have to make sure that you have initialized the ADC before using this function

*/
uint16 LM35_Get_Temperature();

#endif /* LM35_H_ */