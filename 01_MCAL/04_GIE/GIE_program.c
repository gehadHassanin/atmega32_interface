/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   GIE_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  GIE 
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_private.h"

void GIE_InterruptEnable(void)
{
	SET_BIT(SREG_REG, SREG_I);	
}

void GIE_InterruptDisable(void)
{
	CLR_BIT(SREG_REG, SREG_I);	
}