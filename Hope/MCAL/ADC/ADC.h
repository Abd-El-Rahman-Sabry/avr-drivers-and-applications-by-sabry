/*
 * ADC.h
 *
 * Created: 9/13/2021 11:56:43 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef ADC_H_
#define ADC_H_


typedef enum{
		VrefAt_AREF_Pin = 0 ,
		VrefAt_AVCC_pin_AREF_pin,
		VrefAt_Internal_2560mV
}ADC_voltage_reference;

typedef enum
{
		Single_Ended_Input_On_Channel_0_ADC0 = 0 ,
		Single_Ended_Input_On_Channel_1_ADC1 ,
		Single_Ended_Input_On_Channel_2_ADC2 ,
		Single_Ended_Input_On_Channel_3_ADC3 ,
		Single_Ended_Input_On_Channel_4_ADC4 ,
		Single_Ended_Input_On_Channel_5_ADC5 ,
		Single_Ended_Input_On_Channel_6_ADC6 ,
		Single_Ended_Input_On_Channel_7_ADC7 ,
		
		
		DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0  ,
		DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0 ,
		DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2  ,
		DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC2
}ADC_channel;

typedef struct{
	
} ADC_config;

typedef enum{
	
	
} ADC_prescaler;

void ADC_init();
void ADC_enable();
void ADC_disable();
void ADC_set_prescaler(ADC_prescaler pre);
void ADC_set_voltage_reference(ADC_voltage_reference ref);

void ADC_start_conversion();
uint16 ADC_register_val();
uint8 ADC_conversion_flag();


#endif /* ADC_H_ */