/*
 * EXT_INT.c
 *
 * Created: 9/11/2021 1:20:23 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "EXT_INT.h"

static void (*EXT_int0_isr)(void);
static void (*EXT_int1_isr)(void);
static void (*EXT_int2_isr)(void);

INT_error_t EXT_set_interrupt(EXT_int_pin_t pin)
{
	if(NOT_VALID_INT_PIN(pin))
	{
		return EXT_FAIL;
	}
	
	switch(pin)
	{
		case EXT_INT0:
		SET_BIT(GICR , EN_INT0);
		break;
		
		case EXT_INT1:
		SET_BIT(GICR , EN_INT1);
		break;
		
		case EXT_INT2:
		SET_BIT(GICR , EN_INT2);
		break;
	}
	return EXT_SUCCESS;
}
INT_error_t EXT_clear_interrupt(EXT_int_pin_t pin)
{
		if(NOT_VALID_INT_PIN(pin))
		{
			return EXT_FAIL;
		}
		
		switch(pin)
		{
			case EXT_INT0:
			CLEAR_BIT(GICR , EN_INT0);
			break;
			
			case EXT_INT1:
			CLEAR_BIT(GICR , EN_INT1);
			break;
			
			case EXT_INT2:
			CLEAR_BIT(GICR , EN_INT2);
			break;
		}
		return EXT_SUCCESS;
}

static INT_error_t EXT_int0_init(EXT_config_pin* obj){
	INT_error_t state = EXT_SUCCESS;
	if(NOT_VALID_INT_PIN(obj->pin) || NOT_VALID_ISC(obj->ctr))
	{
		return EXT_FAIL;
	}
	
	SET_BIT(GICR , EN_INT0);
	CLEAR_BIT(INT0_PORT , INT0_PIN);
	
	switch(obj->ctr)
	{
		case EXT_low_level_isc:
		{
			CLEAR_BIT(MCUCR , ISC00);
			CLEAR_BIT(MCUCR , ISC01);
			break;
		}
		case EXT_logic_change_isc:
		{
			SET_BIT(MCUCR , ISC00);
			CLEAR_BIT(MCUCR , ISC01);
			break;
		} 
		case EXT_falling_edge_isc:
		{
			CLEAR_BIT(MCUCR , ISC00);
			SET_BIT(MCUCR , ISC01);
			break;
		}
		case EXT_rising_edge_isc:
		{
			SET_BIT(MCUCR , ISC00);
			SET_BIT(MCUCR , ISC01);
			break;
		}
		default:
			state = EXT_FAIL;
			break;
	}
	
		EXT_int0_isr = obj->EXT_isr;
	return state;
}

static INT_error_t EXT_int1_init(EXT_config_pin* obj){
	INT_error_t state = EXT_SUCCESS;
	
	if(NOT_VALID_INT_PIN(obj->pin) || NOT_VALID_ISC(obj->ctr))
	{
		return EXT_FAIL;
	}
	SET_BIT(GICR , EN_INT1);
	CLEAR_BIT(INT1_PORT , INT1_PIN);
	switch(obj->ctr){
		case EXT_low_level_isc:
		{
			CLEAR_BIT(MCUCR , ISC10);
			CLEAR_BIT(MCUCR , ISC11);
			break;
		}
		case EXT_logic_change_isc:
		{
			SET_BIT(MCUCR , ISC10);
			CLEAR_BIT(MCUCR , ISC11);
			break;
		}
		case EXT_falling_edge_isc:
		{
			CLEAR_BIT(MCUCR , ISC10);
			SET_BIT(MCUCR , ISC11);
			break;
		}
		case EXT_rising_edge_isc:
		{
			SET_BIT(MCUCR , ISC10);
			SET_BIT(MCUCR , ISC11);
			break;
		}
		default:
		state = EXT_FAIL;
		break;
	}
	if(obj->EXT_isr != NULLPTR){
		EXT_int1_isr = obj->EXT_isr;
	}
	return state;
}

static INT_error_t EXT_int2_init(EXT_config_pin* obj){
	INT_error_t state = EXT_SUCCESS;
	if(NOT_VALID_INT_PIN(obj->pin) || NOT_VALID_ISC(obj->ctr))
	{
		return EXT_FAIL;
	}
	SET_BIT(GICR , EN_INT2);	
	CLEAR_BIT(INT2_PORT , INT2_PIN);
	
	switch(obj->ctr){
		case EXT_falling_edge_isc:
		{
			CLEAR_BIT(MCUCSR , ISC2);
			break;
		}
		case EXT_rising_edge_isc:
		{
			SET_BIT(MCUCSR , ISC2);
			break;
		}
		default:
		state = EXT_FAIL;
		break;
	}
	if(obj->EXT_isr != NULLPTR){
		EXT_int2_isr = obj->EXT_isr;
	}
	return state;
}

INT_error_t EXT_interrupt_init(EXT_config_pin *obj)
{
	
	if(obj->pin == EXT_INT0)
	{
		return EXT_int0_init(obj);
	}
	else if (obj->pin == EXT_INT1)
	{
		return EXT_int1_init(obj);
	}
	else if(obj->pin == EXT_INT2)
	{
		return EXT_int2_init(obj);
	}
	return EXT_SUCCESS;
}

INT_error_t EXT_set_isc(EXT_int_pin_t pin , EXT_int_sense_control_t ctr)
{
	if(NOT_VALID_ISC(ctr) || NOT_VALID_INT_PIN(pin))
	{
		return EXT_FAIL;
	}
	
	if(pin == EXT_INT0)
	{
			switch(ctr){
				case EXT_low_level_isc:
				{
					CLEAR_BIT(MCUCR , ISC00);
					CLEAR_BIT(MCUCR , ISC01);
					break;
				}
				case EXT_logic_change_isc:
				{
					SET_BIT(MCUCR , ISC00);
					CLEAR_BIT(MCUCR , ISC01);
					break;
				}
				case EXT_falling_edge_isc:
				{
					CLEAR_BIT(MCUCR , ISC00);
					SET_BIT(MCUCR , ISC01);
					break;
				}
				case EXT_rising_edge_isc:
				{
					SET_BIT(MCUCR , ISC00);
					SET_BIT(MCUCR , ISC01);
					break;
				}
			}
	}
	
	else if(pin == EXT_INT1)
	{
			switch(ctr){
				case EXT_low_level_isc:
				{
					CLEAR_BIT(MCUCR , ISC10);
					CLEAR_BIT(MCUCR , ISC11);
					break;
				}
				case EXT_logic_change_isc:
				{
					SET_BIT(MCUCR , ISC10);
					CLEAR_BIT(MCUCR , ISC11);
					break;
				}
				case EXT_falling_edge_isc:
				{
					CLEAR_BIT(MCUCR , ISC10);
					SET_BIT(MCUCR , ISC11);
					break;
				}
				case EXT_rising_edge_isc:
				{
					SET_BIT(MCUCR , ISC10);
					SET_BIT(MCUCR , ISC11);
					break;
				}

			}
	}
	else if(pin == EXT_INT2){
		switch(ctr){
			case EXT_falling_edge_isc:
			{
				CLEAR_BIT(MCUCSR , ISC2);
				break;
			}
			case EXT_rising_edge_isc:
			{
				SET_BIT(MCUCSR , ISC2);
				break;
			}
		}
	}
	
	return EXT_SUCCESS;
}


INT_error_t EXT_set_callback(EXT_int_pin_t pin , void (*isr)(void))
{
	if(NOT_VALID_INT_PIN(pin))
		return EXT_FAIL;
	
	if(pin == EXT_INT0)
	{
		if(isr != NULLPTR)
		{
			EXT_int0_isr = isr;
		}
	}
	else if(pin == EXT_INT1)
	{
		if(isr != NULLPTR)
		{
			EXT_int1_isr = isr;
		}
	}
	else if(pin == EXT_INT2)
	{
		if(isr != NULLPTR)
		{
			EXT_int2_isr = isr;
		}
	}
	
	return EXT_SUCCESS;
}

ISR(INT0_vect)
{
	EXT_int0_isr();
}
ISR(INT1_vect)
{
	EXT_int1_isr();
}
ISR(INT2_vect)
{
	EXT_int2_isr();
}