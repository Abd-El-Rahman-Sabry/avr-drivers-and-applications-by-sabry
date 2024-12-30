/*
 * GPIO.h
 *
 * Created: 9/10/2021 2:07:06 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"

//MACROS
#define GPIO_PIN_INPUT	0
#define GPIO_PIN_OUTPUT	1

#define GPIO_PORT_INPUT		0x00
#define GPIO_PORT_OUTPUT	0xff


#define GPIO_PIN_HIGH 1
#define GPIO_PIN_LOW  0

#define PORT_HIGH 0xff
#define PORT_LOW  0x00

#define  MAX_PORT 3
#define MAX_PIN 7

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7


typedef enum {
	SUCCESS,
	FAIL,
} GPIO_state_t;

typedef enum{
	GPIO_A = 0,
	GPIO_B,
	GPIO_C,
	GPIO_D
}GPIO_port_name_t;




typedef struct{
	GPIO_port_name_t			port_name;
	uint8						pins_dir[8];
	uint8						pins_select[8];
}GPIO_port_config_t;

//initialize functions 

GPIO_state_t GPIO_init_pin(GPIO_port_name_t reg , uint8 pin , uint8 dir);
void GPIO_init_port(GPIO_port_name_t reg , uint8 dir);
void GPIO_init_port_set_mask(GPIO_port_name_t reg , uint8 mask);
void GPIO_init_port_clear_mask(GPIO_port_name_t reg , uint8 mask);

//write functions 

GPIO_state_t GPIO_write_pin(GPIO_port_name_t reg , uint8 pin , uint8 data);
GPIO_state_t GPIO_toggle_pin(GPIO_port_name_t reg , uint8 pin);
void GPIO_write_port(GPIO_port_name_t reg , uint8 data);
void GPIO_port_set_mask(GPIO_port_name_t reg , uint8 mask);
void GPIO_port_clear_mask(GPIO_port_name_t reg , uint8 mask);


//read functions 
uint8 GPIO_read_pin(GPIO_port_name_t reg , uint8 pin);
uint8 GPIO_read_port(GPIO_port_name_t reg);

//PULL up and PULL down internal resistors
 
GPIO_state_t GPIO_enable_pull_up_res(GPIO_port_name_t reg , uint8 pin);
GPIO_state_t GPIO_disable_pull_up_res(GPIO_port_name_t reg , uint8 pin);
void GPIO_disable_all_pull_up_res();
void GPIO_enable_all_pull_up_res();
#endif /* GPIO_H_ */

//ERROR MACROS

#define NOT_VALID_PORT(port) ((port > MAX_PORT)||(port < 0))
#define NOT_VALID_PIN(pin)   ((pin > MAX_PIN)  ||(pin < 0))
#define NOT_VALID_DIR(dir)   ((dir != GPIO_PIN_INPUT) && (dir != GPIO_PIN_OUTPUT))
#define PIN_IS_OUTPUT(reg , pin) (GET_BIT(reg , pin) == GPIO_PIN_OUTPUT)	
#define NOT_VALID_PIN_CODE	  255