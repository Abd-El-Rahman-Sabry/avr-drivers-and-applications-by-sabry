/*
 * button.h
 *
 * Created: 9/21/2021 2:33:15 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../../MCAL/GPIO/GPIO.h"
#include "../Keys_config.h"




typedef enum{
	Button_pull_up = 0,
	Button_pull_down = 1
}Button_Sense;




typedef struct {
	Button_Sense sense;
	Button_event evt;
	void (*callback)(void);
	Button_state current_state;
	GPIO_port_name_t port;
	uint8 pin;
}Button;
void Button_config(Button *btn , GPIO_port_name_t port_name , uint8 pin, Button_event btn_event , void (*btn_callback)(void) , Button_Sense sense);
void Button_listen(Button *btn);

#endif /* BUTTON_H_ */