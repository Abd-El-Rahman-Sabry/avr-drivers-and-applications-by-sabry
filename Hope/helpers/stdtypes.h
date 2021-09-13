/*
 * stdtypes.h
 *
 * Created: 9/9/2021 11:59:43 PM
 *  Author: Abd-El-Rahman Sabry
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_


//Standard Data Types 
typedef		unsigned char			uint8;
typedef		char					sint8;
typedef		unsigned short			uint16;
typedef		short					sint16;
typedef		unsigned int			uint32;
typedef		int						sint32;
typedef		unsigned long long		uint64;
typedef		long long				sint64;
typedef		float					float32;
typedef		double					float64;



//Booleans 
typedef		unsigned char			bool;
#define		TRUE					(1u)
#define		FALSE					(0u)
		
#define		HIGH					(1u)
#define		LOW						(0u)

#define		ONE						(1u)
#define		ZERO					(0u)


//Pointers 
#define		NULLPTR					((void*)0)



#endif /* STDTYPES_H_ */