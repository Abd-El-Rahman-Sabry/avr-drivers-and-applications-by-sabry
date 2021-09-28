/*
 * Keypad.h
 *
 * Created: 9/22/2021 11:01:45 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "../../../MCAL/GPIO/GPIO.h"
#include "../Keys_config.h"

typedef struct {
	Button_event evt;
	void (*callback)(uint8);
	Button_state current_state;
	GPIO_port_name_t port;
}Keypad;
void Keypad_config(Keypad *keypad , GPIO_port_name_t port ,Button_event evnt, void (*callback)(uint8));
uint8 Keypad_listen(Keypad *keypad);


#endif /* KEYPAD_H_ */