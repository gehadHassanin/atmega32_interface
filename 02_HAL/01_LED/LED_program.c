/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  LED_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  LED
 *
 */
 
// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "LED_interface.h"


error_t LED_Init(LED_t *pLed)
{
	error_t errorState = noError;
	
	errorState = DIO_SetPinDirection(pLed->portName, pLed->pinNumber, OUTPUT);
	
	if (ACTIVE_LOW == pLed->activeState)
	{
		errorState = DIO_SetPinValue(pLed->portName, pLed->pinNumber, HIGH);
	}
	
	return errorState;
}

error_t LED_On(LED_t *pLed)
{
	error_t errorState = noError;
	
	if (pLed != NULL)
	{
		if (ACTIVE_HIGH == pLed->activeState)
		{
			errorState = DIO_SetPinValue(pLed->portName, pLed->pinNumber, HIGH); 
			
		}else if (ACTIVE_LOW == pLed->activeState)
		{
			errorState = DIO_SetPinValue(pLed->portName, pLed->pinNumber, LOW);
			
		}else
        {
			errorState = functionParameterError;
		}			

	}else
	{
		errorState = functionParameterError;
	}

	return errorState;
}

error_t LED_Off(LED_t *pLed)
{
	error_t errorState = noError;
	
	if (pLed != NULL)
	{
		if (ACTIVE_HIGH == pLed->activeState)
		{
			errorState = DIO_SetPinValue(pLed->portName, pLed->pinNumber, LOW); 
			
		}else if (ACTIVE_LOW == pLed->activeState)
		{
			errorState = DIO_SetPinValue(pLed->portName, pLed->pinNumber,HIGH);
			
		}else
        {
			errorState = functionParameterError;
		}			

	}else
	{
		errorState = functionParameterError;
	}

	return errorState;
}

error_t LED_Toggle(LED_t *pLed)
{
	error_t errorState = noError;
	
	if (pLed != NULL)
	{
		errorState = DIO_TogglePinValue(pLed->portName, pLed->pinNumber);
		
	}else
	{
		errorState = functionParameterError;
	}
		
	return errorState;
}

