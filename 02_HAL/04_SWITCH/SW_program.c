/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SW_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Switch
 *
 */
 
// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "SW_interface.h" 


error_t SWITCH_Init(SWITCH_t *pSwitch)
{
	error_t errorState = noError; 
	
	if (pSwitch != NULL)
	{
		errorState = DIO_SetPinDirection(pSwitch->portName, pSwitch->pinNumber, INPUT);
		
		if (INT_PULL_UP == pSwitch->pullState)
		{
			errorState = DIO_SetPinValue(pSwitch->portName, pSwitch->pinNumber, HIGH);
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


error_t SWITCH_GetPressed(SWITCH_t *pSwitch, switchState_t *pPressedState)
{
	error_t errorState = noError;
	uint8_t pinValue = LOW;
	
	if (pSwitch != NULL && pPressedState != NULL)
	{
		if (EXT_PULL_UP == pSwitch->pullState || INT_PULL_UP == pSwitch->pullState)
		{
			errorState = DIO_GetPinValue(pSwitch->portName, pSwitch->pinNumber, &pinValue);
			
			if (LOW == pinValue)
			{
				*pPressedState = SW_PRESSED;
				
			}else if (HIGH == pinValue)
			{
				*pPressedState = SW_NOT_PRESSED;
			}
			
		}else if (PULL_DOWN == pSwitch->pullState)
		{
			errorState = DIO_GetPinValue(pSwitch->portName, pSwitch->pinNumber, &pinValue);
			
			if (HIGH == pinValue)
			{
				*pPressedState = SW_PRESSED;
				
			}else if (LOW == pinValue)
			{
				*pPressedState = SW_NOT_PRESSED;
			}
			
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