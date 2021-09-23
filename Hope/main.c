/*
 * Hope.c
 *
 * Created: 9/9/2021 10:27:08 PM
 * Author : Abd-El-Rahman Sabry
 */ 

#include "MCAL/GPIO/GPIO.h"
#include "MCAL/INT/EXT_INT.h"
#include "MCAL/TIMER/TIMER.h"
#include "HAL/LCD/LCD.h"
#include "MCAL/ADC/ADC.h"
#include "HAL/LM35/LM35.h"
#include "HAL/Button/button.h"
#include "MCAL/UART/UART.h"

uint16 x = 0;
uint16 y = 0;

void button_event(){
	x++;
}

int main(void)
{

	
	//GPIO_enable_pull_up_res(GPIO_A, PIN_2);
	
	//Initialize LCD for debugging
	LCD_Init();
	UART_init();
	UART_tx_interrupt_enable();
	UART_rx_interrupt_enable();
	LCD_write_string("NOF CLICKS");
	Button button1,button2;
	GPIO_init_pin(GPIO_D , PIN_0 , GPIO_PIN_INPUT);
	GPIO_init_pin(GPIO_D , PIN_1 , GPIO_PIN_OUTPUT);
	GPIO_init_pin(GPIO_A , PIN_1 , GPIO_PIN_OUTPUT);

	Button_config(&button1 , GPIO_A , PIN_2 , ON_KEY_DOWN , button_event , Button_pull_up);
	Button_config(&button2 , GPIO_D , PIN_2 , ON_KEY_UP , button_event , Button_pull_down);
	uint8 read_data;
	while (1) 
    {
		read_data = UART_receive_byte();
		if(read_data == 'A')
			GPIO_toggle_pin(GPIO_A,PIN_1);
		Button_listen(&button1);
		Button_listen(&button2);
		LCD_go_to(2 , 0);	
		LCD_write_number(x);
	}
}

