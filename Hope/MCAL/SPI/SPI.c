/*
 * SPI.c
 *
 * Created: 9/24/2021 4:32:01 AM
 *  Author: Abd-El-Rahman Sabry
 */ 
#include "SPI.h"

static void (*spi_isr)(void);


void SPI_init()
{
	SPI_STATE(SPI_ENABLE);
	
	
	#if (SPI_DATA_ORDER == SPI_MSB || SPI_DATA_ORDER == SPI_LSB )
		WRITE_BIT(SPCR , DORD , SPI_DATA_ORDER);
	#else
		# warning "Unvalid Value for SPI_DATA_ORDER configuration "
		CLEAR_BIT(SPCR , DORD);
	#endif
	
	
	if(SPI_MASTER_SLAVE == SPI_MASTER)
	{
				#if (SPI_MASTER_SLAVE == SPI_MASTER || SPI_MASTER_SLAVE == SPI_SLAVE )
					WRITE_BIT(SPCR , MSTR , SPI_MASTER_SLAVE);
				#else
					# warning "Unvalid Value for SPI_MASTER_SLAVE configuration "
					SET_BIT(SPCR , MSTR);
				#endif
		
		
				#if (SPI_SPEED == SPI_X2_SPEED || SPI_SPEED == SPI_NORMAL_SPEED )
					WRITE_BIT(SPSR , SPI2X , SPI_SPEED);
				#else
					# warning "Unvalid Value for SPI_SPEED configuration "
					CLEAR_BIT(SPSR , SPI2X);
				#endif
		
				#if	(SPI_CLOCK_DIVIDER <= 7 || SPI_CLOCK_DIVIDER >= 0)
					WRITE_BIT(SPCR , SPR0 , GET_BIT(SPI_CLOCK_DIVIDER , 0));
					WRITE_BIT(SPCR , SPR1 , GET_BIT(SPI_CLOCK_DIVIDER , 1));
				#else
					#error "Unvalid SPI_CLOCK_DIVIDER Configuration"
				#endif
		
		
				#if (SPI_CLOCK_POLARITY == SPI_HIGH || SPI_CLOCK_POLARITY == SPI_LOW )
				WRITE_BIT(SPCR , CPOL , SPI_CLOCK_POLARITY);
				#else
				# warning "Unvalid Value for SPI_CLOCK_POLARITY configuration "
				CLEAR_BIT(SPCR , CPOL);
				#endif

				#if (SPI_CLOCK_PHASE == SPI_LEADING || SPI_CLOCK_PHASE == SPI_TRAILING )
				WRITE_BIT(SPCR , CPHA , SPI_CLOCK_POLARITY);
				#else
				# warning "Unvalid Value for SPI_CLOCK_PHASE configuration "
				CLEAR_BIT(SPCR , CPHA);
				#endif
	}
}


void SPI_write(uint8 data)
{
	uint8 flush;
	SPDR = data;
	while(!CHECK_BIT(SPSR , SPIF));
	flush = SPDR;
}

uint8 SPI_read()
{
	SPDR = 0xff;
	while(!CHECK_BIT(SPDR , SPIF));
	return SPDR;
}


void SPI_enable_interrupt()
{
	SET_BIT(SPCR , SPIE);
}
void SPI_disable_interrupt()
{
	CLEAR_BIT(SPCR , SPIE);
}

void SPI_set_callback(void (*callback)(void))
{
	if(!callback)
	{
		spi_isr = callback;
	}
}