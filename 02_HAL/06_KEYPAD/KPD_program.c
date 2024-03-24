/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  KPD_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Keypad
 *
 */
 
#include <util/delay.h>

// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"



error_t KEYPAD_Init(KEYPAD_t *pKeypad)
{
	error_t errorState = noError;
	uint8_t Iterator = 0;
	
	if (pKeypad != NULL)
	{
		for (Iterator = 0; Iterator < pKeypad->KPD_columnsNumber; Iterator++)
		{
			errorState = DIO_SetPinDirection(pKeypad->KPD_colArr[Iterator].portName, pKeypad->KPD_colArr[Iterator].pinNumber, OUTPUT);
		}
		
		for (Iterator = 0; Iterator < pKeypad->KPD_columnsNumber; Iterator++)
		{
			errorState = DIO_SetPinValue(pKeypad->KPD_colArr[Iterator].portName, pKeypad->KPD_colArr[Iterator].pinNumber, HIGH);
		}
		
		for (Iterator = 0; Iterator < pKeypad->KPD_rowsNumber; Iterator++)
		{
			errorState = DIO_SetPinDirection(pKeypad->KPD_rowArr[Iterator].portName, pKeypad->KPD_rowArr[Iterator].pinNumber, INPUT);
		}
		
		for (Iterator = 0; Iterator < pKeypad->KPD_rowsNumber; Iterator++)
		{
			errorState = DIO_SetPinValue(pKeypad->KPD_rowArr[Iterator].portName, pKeypad->KPD_rowArr[Iterator].pinNumber, HIGH);
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


error_t KEYPAD_GetPressed(KEYPAD_t *pKeypad, uint8_t pKeypad_buttonsArr[MAX_ROWS][MAX_COLUMNS], uint8_t *pReturn_getPressed)
{
	error_t errorState = noError;
	uint8_t column;
	uint8_t row;
	uint8_t pinValue;
	
	*pReturn_getPressed = KPD_NOT_PRESSED; 

	if (pKeypad != NULL && pKeypad_buttonsArr != NULL && pReturn_getPressed != NULL)
	{
		for (column = 0; column < pKeypad->KPD_columnsNumber; column++)
	    {
	    	errorState = DIO_SetPinValue(pKeypad->KPD_colArr[column].portName, pKeypad->KPD_colArr[column].pinNumber, LOW);
	    	
	    	for (row = 0; row < pKeypad->KPD_rowsNumber; row++)
	    	{
	    		errorState = DIO_GetPinValue(pKeypad->KPD_rowArr[row].portName, pKeypad->KPD_rowArr[row].pinNumber, &pinValue);
	    		
	    		if (LOW == pinValue)
	    		{
	    			_delay_ms(50);
	    			
	    			errorState = DIO_GetPinValue(pKeypad->KPD_rowArr[row].portName, pKeypad->KPD_rowArr[row].pinNumber, &pinValue);
	    			
	    			if (LOW == pinValue)
	    			{
	    				*pReturn_getPressed = pKeypad_buttonsArr[row][column];
	    			}
					
	    			errorState = DIO_GetPinValue(pKeypad->KPD_rowArr[row].portName, pKeypad->KPD_rowArr[row].pinNumber, &pinValue);	
					
					while (LOW == pinValue)
					{
						errorState = DIO_GetPinValue(pKeypad->KPD_rowArr[row].portName, pKeypad->KPD_rowArr[row].pinNumber, &pinValue);
					}
	    		}
		    }
			
			errorState = DIO_SetPinValue(pKeypad->KPD_colArr[column].portName, pKeypad->KPD_colArr[column].pinNumber, HIGH);
	    }
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}