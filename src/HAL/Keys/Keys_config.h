/*
 * Keys_config.h
 *
 * Created: 9/26/2021 5:24:29 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef KEYS_CONFIG_H_
#define KEYS_CONFIG_H_

//Set the value of the cooling down time while pressing the key
#define COOL_DOWN_MS 250

typedef enum{
	ON_KEY_DOWN,
	ON_KEY_PRESSED,
	ON_KEY_UP
}Button_event;

typedef enum{
	NOT_PRESSED,
	MAYBE_PRESSED,
	NOT_RELEASED,
	MAYBE_RELEASED
}Button_state;

#endif /* KEYS_CONFIG_H_ */