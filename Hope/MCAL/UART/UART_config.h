/*
 * UART_config.h
 *
 * Created: 9/21/2021 12:27:34 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/******		UART CONFIG FILE	*******/

#define		BAUD_RATE		9600	

#define		SPEED_MODE		NORMAL_SPEED
#define		CPU_F			_8_MHZ
#define		SYNCH_MODE		ASYNCH
#define		PARITY_MODE		NO_PARITY
#define		N_DATA_BITS		_8_BITS
#define		N_STOP_BITS		ONE_STOP_BIT


/*************		Values Of Config Parameters	****************/

// SPEED MODE

#define DOUBLE_SPEED 8
#define NORMAL_SPEED 16
#define SYNCH_SPEED	 2
/********************************/

// CPU Frequency CPU_F

#define _1_MHZ	1000000UL
#define _4_MHZ	4000000UL
#define _8_MHZ	8000000UL
#define _16_MHZ 16000000UL

/********************************/

// Synchronization Mode

#define ASYNCH	0
#define SYNCH	1

/********************************/

// Number of data bits

#define _5_BITS		0
#define _6_BITS		1
#define _7_BITS		2
#define _8_BITS		3
#define _9_BITS		7

/********************************/

// PARITY Mode

#define ODD_PARITY	3
#define EVEN_PARITY	2
#define NO_PARITY	0

/********************************/

// Stop Bits 

#define TWO_STOP_BITS	1
#define ONE_STOP_BIT	0

/********************************/

#endif /* UART_CONFIG_H_ */