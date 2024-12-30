/*
 * LCD.c
 *
 * Created: 9/17/2021 6:18:07 PM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "LCD.h"



#if		LCD_CURRENT_MODE == LCD_4BIT_MODE_SAME_PORT
static inline void latch()
{
	GPIO_write_pin(LCD_DATA_PORT , EN , HIGH);
	_delay_ms(2);
	GPIO_write_pin(LCD_DATA_PORT , EN , LOW);
	_delay_ms(2);
}
static void lcd_write_command(uint8 command)
{

	GPIO_write_pin(LCD_DATA_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_DATA_PORT , RS , LCD_COMMAND_SELECT);

	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(command , 4));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(command , 5));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(command , 6));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(command , 7));
	
	latch();
	
	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(command , 0));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(command , 1));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(command , 2));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(command , 3));
	
	latch();
	
}

static void lcd_write_data(uint8 data)
{

	GPIO_write_pin(LCD_DATA_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_DATA_PORT , RS , LCD_DATA_SELECT);

	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(data , 4));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(data , 5));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(data , 6));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(data , 7));
	
	latch();
	
	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(data , 0));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(data , 1));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(data , 2));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(data , 3));
	
	latch();
	
}

void LCD_Init()
{
	GPIO_init_pin(LCD_DATA_PORT , RS , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , EN , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , RW , GPIO_PIN_OUTPUT);
	
	GPIO_init_pin(LCD_DATA_PORT , DB4 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB5 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB6 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB7 , GPIO_PIN_OUTPUT);
	_delay_ms(15);
	lcd_write_command(0x33);
	_delay_us(100);
	lcd_write_command(0x32);
	_delay_us(100);
	lcd_write_command(0x28);
	_delay_us(100);
	lcd_write_command(0x01);
	_delay_ms(2);
	lcd_write_command(0x02);
	_delay_ms(2);
	lcd_write_command(0x0C);
	_delay_us(100);
}

#elif	LCD_CURRENT_MODE == LCD_4BIT_MODE_DIFFERENT_PORT
static inline void latch()
{
	GPIO_write_pin(LCD_CONTROL_PORT , EN , HIGH);
	_delay_ms(2);
	GPIO_write_pin(LCD_CONTROL_PORT , EN , LOW);
	_delay_ms(2);
}
static void lcd_write_command(uint8 command)
{

	GPIO_write_pin(LCD_CONTROL_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_CONTROL_PORT , RS , LCD_COMMAND_SELECT);

	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(command , 4));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(command , 5));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(command , 6));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(command , 7));
	
	latch();
	
	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(command , 0));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(command , 1));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(command , 2));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(command , 3));
	
	latch();
	
}

static void lcd_write_data(uint8 data)
{

	GPIO_write_pin(LCD_CONTROL_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_CONTROL_PORT , RS , LCD_DATA_SELECT);

	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(data , 4));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(data , 5));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(data , 6));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(data , 7));
	
	latch();
	
	GPIO_write_pin(LCD_DATA_PORT , DB4 , GET_BIT(data , 0));
	GPIO_write_pin(LCD_DATA_PORT , DB5 , GET_BIT(data , 1));
	GPIO_write_pin(LCD_DATA_PORT , DB6 , GET_BIT(data , 2));
	GPIO_write_pin(LCD_DATA_PORT , DB7 , GET_BIT(data , 3));
	
	latch();
	
}

void LCD_Init()
{
	GPIO_init_pin(LCD_CONTROL_PORT , RS , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_CONTROL_PORT , EN , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_CONTROL_PORT , RW , GPIO_PIN_OUTPUT);
	
	GPIO_init_pin(LCD_DATA_PORT , DB4 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB5 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB6 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_DATA_PORT , DB7 , GPIO_PIN_OUTPUT);
	_delay_ms(15);
	lcd_write_command(0x33);
	_delay_us(100);
	lcd_write_command(0x32);
	_delay_us(100);
	lcd_write_command(0x28);
	_delay_us(100);
	lcd_write_command(0x01);
	_delay_ms(2);
	lcd_write_command(0x02);
	_delay_ms(2);
	lcd_write_command(0x0C);
	_delay_us(100);
}


#elif	LCD_CURRENT_MODE == LCD_8BIT_MODE


static inline void latch()
{
	GPIO_write_pin(LCD_CONTROL_PORT , EN , HIGH);
	_delay_ms(2);
	GPIO_write_pin(LCD_CONTROL_PORT , EN , LOW);
	_delay_ms(2);
}
static void lcd_write_command(uint8 command)
{

	GPIO_write_pin(LCD_CONTROL_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_CONTROL_PORT , RS , LCD_COMMAND_SELECT);
	GPIO_write_port(LCD_DATA_PORT ,command);
	latch();
}

static void lcd_write_data(uint8 data)
{

	GPIO_write_pin(LCD_CONTROL_PORT , RW , LCD_WRITE);
	GPIO_write_pin(LCD_CONTROL_PORT , RS , LCD_DATA_SELECT);
	GPIO_write_port(LCD_DATA_PORT , data);
	latch();
}

void LCD_Init()
{
	GPIO_init_pin(LCD_CONTROL_PORT , RS , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_CONTROL_PORT , EN , GPIO_PIN_OUTPUT);
	GPIO_init_pin(LCD_CONTROL_PORT , RW , GPIO_PIN_OUTPUT);
	GPIO_init_port(LCD_DATA_PORT , GPIO_PORT_OUTPUT);
	
	_delay_ms(15);
	lcd_write_command(0x38);
	_delay_us(100);
	lcd_write_command(0x0C);
	_delay_us(100);
	lcd_write_command(0x01);
	_delay_ms(2);
	lcd_write_command(0x02);
	_delay_ms(2);

}

#endif



void LCD_write_char(uint8 c)
{
	if(c > 127 || c < 1)
		return;

	lcd_write_data(c);
}


void LCD_clear()
{
	lcd_write_command(0x01);
	_delay_ms(2);
}
void LCD_write_string(sint8 *str)
{
	uint8 c = 0;
	while ( str[c] )
	{
		LCD_write_char(str[c++]);
	}
}

void LCD_go_to(uint8 row , uint8 col)
{
	if(row == 1)
	{
		if(col < MAX_COL)
		{
			lcd_write_command((0x80+col));
		}
	}
	else if(row == 2)
	{
		if(col < MAX_COL)
		{
			lcd_write_command((0xC0+col));
		}
	}
}
void LCD_write_number(sint32 n)
{
	uint8 i = 0 , j , digits[10];
	if(n < 0)
	{
		n = -n;
		lcd_write_data('-');
	}
		
	if(n == 0)
		lcd_write_data('0');

	else {
		while(n)
		{
			digits[i] = (uint8)(n%10 + '0');
			n = n / 10;
			i++;
		}
		for(j = i ; j>0 ; j--)
		{
			lcd_write_data(digits[j-1]);
		}
	}
}
void LCD_clear_next_chars(uint8 n)
{
	for(uint8 i = 0 ; i < n ; i++)
		LCD_write_char(' ');
}
void LCD_string_at(uint8 row , uint8 col , uint8* str)
{
	LCD_go_to(row , col);
	LCD_write_string(str);
}