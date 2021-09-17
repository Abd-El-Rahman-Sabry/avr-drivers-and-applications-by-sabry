/*
 * LCD_configh.h
 *
 * Created: 9/17/2021 6:17:26 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define LCD_4BIT_MODE_SAME_PORT 0
#define LCD_4BIT_MODE_DIFFERENT_PORT 1
#define LCD_8BIT_MODE 2


/*********************************MODE SELECTION************************************/

#define LCD_CURRENT_MODE LCD_8BIT_MODE

/**********************************************************************************/


/***** 4BIT SAME PORT MODE ***/



#if   LCD_CURRENT_MODE == LCD_4BIT_MODE_SAME_PORT
	
	#define LCD_DATA_PORT GPIO_C
	#define DB4 0
	#define DB5 1
	#define DB6 2
	#define DB7 3
	
	#define RS  4
	#define RW  5
	#define EN  6 

#elif LCD_CURRENT_MODE == LCD_4BIT_MODE_DIFFERENT_PORT
	#define LCD_DATA_PORT		GPIO_C
	#define LCD_CONTROL_PORT	GPIO_C
	#define DB4 0
	#define DB5 1
	#define DB6 2
	#define DB7 3
	
	#define RS  4
	#define RW  5
	#define EN  6
#elif LCD_CURRENT_MODE == LCD_8BIT_MODE
	#define LCD_DATA_PORT		GPIO_C
	#define LCD_CONTROL_PORT	GPIO_D
	
	#define DB0 0
	#define DB1 1
	#define DB2 2
	#define DB3 3
	#define DB4 4
	#define DB5 5
	#define DB6 6
	#define DB7 7
	
	#define RS  0
	#define RW  1
	#define EN  2
#endif


#endif /* LCD_CONFIG_H_ */