/*****************************************************
*Author :Moatasem
*Date:   12/10/2018
*Version: v02
*Brief: LCD COMPONENT
*******************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "../../MCAL/GPIO/GPIO.h"
#include <util/delay.h>
#include "LCD_config.h"




#define MAX_COL 16
#define MAX_ROW 2

void LCD_Init();
void LCD_write_char(uint8 c);
void LCD_write_number(uint32 n);
void LCD_clear();
void LCD_write_string(sint8 *str);
void LCD_go_to(uint8 row , uint8 col);
void LCD_clear_next_chars(uint8 n);
#endif