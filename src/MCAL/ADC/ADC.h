/*
 * ADC.h
 *
 * Created: 9/13/2021 11:56:43 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

#define  ENABLE_ADC 1
#define  DISABLE_ADC 1
#define ADC_STATE(state) WRITE_BIT(ADCSRA , ADEN , state);

typedef enum{
		AREF_Pin = 0 ,
		AVCC_pin_External_Cap_At_AREF_pin,
		Internal_2560mV = 3
}ADC_voltage_reference_t;

typedef enum
{
		Channel_0_ADC0 = 0 ,
		Channel_1_ADC1 ,
		Channel_2_ADC2 ,
		Channel_3_ADC3 ,
		Channel_4_ADC4 ,
		Channel_5_ADC5 ,
		Channel_6_ADC6 ,
		Channel_7_ADC7 ,
		DifferentialWithGain_10x_PositiveInputOn_ADC0_NegativeInputOn_ADC0  ,
		DifferentialWithGain_10x_PositiveInputOn_ADC1_NegativeInputOn_ADC0  ,
		DifferentialWithGain_200x_PositiveInputOn_ADC0_NegativeInputOn_ADC0 ,
		DifferentialWithGain_200x_PositiveInputOn_ADC1_NegativeInputOn_ADC0 ,
		DifferentialWithGain_10x_PositiveInputOn_ADC2_NegativeInputOn_ADC2  ,
		DifferentialWithGain_10x_PositiveInputOn_ADC3_NegativeInputOn_ADC2  ,
		DifferentialWithGain_200x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC5_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC6_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC7_NegativeInputOn_ADC1 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC0_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC1_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC2_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC3_NegativeInputOn_ADC2 ,
		DifferentialWithGain_1x_PositiveInputOn_ADC4_NegativeInputOn_ADC2 ,
}ADC_channel_t;



typedef enum{
	ADC_prescaler_2 = 1,
	ADC_prescaler_4,
	ADC_prescaler_8,
	ADC_prescaler_16,
	ADC_prescaler_32,
	ADC_prescaler_64,
	ADC_prescaler_128
} ADC_prescaler_t;


typedef enum {
	AutoTriggerIS_Disabled        ,
	Free_Running_Mode             ,
	Analog_Comparator             ,
	External_Interrupt_Request_0  ,
	Timer_Counter0_Compare_Match  ,
	Timer_Counter0_Overflow       ,
	Timer_Counter_Compare_Match_B ,
	Timer_Counter1_Overflow       ,
	Timer_Counter1_Capture_Event
}ADC_auto_trigger_t;

typedef struct{
	ADC_prescaler_t ps;
	ADC_channel_t channel;
	ADC_voltage_reference_t ref;
} ADC_config_t;


void ADC_init(ADC_channel_t ch , ADC_prescaler_t ps , ADC_voltage_reference_t ref);
void ADC_set_auto_triggering(ADC_auto_trigger_t at);
void ADC_clear_auto_triggering();
void ADC_set_channel(ADC_channel_t channel);
void ADC_enable();
void ADC_disable();
void ADC_set_prescaler(ADC_prescaler_t pre);
void ADC_set_voltage_reference(ADC_voltage_reference_t ref);
void ADC_set_interrupt();
void ADC_clear_interrupt();
uint16 ADC_read(ADC_channel_t channel);
void ADC_set_interrupt_callback(void (*isr)(void));
void ADC_start_conversion();
uint16 ADC_register_val();
ADC_voltage_reference_t ADC_get_current_vref();
uint8 ADC_conversion_flag();
void ADC_enable_noise_reduction();
void ADC_disable_noise_reduction();

#define ADC_NOT_VALID_REF(ref) (ref > 3 || ref == 2 || ref < 0)
#define ADC_NOT_VALID_PS(ps)	(ps > 7 || ps < 0 )
#define ADC_NOT_VALID_CHANNEL(ch) (ch > 15 || ch < 0)
#endif /* ADC_H_ */