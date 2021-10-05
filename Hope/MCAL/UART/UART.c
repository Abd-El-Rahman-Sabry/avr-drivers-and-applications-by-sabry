/*
 *	UART.c
 *
 *	Created: 9/21/2021 12:27:05 AM
 *  Author: Abd-El-Rahman Sabry
 */ 

#include "UART.h"


static void (*uart_tx_callback)(void);
static void (*uart_rx_callback)(void);


void UART_init()
{
	//Set Baud Rate
	UBRRH = BAUD_CALC>>8;
	UBRRL = BAUD_CALC;
	
	//SET SPEED MODE
	#if (SPEED_MODE == DOUBLE_SPEED)
		SET_BIT(UCSRA , U2X);
	#elif (SPEED_MODE == NORMAL_SPEED)
		CLEAR_BIT(UCSRA , U2X);
	#endif
	
	//Enable Receiver and transmitter
	SET_BIT(UCSRB , RXEN);
	SET_BIT(UCSRB , TXEN);
	
	//Set synchronization mode 
		#if (SYNCH_MODE == ASYNCH || SYNCH_MODE == SYNCH)
			WRITE_BIT(UCSRC , UMSEL , SYNCH_MODE);
		#else
			# warning  "Not valid value for SYNCH_MODE. SYNCH_MODE will be set to ASYNCH "
			SET_BIT(UCSRC , UMSEL);
		#endif
	
	  /***********************************************************************/
	 // Building the UART FARAME											//
	//									                                   //
   /***********************************************************************/
	
	//PARITY MODE
	#if (PARITY_MODE == 0 || PARITY_MODE == 2 || PARITY_MODE == 3)
		WRITE_BIT(UCSRC , UPM0, GET_BIT(PARITY_MODE , 0));
		WRITE_BIT(UCSRC , UPM1, GET_BIT(PARITY_MODE , 1));
	#else
		# warning  "Not valid value for PARITY_MODE. N_DATA_BITS will be set to ODD_PARITY " 
		SET_BIT(UCSRC , UPM0);
		SET_BIT(UCSRC , UPM1);
	#endif	
	
	//STOP BITS
	#if (N_STOP_BITS == TWO_STOP_BITS || N_STOP_BITS == ONE_STOP_BIT)
		WRITE_BIT(UCSRC , USBS, N_STOP_BITS);
	#else
		# warning  "Not valid value for N_STOP_BITS. N_DATA_BITS will be set to 1 stop bit " 
		WRITE_BIT(UCSRC , USBS, 0);
	#endif
	// DATA BITS
	#if (N_DATA_BITS >= 0 && N_DATA_BITS <= 3) || (N_DATA_BITS == 7)
		WRITE_BIT(UCSRC , UCSZ0, GET_BIT(N_DATA_BITS , 0));
		WRITE_BIT(UCSRC , UCSZ1, GET_BIT(N_DATA_BITS , 1));
		WRITE_BIT(UCSRB , UCSZ2, GET_BIT(N_DATA_BITS , 2));
	#else
		# warning  "Not valid value for N_DATA_BITS. N_DATA_BITS will be set to 8-bits data" 
				SET_BIT(UCSRC , UCSZ0);
				SET_BIT(UCSRC , UCSZ1);
				CLEAR_BIT(UCSRB , UCSZ2);
	#endif
	/************************** END OF BUILDING THE DATA FRAME *******************************************************/
}


void UART_send_byte(uint8 data)
{
	while (!GET_BIT(UCSRA , UDRE));
	UDR = data;
}
uint8 UART_receive_byte()
{
	while (!GET_BIT(UCSRA , RXC));
	return UDR;
}


void UART_send_byte_NOBLOCK(uint8 data)
{
	if (CHECK_BIT(UCSRA , UDRE));
		UDR = data;
}
uint8 UART_receive_byte_NOBLOCK(uint8 *pdata)
{
	if(CHECK_BIT(UCSRA , RXC))
	{
		*pdata = UDR;
		return UART_DATA_RECEIVED;
	}
	return UART_NO_DATA_RECEIVED;
}

void UART_rx_interrupt_enable()
{
	SET_BIT(UCSRB , RXCIE);
}
void UART_rx_interrupt_disable()
{
	CLEAR_BIT(UCSRB , RXCIE);
}

void UART_tx_interrupt_enable()
{
	SET_BIT(UCSRB , TXCIE);
}
void UART_tx_interrupt_disable()
{
	CLEAR_BIT(UCSRB , TXCIE);
}

void UART_tx_set_callback(void (*txCallback)(void))
{
	if(txCallback != NULLPTR)
	{
		uart_tx_callback = txCallback;
	}
}
void UART_rx_set_callback(void (*rxCallback)(void))
{
	if(rxCallback != NULLPTR)
	{
		uart_rx_callback = rxCallback;
	}
}
void UART_send_byte_direct(uint8 data)
{
	UDR = data;
}

uint8 UART_receive_byte_direct(void)
{
	return UDR;
}

ISR(USART_RXC_vect)
{
	if(uart_rx_callback != NULLPTR)
	{
		uart_rx_callback();
	}
}

ISR(USART_TXC_vect)
{
		if(uart_tx_callback != NULLPTR)
		{
			uart_tx_callback();
		}
}