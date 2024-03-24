 /*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   DIO_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  DIO/GPIO
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IO PIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

error_t DIO_SetPinDirection(port_t portName, pin_t pinNumber, direction_t pinDirection)
{
	error_t Error_State = noError;

	if (pinNumber >= PIN0 && pinNumber <= PIN7)
	{
		if (OUTPUT == pinDirection)
		{
			switch (portName)
			{
				case PORTA :  SET_BIT(DDRA_REG, pinNumber); break;
			    case PORTB :  SET_BIT(DDRB_REG, pinNumber); break;
			    case PORTC :  SET_BIT(DDRC_REG, pinNumber); break;
			    case PORTD :  SET_BIT(DDRD_REG, pinNumber); break;
			    default : Error_State = functionParameterError; 
			}

		}else if (INPUT == pinDirection)
		{
			switch (portName)
			{
				case PORTA : CLR_BIT(DDRA_REG, pinNumber); break;
			    case PORTB : CLR_BIT(DDRB_REG, pinNumber); break;
			    case PORTC : CLR_BIT(DDRC_REG, pinNumber); break;
			    case PORTD : CLR_BIT(DDRD_REG, pinNumber); break;
			    default : Error_State = functionParameterError; 
			}

		}else
		{
			Error_State = functionParameterError;
		}

	}else 
	{
		Error_State = functionParameterError;
	}

	return Error_State;
}


error_t DIO_SetPinValue(port_t portName, pin_t pinNumber, state_t voltageLevel)
{
	error_t Error_State = noError;

	if (pinNumber >= PIN0 && pinNumber <= PIN7)
	{
		if (HIGH == voltageLevel)
		{
			switch (portName)
			{
				case PORTA : SET_BIT(PORTA_REG, pinNumber); break;
			    case PORTB : SET_BIT(PORTB_REG, pinNumber); break;
			    case PORTC : SET_BIT(PORTC_REG, pinNumber); break;
			    case PORTD : SET_BIT(PORTD_REG, pinNumber); break;
			    default : Error_State = functionParameterError; 
			}

		}else if (LOW == voltageLevel)
		{
			switch (portName)
			{
				case PORTA : CLR_BIT(PORTA_REG, pinNumber); break;
			    case PORTB : CLR_BIT(PORTB_REG, pinNumber); break;
			    case PORTC : CLR_BIT(PORTC_REG, pinNumber); break;
			    case PORTD : CLR_BIT(PORTD_REG, pinNumber); break;
			    default : Error_State = functionParameterError; 
			}

		}else
		{
			Error_State = functionParameterError;
		}

	}else 
	{
		Error_State = functionParameterError;
	}

	return Error_State;	
}


error_t DIO_GetPinValue(port_t portName, pin_t pinNumber, uint8_t *pData)
{
	error_t Error_State = noError;

	if (pinNumber >= PIN0 && pinNumber <= PIN7 && pData != NULL)
	{
		switch (portName)
		{
			case PORTA : *pData = GET_BIT(PINA_REG, pinNumber); break;
		    case PORTB : *pData = GET_BIT(PINB_REG, pinNumber); break;
		    case PORTC : *pData = GET_BIT(PINC_REG, pinNumber); break;
		    case PORTD : *pData = GET_BIT(PIND_REG, pinNumber); break;
		    default : Error_State = functionParameterError; 
		}

	}else
	{
		Error_State = functionParameterError;
	}

	return Error_State;	
}

error_t DIO_TogglePinValue(port_t portName, pin_t pinNumber)
{
	error_t Error_State = noError;

	if (pinNumber >= PIN0 && pinNumber <= PIN7)
	{
		switch (portName)
		{
			case PORTA : TOG_BIT(PORTA_REG, pinNumber); break;
		    case PORTB : TOG_BIT(PORTB_REG, pinNumber); break;
		    case PORTC : TOG_BIT(PORTC_REG, pinNumber); break;
		    case PORTD : TOG_BIT(PORTD_REG, pinNumber); break;
		    default : Error_State = functionParameterError;
		}

	}else
	{
		Error_State = functionParameterError;
	}

	return Error_State;
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IO PORT <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

error_t DIO_SetPortDirection(port_t portName, direction_t portDirection)
{
	error_t Error_State = noError;

	switch (portName)
	{
		case PORTA : DDRA_REG = portDirection; break;
		case PORTB : DDRB_REG = portDirection; break;
	    case PORTC : DDRC_REG = portDirection; break;
	    case PORTD : DDRD_REG = portDirection; break;
	    default : Error_State = functionParameterError; 
	}

	return Error_State;
}


error_t DIO_SetPortValue(port_t portName, state_t voltageLevel)
{
	error_t Error_State = noError;

	switch (portName)
	{
		case PORTA : PORTA_REG = voltageLevel; break;
	    case PORTB : PORTB_REG = voltageLevel; break;
	    case PORTC : PORTC_REG = voltageLevel; break;
	    case PORTD : PORTD_REG = voltageLevel; break;
	    default : Error_State = functionParameterError; 
	}

	return Error_State;
}


error_t DIO_GetPortValue(port_t portName, uint8_t *pData)
{
	error_t Error_State = noError;

	if (pData != NULL) 
	{
		switch (portName)
		{
			case PORTA : *pData = PINA_REG; break;
		    case PORTB : *pData = PINB_REG; break;
		    case PORTC : *pData = PINC_REG; break;
		    case PORTD : *pData = PIND_REG; break;
		    default : Error_State = functionParameterError; 
		}

	}else
	{
		Error_State = functionParameterError;
	}

	return Error_State;
}

error_t DIO_TogglePortValue(port_t portName)
{
	error_t Error_State = noError;

	switch (portName)
	{
		case PORTA : PORTA_REG = ~(PORTA_REG); break;
	    case PORTB : PORTB_REG = ~(PORTB_REG); break;
	    case PORTC : PORTC_REG = ~(PORTC_REG); break;
	    case PORTD : PORTD_REG = ~(PORTD_REG); break;
	    default : Error_State = functionParameterError;
	}

	return Error_State;
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IO High Nibble <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

error_t DIO_SetHighNibbleDirection(port_t portName, uint8_t highNibbleDirection)
{
	error_t Error_State = noError;
	highNibbleDirection &= LOW_NIBBLE_MASK;

	switch (portName)
	{
		case PORTA : DDRA_REG &= HIGH_NIBBLE_MASK; DDRA_REG |= highNibbleDirection; break;
	    case PORTB : DDRB_REG &= HIGH_NIBBLE_MASK; DDRB_REG |= highNibbleDirection; break;
	    case PORTC : DDRC_REG &= HIGH_NIBBLE_MASK; DDRC_REG |= highNibbleDirection; break;
	    case PORTD : DDRD_REG &= HIGH_NIBBLE_MASK; DDRD_REG |= highNibbleDirection; break;
     	default : Error_State = functionParameterError; 
	}

	return Error_State;
}

error_t DIO_SetHighNibbleValue(port_t portName, uint8_t voltageLevel)
{
	error_t Error_State = noError;
	voltageLevel &= LOW_NIBBLE_MASK;

	switch (portName)
	{
		case PORTA : PORTA_REG &= HIGH_NIBBLE_MASK; PORTA_REG |= voltageLevel; break;
	    case PORTB : PORTB_REG &= HIGH_NIBBLE_MASK; PORTB_REG |= voltageLevel; break;
	    case PORTC : PORTC_REG &= HIGH_NIBBLE_MASK; PORTC_REG |= voltageLevel; break;
	    case PORTD : PORTD_REG &= HIGH_NIBBLE_MASK; PORTD_REG |= voltageLevel; break;
	    default : Error_State = functionParameterError; 
	}

	return Error_State;	
}

error_t DIO_GetHighNibbleValue(port_t portName, uint8_t *pData)
{
	error_t Error_State = noError;

	if (pData != NULL)
	{
		switch (portName)
		{
			case PORTA : *pData = (PINA_REG >> _4_BITS); break;
		    case PORTB : *pData = (PINB_REG >> _4_BITS); break;
		    case PORTC : *pData = (PINC_REG >> _4_BITS); break;
		    case PORTD : *pData = (PIND_REG >> _4_BITS); break;
		    default : Error_State = functionParameterError; 
		}

	}else
	{
		Error_State = functionParameterError; 
	}

	return Error_State;		
}

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< IO Low Nibble <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

error_t DIO_SetLowNibbleDirection(port_t portName, uint8_t lowNibbleDirection)
{
	error_t Error_State = noError;
	lowNibbleDirection &= HIGH_NIBBLE_MASK;

	switch (portName)
	{
		case PORTA : DDRA_REG &= LOW_NIBBLE_MASK; DDRA_REG |= lowNibbleDirection; break;
	    case PORTB : DDRB_REG &= LOW_NIBBLE_MASK; DDRB_REG |= lowNibbleDirection; break;
	    case PORTC : DDRC_REG &= LOW_NIBBLE_MASK; DDRC_REG |= lowNibbleDirection; break;
	    case PORTD : DDRD_REG &= LOW_NIBBLE_MASK; DDRD_REG |= lowNibbleDirection; break;
	    default : Error_State = functionParameterError; 
	}

	return Error_State;
}


error_t DIO_SetLowNibbleValue(port_t portName, uint8_t voltageLevel)
{
	error_t Error_State = noError;
	voltageLevel &= HIGH_NIBBLE_MASK;

	switch (portName)
	{
		case PORTA : PORTA_REG &= LOW_NIBBLE_MASK; PORTA_REG |= voltageLevel; break;
	    case PORTB : PORTB_REG &= LOW_NIBBLE_MASK; PORTB_REG |= voltageLevel; break;
	    case PORTC : PORTC_REG &= LOW_NIBBLE_MASK; PORTC_REG |= voltageLevel; break;
	    case PORTD : PORTD_REG &= LOW_NIBBLE_MASK; PORTD_REG |= voltageLevel; break;
	    default : Error_State = functionParameterError; 
	}

	return Error_State;
}


error_t DIO_GetLowNibbleValue(port_t portName, uint8_t *pData)
{
	error_t Error_State = noError;

	if (pData != NULL)
	{
		switch (portName)
		{
			case PORTA : PINA_REG &= HIGH_NIBBLE_MASK; *pData = PINA_REG; break;
		    case PORTB : PINB_REG &= HIGH_NIBBLE_MASK; *pData = PINB_REG; break;
		    case PORTC : PINC_REG &= HIGH_NIBBLE_MASK; *pData = PINC_REG; break;
		    case PORTD : PIND_REG &= HIGH_NIBBLE_MASK; *pData = PIND_REG; break;
		    default : Error_State = functionParameterError; 
		}

	}else
	{
		Error_State = functionParameterError; 
	}

	return Error_State;		

}


void DIO_InternalPullUpEnable(void)
{
	CLR_BIT(SFIOR_REG, PUD);
}


void DIO_InternalPullUpDisable(void)
{
	SET_BIT(SFIOR_REG, PUD);
}
