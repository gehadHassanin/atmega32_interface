/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   EXTI_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  EXTI 
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

void (*pCallBackFunction[NUM_OF_INTERRPUT_SOURCE])(void) = {{NULL}};

error_t EXTI_Init(EXTI_t *pExternalInterrupt)
{
	error_t errorState = noError;
	
	if (pExternalInterrupt->interruptNumber == EXTI_INT0)
	{
		switch (pExternalInterrupt->senseMode)
		{
			case EXTI_LOW_LEVEL    : CLR_BIT(MCUCR_REG, MCUCR_ISC00); CLR_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_ON_CHANGE    : SET_BIT(MCUCR_REG, MCUCR_ISC00); CLR_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCR_REG, MCUCR_ISC00); SET_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCR_REG, MCUCR_ISC00); SET_BIT(MCUCR_REG, MCUCR_ISC01); break;
			default : errorState = functionParameterError;
		}
		
		
	}else if (pExternalInterrupt->interruptNumber == EXTI_INT1)
	{
		
		switch (pExternalInterrupt->senseMode)
		{
			case EXTI_LOW_LEVEL    : CLR_BIT(MCUCR_REG, MCUCR_ISC10); CLR_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_ON_CHANGE    : SET_BIT(MCUCR_REG, MCUCR_ISC10); CLR_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCR_REG, MCUCR_ISC10); SET_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCR_REG, MCUCR_ISC10); SET_BIT(MCUCR_REG, MCUCR_ISC11); break;
			default : errorState = functionParameterError;
		}
		
	}else if (pExternalInterrupt->interruptNumber == EXTI_INT2)
	{
	    switch (pExternalInterrupt->senseMode)
		{
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCSR_REG, MCUCSR_ISC2); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCSR_REG, MCUCSR_ISC2); break;
			default : errorState = functionParameterError;
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	
	if (pExternalInterrupt->stateOfInterrupt == EXTI_DISABLE)
	{
	    switch (pExternalInterrupt->interruptNumber)
	    {
	    	case EXTI_INT0 : CLR_BIT(GICR_REG, GICR_INT0); break; 
	    	case EXTI_INT1 : CLR_BIT(GICR_REG, GICR_INT1); break; 
	    	case EXTI_INT2 : CLR_BIT(GICR_REG, GICR_INT2); break; 
	    }
		
	}else if (pExternalInterrupt->stateOfInterrupt == EXTI_ENABLE)
	{
        switch (pExternalInterrupt->interruptNumber)
	    {
	    	case EXTI_INT0 : SET_BIT(GICR_REG, GICR_INT0); break; 
	    	case EXTI_INT1 : SET_BIT(GICR_REG, GICR_INT1); break; 
	    	case EXTI_INT2 : SET_BIT(GICR_REG, GICR_INT2); break; 
	    }
	    	
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


error_t EXTI_InterruptEnable(sourceOfInterrupt_t interruptNumber)
{
	error_t errorState = noError;
	
    switch (interruptNumber)
	{
		case EXTI_INT0 : SET_BIT(GICR_REG, GICR_INT0); break; 
		case EXTI_INT1 : SET_BIT(GICR_REG, GICR_INT1); break; 
		case EXTI_INT2 : SET_BIT(GICR_REG, GICR_INT2); break; 
		default : errorState = functionParameterError;
	}
	
	return errorState;
}


error_t EXTI_InterruptDisable(sourceOfInterrupt_t interruptNumber)
{
	error_t errorState = noError;
	
	switch (interruptNumber)
	{
		case EXTI_INT0 : CLR_BIT(GICR_REG, GICR_INT0); break; 
		case EXTI_INT1 : CLR_BIT(GICR_REG, GICR_INT1); break; 
		case EXTI_INT2 : CLR_BIT(GICR_REG, GICR_INT2); break; 
		default : errorState = functionParameterError;
	}
		
	return errorState;
}


error_t EXTI_SetSenseControl(sourceOfInterrupt_t interruptNumber, senseControl_t senseMode)
{
	error_t errorState = noError;

	if (interruptNumber == EXTI_INT0)
	{
		switch (senseMode)
		{
			case EXTI_LOW_LEVEL    : CLR_BIT(MCUCR_REG, MCUCR_ISC00); CLR_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_ON_CHANGE    : SET_BIT(MCUCR_REG, MCUCR_ISC00); CLR_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCR_REG, MCUCR_ISC00); SET_BIT(MCUCR_REG, MCUCR_ISC01); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCR_REG, MCUCR_ISC00); SET_BIT(MCUCR_REG, MCUCR_ISC01); break;
			default : errorState = functionParameterError;
		}
			
	}else if (interruptNumber == EXTI_INT1)
	{
		switch (senseMode)
		{
			case EXTI_LOW_LEVEL    : CLR_BIT(MCUCR_REG, MCUCR_ISC10); CLR_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_ON_CHANGE    : SET_BIT(MCUCR_REG, MCUCR_ISC10); CLR_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCR_REG, MCUCR_ISC10); SET_BIT(MCUCR_REG, MCUCR_ISC11); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCR_REG, MCUCR_ISC10); SET_BIT(MCUCR_REG, MCUCR_ISC11); break;
			default : errorState = functionParameterError;
		}
		
	}else if (interruptNumber == EXTI_INT2)
	{
	    switch (senseMode)
		{
			case EXTI_FALLING_EDGE : CLR_BIT(MCUCSR_REG, MCUCSR_ISC2); break;
			case EXTI_RISING_EDGE  : SET_BIT(MCUCSR_REG, MCUCSR_ISC2); break;
			default : errorState = functionParameterError;
		}
		
	}else
	{
		errorState = functionParameterError;		
	}
		
	return errorState;
}


error_t EXTI_SetCallBackFunction(sourceOfInterrupt_t interruptNumber, void(*pFunction)(void))
{
	error_t errorState = noError;
	
	if (pFunction != NULL && interruptNumber >= EXTI_INT0 && interruptNumber <= EXTI_INT2)
	{
		pCallBackFunction[interruptNumber] = pFunction;
		
	}else
	{
		errorState = functionParameterError;		
	}
	
	return errorState;
}


/*************************************************************ISR Implementation******************************************************/


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if (pCallBackFunction[EXTI_INT0] != NULL)
	{
		(pCallBackFunction[EXTI_INT0])();
		
	}else
	{
		/* Do Nothing */
	}
}


void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (pCallBackFunction[EXTI_INT1] != NULL)
	{
		(pCallBackFunction[EXTI_INT1])();
		
	}else
	{
		/* Do Nothing */
	}
}


void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (pCallBackFunction[EXTI_INT2] != NULL)
	{
		(pCallBackFunction[EXTI_INT2])();
		
	}else
	{
		/* Do Nothing */
	}
}
