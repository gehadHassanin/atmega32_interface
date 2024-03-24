/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PORT_program.c   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Gehad Hassanein
 *  Layer  : MCAL
 *  SWC    : PORT
 *
 */ 

#include "STD_TYPES.h"

#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"


void PORT_Init(void)
{
	DDRA_REG = PORTA_DIR;
	DDRB_REG = PORTB_DIR;
	DDRC_REG = PORTC_DIR;
	DDRD_REG = PORTD_DIR;
	
	PORTA_REG = PORTA_INITVAL;
	PORTB_REG = PORTB_INITVAL;
	PORTC_REG = PORTC_INITVAL;
	PORTD_REG = PORTD_INITVAL;	
}