/*
 * SPI.h
 *
 * Created: 9/24/2021 4:31:51 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../../helpers/stdtypes.h"
#include "../../helpers/utils.h"
#include "../../MCAL_REG/mem_map.h"
#include "SPI_config.h"

#define SPI_ENABLE	1
#define SPI_DISABLE 0

#define SPI_STATE(state) WRITE_BIT(SPCR , SPE , state)

void	SPI_init();

void	SPI_write(uint8 data);

uint8	SPI_read();

void	SPI_enable_interrupt();

void	SPI_disable_interrupt();

void	SPI_set_callback(void (*callback)(void));



#endif /* SPI_H_ */