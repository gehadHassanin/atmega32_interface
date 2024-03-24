/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  CLCD_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  CLCD
 *
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

typedef enum{
	
	LOW_NIBBLE,
	HIGH_NIBBLE		
}Nibble_t;


typedef enum{
	
	LCD_8_BIT_MODE,
	LCD_4_BIT_MODE	
}LCD_BitMode_t;


/****************************************************@data Type****************************************
*  @name         : LCD_t
*  @intilization : LCD_t lcd = {LCD_8_BIT_MODE, PORTA, PORTB, PIN0, PIN1, PIN2,HIGH_NIBBLE};
*  @Note         : !bitMode --> {LCD_8_BIT_MODE, LCD_4_BIT_MODE}  
*                  !dataPortName --> {PORTA, PORTB, PORTC, PORTD} 
*                  !controlPortName --> {PORTA, PORTB, PORTC, PORTD} 
*                  !RsControlPinNumber --> {PIN0, PIN1......PIN7}
*                  !RwControlPinNumber --> {PIN0, PIN1......PIN7}
*                  !EnControlPinNumber --> {PIN0, PIN1......PIN7}
*                  !nibbleOfFourBitMode --> {HIGH_NIBBLE, LOW_NIBBLE}
*/
typedef struct{
	
	LCD_BitMode_t bitMode;
	port_t dataPortName;
	port_t controlPortName;
	pin_t RsControlPinNumber;
	pin_t RwControlPinNumber;
	pin_t EnControlPinNumber;
    Nibble_t nibbleOfFourBitMode;		
}LCD_t;


/**
*  @breif          : function used to set configration of bin to work correctly and intilization of bit mode(8 or 4)
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*  @Note           : this function must be used to all Lcd used in project
*/
error_t LCD_Init(LCD_t *pLcd);


/**
*  @breif          : function used to send character to lcd
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @param  data    : character which will send to lcd
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*/
error_t LCD_SendChar(LCD_t *pLcd, uint8_t data);


/**
*  @breif          : function used to send string to lcd
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @param  strData : pointer to string which will send to lcd
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*/
error_t LCD_SendString(LCD_t *pLcd, uint8_t *strData);



/**
*  @breif          : function used to send number to lcd
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @param  number  : number which will send to lcd
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*/
error_t LCD_SendNumber(LCD_t *pLcd, sint32_t number);


/**
*  @breif          : function used to send float number to lcd
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @param  data    : float number which will send to lcd
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*/
error_t LCD_SendFloatNumber(LCD_t *pLcd, float32_t floatNumber);


/**
*  @breif          : function used to clear screen of lcd
*  @param  pLcd    : pointer to variable from @LCD_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LCD_t data type must be intilized
*/
error_t ClearScreen(LCD_t *pLcd);

#endif /* CLCD_INTERFACE_H_ */
