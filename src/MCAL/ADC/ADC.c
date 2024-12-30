/*
 * ADC.c
 *
 * Created: 9/13/2021 11:56:57 PM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "ADC.h"

static void (*adc_isr)(void) = NULLPTR;
static ADC_voltage_reference_t Vref;


void ADC_init(ADC_channel_t ch , ADC_prescaler_t ps , ADC_voltage_reference_t ref)
{
	if(ADC_NOT_VALID_CHANNEL(ch) || ADC_NOT_VALID_PS(ps) || ADC_NOT_VALID_REF(ref) )
	{
		return;
	}
	ADC_STATE(ENABLE_ADC);
	//Set channel 
	WRITE_BIT(ADMUX , MUX0 , GET_BIT(ch , 0));
	WRITE_BIT(ADMUX , MUX1 , GET_BIT(ch , 1));
	WRITE_BIT(ADMUX , MUX2 , GET_BIT(ch , 2));
	WRITE_BIT(ADMUX , MUX3 , GET_BIT(ch , 3));
	WRITE_BIT(ADMUX , MUX4 , GET_BIT(ch , 4));
	
	
	//Right adjustment
	CLEAR_BIT(ADMUX , ADLAR);
	
	//set reference
	WRITE_BIT(ADMUX , REFS0 ,	GET_BIT(ref , 0));
	WRITE_BIT(ADMUX	, REFS1	,	GET_BIT(ref , 1));
	Vref = ref;
	
	//set prescaler
	
	WRITE_BIT(ADCSRA , ADPS0 , GET_BIT(ps , 0));
	WRITE_BIT(ADCSRA , ADPS1 , GET_BIT(ps , 1));
	WRITE_BIT(ADCSRA , ADPS2 , GET_BIT(ps , 2));
}
void ADC_enable()
{
	ADC_STATE(ENABLE_ADC);
}
void ADC_disable()
{
	ADC_STATE(DISABLE_ADC);
}
void ADC_enable_noise_reduction()
{
	SET_BIT(MCUCR ,SM0);
	CLEAR_BIT(MCUCR ,SM1);
	CLEAR_BIT(MCUCR ,SM2);
}
void ADC_disable_noise_reduction()
{
		CLEAR_BIT(MCUCR ,SM0);
		CLEAR_BIT(MCUCR ,SM1);
		CLEAR_BIT(MCUCR ,SM2);
}
void ADC_set_channel(ADC_channel_t channel)
{
	if(ADC_NOT_VALID_CHANNEL(channel))
		return;
	WRITE_BIT(ADMUX , MUX0 , GET_BIT(channel , 0));
	WRITE_BIT(ADMUX , MUX1 , GET_BIT(channel , 1));
	WRITE_BIT(ADMUX , MUX2 , GET_BIT(channel , 2));
	WRITE_BIT(ADMUX , MUX3 , GET_BIT(channel , 3));
	WRITE_BIT(ADMUX , MUX4 , GET_BIT(channel , 4));
}
void ADC_set_prescaler(ADC_prescaler_t ps)
{
	if(ADC_NOT_VALID_PS(ps))
		return;
	WRITE_BIT(ADCSRA , ADPS0 , GET_BIT(ps , 0));
	WRITE_BIT(ADCSRA , ADPS1 , GET_BIT(ps , 1));
	WRITE_BIT(ADCSRA , ADPS2 , GET_BIT(ps , 2));
}
void ADC_set_voltage_reference(ADC_voltage_reference_t ref)
{
	if(ADC_NOT_VALID_REF(ref))
		return;
	WRITE_BIT(ADMUX , REFS0 ,	GET_BIT(ref , 0));
	WRITE_BIT(ADMUX	, REFS1	,	GET_BIT(ref , 1));
	Vref = ref;
}
void ADC_set_auto_triggering(ADC_auto_trigger_t at)
{	
	if(at == AutoTriggerIS_Disabled)
	{
			CLEAR_BIT(ADCSRA , ADATE);
			return;
	}
	WRITE_BIT(SFIOR , ADTS0 , GET_BIT((at-1) , 0));
	WRITE_BIT(SFIOR , ADTS1 , GET_BIT((at-1) , 1));
	WRITE_BIT(SFIOR , ADTS2 , GET_BIT((at-1) , 2));
	
}
ADC_voltage_reference_t ADC_get_current_vref() {return Vref;}

void ADC_set_interrupt_callback(void (*isr)(void))
{
	if(isr == NULLPTR)
		return;
	adc_isr = isr;
}
void ADC_start_conversion()
{
	SET_BIT(ADCSRA , ADSC);
}
uint16 ADC_register_val()
{
	return (ADCL + ADCH*256);
}
uint8 ADC_conversion_flag()
{
	return GET_BIT(ADCSRA , ADIF);
}
void ADC_set_interrupt()
{
	SET_BIT(ADCSRA , ADIE);
}
void ADC_clear_interrupt()
{
	CLEAR_BIT(ADCSRA , ADIE);
}
uint16 ADC_read(ADC_channel_t channel)
{
	ADC_set_channel(channel);
	
	ADC_start_conversion();
	while(GET_BIT(ADCSRA , ADIF) == 0);
	
	return  (ADCL + ADCH*256);
}

ISR(ADC_vect)
{
	if(adc_isr != NULLPTR)
	{
		adc_isr();
	}
}