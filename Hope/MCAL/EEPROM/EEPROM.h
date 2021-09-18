/*
 * EEPROM.h
 *
 * Created: 9/18/2021 12:44:35 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_


uint8 EEPROM_read(uint16 address);
void EEPROM_write(uint8 data , uint16 address);



#endif /* EEPROM_H_ */