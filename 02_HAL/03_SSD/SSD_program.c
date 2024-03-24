/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SSD_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Seven segment disblay
 *
 */
 
// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "SSD_interface.h" 
#include "SSD_private.h"


uint8_t numbers[] = SSD_NUMBERS;

error_t SSD_Init(SSD_t *pSevenSegment)
{
	error_t errorState = noError;
	
	if (pSevenSegment != NULL)
	{
		errorState = DIO_SetPortDirection(pSevenSegment->dataPort, OUTPUT);
		errorState = DIO_SetPinDirection(pSevenSegment->enablePort, pSevenSegment->enablePin, OUTPUT);
		
		if (COMMON_ANODE == pSevenSegment->connection)
		{
			errorState = DIO_SetPortValue(pSevenSegment->dataPort, HIGH);
			
		}else
		{
			/* Do Nothing */
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


error_t SSD_Enable(SSD_t *pSevenSegment)
{
	error_t errorState = noError;
	
	if (pSevenSegment != NULL)
	{
		if (COMMON_CATHODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPinValue(pSevenSegment->enablePort, pSevenSegment->enablePin, LOW);
			
		}else if (COMMON_ANODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPinValue(pSevenSegment->enablePort, pSevenSegment->enablePin, HIGH);
			
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


error_t SSD_Disable(SSD_t *pSevenSegment)
{
	error_t errorState = noError;
	
	if (pSevenSegment != NULL)
	{
		if (COMMON_CATHODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPinValue(pSevenSegment->enablePort, pSevenSegment->enablePin, HIGH);
			
		}else if (COMMON_ANODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPinValue(pSevenSegment->enablePort, pSevenSegment->enablePin, LOW);
			
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


error_t SSD_SendNumber(SSD_t *pSevenSegment, uint8_t number)
{
	error_t errorState = noError;

	if (pSevenSegment != NULL && (number >= 0 && number <= 9))
	{
		if (COMMON_CATHODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPortValue(pSevenSegment->dataPort, numbers[number]);
				
		}else if (COMMON_ANODE == pSevenSegment->commonState)
		{
			errorState = DIO_SetPortValue(pSevenSegment->dataPort, ~(numbers[number]));
			
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
