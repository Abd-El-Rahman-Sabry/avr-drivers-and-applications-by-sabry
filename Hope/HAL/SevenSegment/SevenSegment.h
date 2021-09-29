/*
 * SevenSegment.h
 *
 * Created: 9/22/2021 11:02:29 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include "../../MCAL/GPIO/GPIO.h"
//Normal Mode : Port pins mapping 

#define SS_NORMAL_A		0
#define SS_NORMAL_B		1
#define SS_NORMAL_C		2
#define SS_NORMAL_D		3
#define SS_NORMAL_E		4
#define SS_NORMAL_F		5
#define SS_NORMAL_G		6


//BCD Mode : Port pins mapping 

#define SS_BCD_0	0
#define SS_BCD_1	1
#define SS_BCD_2	2
#define SS_BCD_3	3



typedef enum {
	CC_BCD,
	CA_BCD,
	CC_NORMAL,
	CA_NORMAL
} SS_type;

void SevenSegment_init(GPIO_port_name_t port , SS_type mode);
void SevenSegment_write(GPIO_port_name_t port, SS_type mode, uint8 digit);
#endif /* SEVENSEGMENT_H_ */