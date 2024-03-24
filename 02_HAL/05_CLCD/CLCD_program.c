/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  CLCD_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  CLCD
 *
 */
 
 // inclue avr lib
#include <util/delay.h>

// include LIB 
#include "STD_TYPES.h" 
#include "BIT_MATH.h"  

// include MCAL layer
#include "DIO_interface.h"

// include HAL layer
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"


error_t LCD_Init(LCD_t *pLcd)
{
	error_t errorState = noError;
	
	if (pLcd != NULL)
	{
		errorState = DIO_SetPinDirection(pLcd->controlPortName, pLcd->RsControlPinNumber, OUTPUT);
		errorState = DIO_SetPinDirection(pLcd->controlPortName, pLcd->RwControlPinNumber, OUTPUT);
		errorState = DIO_SetPinDirection(pLcd->controlPortName, pLcd->EnControlPinNumber, OUTPUT);
		
		if(pLcd->bitMode == LCD_8_BIT_MODE)
		{
			errorState = DIO_SetPortDirection(pLcd->dataPortName, OUTPUT); 
			
			_delay_ms(40);
			
			errorState = LCD_SendCommand(pLcd, LCD_FUNCTION_SET_8_BIT_MODE);
			_delay_ms(1);
			
			errorState = LCD_SendCommand(pLcd, LCD_DISBLAY_ON_CURSOR_OFF);
            _delay_ms(1);	

 		    errorState = LCD_SendCommand(pLcd, LCD_CLEAR_SCREEN);
		    _delay_ms(5);

		    errorState = LCD_SendCommand(pLcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);			
			
		}else if (pLcd->bitMode == LCD_4_BIT_MODE) 
		{
			switch (pLcd->nibbleOfFourBitMode)
			{
				case LOW_NIBBLE  : DIO_SetLowNibbleDirection(pLcd->dataPortName, OUTPUT); break;
				case HIGH_NIBBLE : DIO_SetHighNibbleDirection(pLcd->dataPortName, OUTPUT); break;
				default : errorState = functionParameterError; 
			}
			
			errorState = LCD_SendCommand(pLcd, LCD_RETURN_HOME);
			
			_delay_ms(40);
			
			errorState = LCD_SendCommand(pLcd, LCD_FUNCTION_SET_4_BIT_MODE);
			_delay_ms(1);
			
			errorState = LCD_SendCommand(pLcd, LCD_DISBLAY_ON_CURSOR_OFF);
            _delay_ms(1);	

 		    errorState = LCD_SendCommand(pLcd, LCD_CLEAR_SCREEN);
		    _delay_ms(5);

		    errorState = LCD_SendCommand(pLcd, LCD_ENTRY_MODE_INC_SHIFT_OFF);
			
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


error_t LCD_SendChar(LCD_t *pLcd, uint8_t data)
{
	error_t errorState = noError;

	if (pLcd != NULL)
	{
		errorState = LCD_SendData(pLcd, data);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;		
}


error_t LCD_SendString(LCD_t *pLcd, uint8_t *strData)
{
	error_t errorState = noError;
	uint8_t Iterator = 0;
	
	if (pLcd != NULL)
	{
		for (Iterator; strData[Iterator] != NULL; Iterator++)
		{
			errorState = LCD_SendData(pLcd, strData[Iterator]);
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;	
}


error_t ClearScreen(LCD_t *pLcd)
{
	error_t errorState = noError;
	
	if (pLcd != NULL)
	{
		errorState = LCD_SendCommand(pLcd, LCD_CLEAR_SCREEN);
		_delay_ms(5);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;	
}


error_t LCD_SendNumber(LCD_t *pLcd, sint32_t number)
{
	error_t errorState = noError;
	uint32_t reverseNumber = 0;
	
	if (pLcd != NULL)
	{
		if (number != 0)
	    {
		    if(number < 0)
		    {
		    	errorState = LCD_SendData(pLcd, '-');
		        number *= -1;	
		    }else
		    {
		    	/* Do Nothing */
		    }
		    
		    while (number > 0)
	        {
	        	reverseNumber = reverseNumber * 10 + (number % 10);
	        	number /= 10;
	        }
	        
	        while (reverseNumber > 0)
	        {
	        	number = (reverseNumber % 10);
	        	errorState = LCD_SendData(pLcd, (number + '0'));
	        	reverseNumber /= 10;
	        }
		
	    }else if (number == 0)
	    {
	    	errorState = LCD_SendData(pLcd, '0');
        
	    }
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


error_t LCD_SendFloatNumber(LCD_t *pLcd, float32_t floatNumber) // --------------------> lesa 
{
	error_t errorState = noError;
	sint32_t number = floatNumber;
	
	errorState = LCD_SendNumber(pLcd, number);
	errorState = LCD_SendData(pLcd, ',');
	
	if (number < 0)
	{
		number *= -1;
		floatNumber *= -1;
		
	}else
	{
		/* Do Nothing */
	}
	
	number = (floatNumber - number) * 100;  
	errorState = LCD_SendNumber(pLcd, number);

	return errorState;
}
/**************************************************************Static Function*************************************************************/

static error_t LCD_SendFallingEdgePulse(LCD_t *pLcd)
{
	error_t errorState = noError;
	
	if (pLcd != NULL)
	{
		errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->EnControlPinNumber, HIGH);
		_delay_ms(1);
	    errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->EnControlPinNumber, LOW);
		_delay_ms(1);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}


static error_t LCD_SendCommand(LCD_t *pLcd, uint8_t command)
{
	error_t errorState = noError;
	
	if (pLcd != NULL)
	{
		errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->RsControlPinNumber, LOW);
		errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->RwControlPinNumber, LOW);
		
		if (pLcd->bitMode == LCD_8_BIT_MODE)
		{
			errorState = DIO_SetPortValue(pLcd->dataPortName, command);
			errorState = LCD_SendFallingEdgePulse(pLcd);
			
		}else if (pLcd->bitMode == LCD_4_BIT_MODE)
		{
			switch (pLcd->nibbleOfFourBitMode)
			{
				case LOW_NIBBLE : 
				                    errorState = DIO_SetLowNibbleValue(pLcd->dataPortName, (command >> _4_BITS));
									errorState = LCD_SendFallingEdgePulse(&pLcd);
									errorState = DIO_SetLowNibbleValue(pLcd->dataPortName, command); 
									errorState = LCD_SendFallingEdgePulse(pLcd);
									break;
				case HIGH_NIBBLE :
				                    errorState = DIO_SetHighNibbleValue(pLcd->dataPortName, command); 
									errorState = LCD_SendFallingEdgePulse(&pLcd);
									errorState = DIO_SetHighNibbleValue(pLcd->dataPortName, (command << _4_BITS));
									errorState = LCD_SendFallingEdgePulse(pLcd);
									break;	
                default : errorState = functionParameterError;									
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


static error_t LCD_SendData(LCD_t *pLcd, uint8_t data)
{
	error_t errorState = noError;
	
	if (pLcd != NULL)
	{
		errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->RsControlPinNumber, HIGH);
		errorState = DIO_SetPinValue(pLcd->controlPortName, pLcd->RwControlPinNumber, LOW);
		
		if (pLcd->bitMode == LCD_8_BIT_MODE)
		{
			errorState = DIO_SetPortValue(pLcd->dataPortName, data);
			errorState = LCD_SendFallingEdgePulse(pLcd);
			
		}else if (pLcd->bitMode == LCD_4_BIT_MODE)
		{
			switch (pLcd->nibbleOfFourBitMode)
			{
				case LOW_NIBBLE : 
				                    errorState = DIO_SetLowNibbleValue(pLcd->dataPortName, (data >> _4_BITS));
									errorState = LCD_SendFallingEdgePulse(&pLcd);
									errorState = DIO_SetLowNibbleValue(pLcd->dataPortName, data); 
									errorState = LCD_SendFallingEdgePulse(pLcd);
									break;
				case HIGH_NIBBLE :
				                    errorState = DIO_SetHighNibbleValue(pLcd->dataPortName, data); 
									errorState = LCD_SendFallingEdgePulse(&pLcd);
									errorState = DIO_SetHighNibbleValue(pLcd->dataPortName, (data << _4_BITS));
									errorState = LCD_SendFallingEdgePulse(pLcd);
									break;	
                default : errorState = functionParameterError;									
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
