#ifndef STD_TYPES_H_
#define STD_TYPES_H_

//Standard data types
typedef unsigned char        uint8_t;
typedef unsigned short       uint16;
typedef unsigned long        uint32_t;
typedef unsigned long long   uint64_t;

typedef signed  char         sint8_t;
typedef signed  short        sint16_t;
typedef signed  long         sint32_t;
typedef signed  long long    sint64_t;

typedef float                float32_t;
typedef double               float64_t;
typedef long double          float128_t;

typedef enum {
	
	functionParameterError,
	noError,
	TimeoutError,
	BusyError
}error_t;

#define OK  1
#define NOK 0

#define IDEL   (1)
#define BUSY   (0)

#define NULL 0
#define _4_BITS   (4)

#endif // STD_TYPES_H_INCLUDED
