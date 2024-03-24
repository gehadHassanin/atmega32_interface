/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  BUZ_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Buzzer
 *
 */
 
// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "BUZ_interface.h"


error_t BUZ_Init(BUZ_t *pBuzzer)
{
	error_t errorState = noError;
	
	errorState = DIO_SetPinDirection(pBuzzer->portName, pBuzzer->pinNumber, OUTPUT);
	
	if (ACTIVE_LOW == pBuzzer->activeState)
	{
		errorState = DIO_SetPinValue(pBuzzer->portName, pBuzzer->pinNumber, HIGH);
	}
	
	return errorState;
}

error_t BUZ_On(BUZ_t *pBuzzer)
{
	error_t errorState = noError;
	
	if (pBuzzer != NULL)
	{
		if (ACTIVE_HIGH == pBuzzer->activeState)
		{
			errorState = DIO_SetPinValue(pBuzzer->portName, pBuzzer->pinNumber, HIGH); 
			
		}else if (ACTIVE_LOW == pBuzzer->activeState)
		{
			errorState = DIO_SetPinValue(pBuzzer->portName, pBuzzer->pinNumber, LOW);
			
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

error_t BUZ_Off(BUZ_t *pBuzzer)
{
	error_t errorState = noError;
	
	if (pBuzzer != NULL)
	{
		if (ACTIVE_HIGH == pBuzzer->activeState)
		{
			errorState = DIO_SetPinValue(pBuzzer->portName, pBuzzer->pinNumber, LOW); 
			
		}else if (ACTIVE_LOW == pBuzzer->activeState)
		{
			errorState = DIO_SetPinValue(pBuzzer->portName, pBuzzer->pinNumber,HIGH);
			
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

error_t BUZ_Toggle(BUZ_t *pBuzzer)
{
	error_t errorState = noError;
	
	if (pBuzzer != NULL)
	{
		errorState = DIO_TogglePinValue(pBuzzer->portName, pBuzzer->pinNumber);
		
	}else
	{
		errorState = functionParameterError;
	}
		
	return errorState;
}

