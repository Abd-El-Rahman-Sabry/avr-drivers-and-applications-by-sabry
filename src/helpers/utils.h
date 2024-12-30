/*
 * utils.h
 *
 * Created: 9/10/2021 12:15:43 AM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef UTILS_H_
#define UTILS_H_

//MACROS FOR PIN

#define WRITE_BIT(reg , bit , data)	(  reg  =  (reg& ~(1<<bit))  | (data<<bit)  )
#define GET_BIT(reg , bit)		    ( ((reg)&(1<<bit))>>bit  )
#define CHECK_BIT(reg , bit)		((reg) & (1<<bit) )
#define TOGGLE_BIT(reg , bit)		(  reg  ^= (1<<bit)  )
#define SET_BIT(reg , bit)			(  reg  |= (1<<bit)  )
#define CLEAR_BIT(reg , bit)		(  reg  &=~(1<<bit)  )

//MACROS FOR PORTS AND REGISTERS

#define INIT_PORT(reg , dir)		(  reg = dir         )
#define WRITE_PORT(reg , data)		(  reg = data        )
#define PORT_SET_MASK(reg , mask)	(  reg |= (mask)     )
#define PORT_CLEAR_MASK(reg ,mask)	(  reg &=~(mask)     )



#define PORT_MASK(reg , clr , set)  (  reg = (reg&~(clr))|(set))



#define SET_REG(reg)				(  reg = 0xff        )
#define CLEAR_REG(reg)				(  reg = 0x00        )
#define TOGGLE_REG(reg)				(  reg ^=0xff		 )

//LOWER NIBBLE MACROS	(0 - 3)

#define GET_LOWER(reg)				(  reg &   0x0f      )
#define SET_LOWER_NIBBLE(reg)		(  reg | = 0x0f		 )
#define CLEAR_LOWER_NIBBLE(reg)		(  reg & = 0xf0      )


#define LOWER_NIBBLE_DATA(reg , data) ( reg = (reg&0xf0)|data ) 

//HIGHER NIBBLE MACROS	(4 - 7)

#define GET_HIGHER(reg)				(  (reg&0xf0)>>4    )
#define SET_HIGHER_NIBBLE(reg)		(  reg | =0xf0		)
#define CLEAR_HIGHER_NIBBLE(reg)	(  reg & = 0x0f     )

#define HIGHER_NIBBLE_DATA(reg , data)	(	reg = (reg&0x0f) | (data<<4) )


#define IS_BOOLEAN(x) ((x == 1) || (x == 1))
#endif /* UTILS_H_ */