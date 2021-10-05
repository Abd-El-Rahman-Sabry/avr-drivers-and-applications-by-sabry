/*
 * EXT_INT.h
 *
 * Created: 9/11/2021 12:35:59 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_
#include "../../MCAL_REG/mem_map.h"
#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"

#define MAX_EXT_INT 2

#define INT0_PORT DDRD
#define INT0_PIN  2

#define INT1_PORT DDRD
#define INT1_PIN 3

#define INT2_PORT DDRB
#define INT2_PIN  2

typedef enum{
	EXT_INT0 ,
	EXT_INT1 ,
	EXT_INT2 
}EXT_int_pin_t;

typedef enum {
	EXT_low_level_isc,
	EXT_logic_change_isc,
	EXT_falling_edge_isc,
	EXT_rising_edge_isc	
} EXT_int_sense_control_t;

typedef enum INT_error{
	EXT_SUCCESS,
	EXT_FAIL
} INT_error_t;

typedef struct{
	EXT_int_pin_t pin;
	EXT_int_sense_control_t ctr;
	void (*EXT_isr )(void);	
}EXT_config_pin;

INT_error_t EXT_set_interrupt(EXT_int_pin_t pin);
INT_error_t EXT_clear_interrupt(EXT_int_pin_t pin);
INT_error_t EXT_set_isc(EXT_int_pin_t pin , EXT_int_sense_control_t ctr);
INT_error_t EXT_set_callback(EXT_int_pin_t pin , void (*isr)(void));
INT_error_t EXT_interrupt_init(EXT_config_pin *obj);

//Validate

#define NOT_VALID_INT_PIN(pin) ((pin > 3 )||(pin < 0))
#define NOT_VALID_ISC(isc) ((isc > 5) || (isc < 0))
#endif /* EXT_INT_H_ */