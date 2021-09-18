/*
 * mem_map.h
 *
 * Created: 9/10/2021 1:30:38 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef MEM_MAP_H_
#define MEM_MAP_H_
#include "../helpers/stdtypes.h"

#define VECTOR(n) __vector_##n
/* DIO_Registers */
#define DDRA (*(volatile uint8*)0x3A)
#define DDRB (*(volatile uint8*)0x37)
#define DDRC (*(volatile uint8*)0x34)
#define DDRD (*(volatile uint8*)0x31)

#define PINA (*(volatile uint8*)0x39)
#define PINB (*(volatile uint8*)0x36)
#define PINC (*(volatile uint8*)0x33)
#define PIND (*(volatile uint8*)0x30)

#define PORTA (*(volatile uint8*)0x3B)
#define PORTB (*(volatile uint8*)0x38)
#define PORTC (*(volatile uint8*)0x35)
#define PORTD (*(volatile uint8*)0x32)


//******************* External INTERRUPTS *****************************


/*

Interrupt Sensing Control (ISC)

 0 0 ----> LOW LEVEL

 0 1 ----> Logical Change (at any edge)

 1 0 ----> Falling edge 

 1 1 ----> Rising Edge


*/

//Interrupt vectors
#define GICR (*((volatile uint8*)0x5B))
#define EN_INT0 6
#define EN_INT1 7
#define EN_INT2 5

#define MCUCR (*((volatile uint8*)0x55))
	#define ISC00	0
	#define ISC01	1
	#define ISC10	2
	#define ISC11	3
	#define SM0		4
	#define SM1		5
	#define SM2		6
#define MCUCSR (*((volatile uint8*)0x54))
	#define ISC2 6
// External Interrupt vectors
#define INT0_vect __vector_1
#define INT1_vect __vector_2
#define INT2_vect __vector_3



//******************* TIMERS ****************************

#define TIMSK (*((volatile uint8*)0x59))
	#define TOIE0  0
	#define OCIE0  1
	#define TOIE1  2
	#define OCIE1B 3
	#define OCIE1A 4
	#define TICIE1 5
	#define TOIE2  6
	#define OCIE2  7       

#define TIFR (*((volatile uint8*)0x58))

//TIMER0 REGISERS 

#define TCCR0 (*((volatile uint8*)0x53))
	#define CS00  0
	#define CS01  1
	#define CS02  2
	#define WGM00 6
	#define WGM01 3
	#define COM00 4
	#define COM01 5
	#define FOC00 7
	
	
#define TCNT0 (*((volatile uint8*)0x52))
#define OCR0  (*((volatile uint8*)0x5C))

//Timer1 registers

#define TCCR1A (*((volatile uint8*)0x4F)) 
	#define COM1A1 7 
	#define COM1A0 6 
	#define COM1B1 5 
	#define COM1B0 4
	#define FOC1A  3 
	#define FOC1B  2 
	#define WGM11  1 
	#define WGM10  0
	
#define TCCR1B (*((volatile uint8*)0x4E)) 
	#define ICNC1 7
	#define ICES1 6
	#define WGM13 4
	#define WGM12 3
	#define CS12  2
	#define CS11  1
	#define CS10  0
	
	
#define TCNT1H (*((volatile uint8*)0x4D)) 
#define TCNT1L (*((volatile uint8*)0x4C))
#define OCR1AH (*((volatile uint8*)0x4B))
#define OCR1AL (*((volatile uint8*)0x4A))
#define OCR1BH (*((volatile uint8*)0x49)) 
#define OCR1BL (*((volatile uint8*)0x48))
#define ICR1H  (*((volatile uint8*)0x47))
#define ICR1L  (*((volatile uint8*)0x46))     


//Timer interrupt vectors
#define TIMER2_COMP   __vector_4 
#define TIMER2_OVF    __vector_5
#define TIMER1_CAPT   __vector_6
#define TIMER1_COMPA  __vector_7
#define TIMER1_COMPB  __vector_8
#define TIMER1_OVF    __vector_9
#define TIMER0_COMP   __vector_10
#define TIMER0_OVF    __vector_11



/*********************************** ADC **********************************/
#define ADMUX (*(volatile uint8*)0x27)
	#define MUX0  0
	#define MUX1  1
	#define MUX2  2
	#define MUX3  3
	#define MUX4  4
	#define ADLAR 5
	#define REFS0 6
	#define REFS1 7

#define ADCSRA (*(volatile uint8*)0x26)
	#define ADPS0 0
	#define ADPS1 1
	#define ADPS2 2
	#define ADIE  3
	#define ADIF  4
	#define ADATE 5
	#define ADSC  6
	#define ADEN  7

#define ADCL (*(volatile uint8*)0x24)
#define ADCH (*(volatile uint8*)0x25)


//Special function io register 

#define SFIOR (*(volatile uint8*)0x50)
#define ADTS2	7
#define ADTS1	6
#define ADTS0	5
#define ACME	3	 
#define PUD		2
#define PSR2	1 
#define PSR10	0

// ADC interrupt vector
#define ADC_vect __vector_16


//EEPROM

#define EEPCR	(*(volatile uint8*)0x3C)
	#define EERIE	3
	#define EEMWE	2
	#define EEWE	1
	#define EERE	0
	
#define EEDR	(*(volatile uint8*)0x3D)
#define EEARL	(*(volatile uint8*)0x3E)
#define EEARH	(*(volatile uint8*)0x3F)

#define EE_READY_vect __vector_17
	
/*interrupt functions*/

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)


#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))


#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)

#endif /* MEM_MAP_H_ */