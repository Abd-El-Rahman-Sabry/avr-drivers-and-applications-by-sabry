/*
 * SPI_config.h
 *
 * Created: 9/24/2021 4:31:42 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_
/************************************************************************/

/*                           SPI_CONTROL_PANAL                          */

/************************************************************************/

#define SPI_MASTER_SLAVE		SPI_MASTER

#define SPI_CLOCK_DIVIDER		SPI_F_64 

#define SPI_DATA_ORDER			SPI_MSB

#define SPI_SPEED				SPI_NORMAL_SPEED

#define SPI_CLOCK_POLARITY		SPI_HIGH

#define SPI_CLOCK_PHASE			SPI_LEADING

/**********************************************************************/


//Master or slave
#define SPI_MASTER	1
#define SPI_SLAVE	0

//Data order 
#define SPI_LSB 1
#define SPI_MSB 0

//Speed
#define SPI_NORMAL_SPEED	0
#define SPI_X2_SPEED		1


//Clock Divider 
	//Normal speed 
	#define SPI_F_4		0
	#define SPI_F_16	1
	#define SPI_F_64	2
	#define SPI_F_128	3
	//Double speed
	#define SPI2X_F_2	4
	#define SPI2X_F_8	5
	#define SPI2X_F_32	6
	#define SPI2X_F_64	7

//Clock Polarity
#define SPI_HIGH	1
#define SPI_LOW		0

//Clock Phase 

#define SPI_LEADING		0
#define SPI_TRAILING	1

#endif /* SPI_CONFIG_H_ */