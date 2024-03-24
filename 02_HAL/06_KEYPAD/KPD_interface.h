/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  KPD_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Keypad 
 *
 */

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define MAX_COLUMNS  (4)
#define MAX_ROWS     (4)

#define KPD_NOT_PRESSED (0xff)

/**
*  @Note  : !portName --> {PORTA, PORTB, PORTC, PORTD}  
*           !pinNumber --> {PIN0, PIN1.....PIN7}
*/
typedef struct {
	
	port_t portName;
	pin_t pinNumber;
}keypadPin_t;


/****************************************************@data Type****************************************
*  @name         : KEYPAD_t
*  @intilization : KEYPAD_t myKeypad = {{{PORTC, PIN0}, {PORTC, PIN1}, {PORTC, PIN2}, {PORTC, PIN3}},
*                                       {{PORTC, PIN4}, {PORTC, PIN5}, {PORTC, PIN6}, {PORTC, PIN7}}, 4, 4};
*/
typedef struct {
	
	keypadPin_t KPD_colArr[MAX_COLUMNS];
	keypadPin_t KPD_rowArr[MAX_ROWS];
	uint8_t KPD_columnsNumber;
	uint8_t KPD_rowsNumber;
}KEYPAD_t;


/**
*  @breif          : function used to set configration of bin to work correctly
*  @param  pKeypad : pointer to variable from @KEYPAD_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @KEYPAD_t data type must be intilized
*  @Note           : this function must be used to all keypad used in project
*/
error_t KEYPAD_Init(KEYPAD_t *pKeypad);


/**
*  @breif                    : function used to return character pressed 
*  @param  pKeypad           : pointer to variable from @KEYPAD_t data type
*  @param pReturn_getPressed : pointer to variable from @uin8_t  data type to return character pressed 
*  @param pKeypad_buttonsArr : two dimensional array to store keypad character
*  @return error_t           : !noError --> if function passed parameter is Correct
*                              !functionParameterError --> if function passed parameter is Wrong
*  @preCondition             : !variable from @KEYPAD_t data type must be intilized
*                              !variable from @uin8_t data type must be intilized to return character pressed  
*/
error_t KEYPAD_GetPressed(KEYPAD_t *pKeypad, uint8_t pKeypad_buttonsArr[MAX_ROWS][MAX_COLUMNS], uint8_t *pReturn_getPressed);

#endif /* KPD_INTERFACE_H_ */
