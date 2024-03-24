/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SW_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Switch
 *
 */

#ifndef SW_INTERFACE_H_
#define SW_INTERFACE_H_

typedef enum {
	
	EXT_PULL_UP, // External pull up resistor
    INT_PULL_UP, // Internal pull up resistor
	PULL_DOWN   // pull down resistor
}SW_connectionType_t;

typedef enum {
	
	SW_NOT_PRESSED,
	SW_PRESSED
}switchState_t;


/****************************************************@data Type****************************************
*  @name         : SWITCH_t
*  @intilization : SWITCH_t mySwitch = {PORTA, PIN0, INT_PULL_UP};
*  @Note         : !portName --> {PORTA, PORTB, PORTC, PORTD}  
*                  !pinNumber --> {PIN0, PIN1.....PIN7}
*                  !pullState --> {EXT_PULL_UP, INT_PULL_UP,PULL_DOWN} 
*/
typedef struct {
	
	port_t portName;
	pin_t pinNumber;
	SW_connectionType_t pullState;
}SWITCH_t;


/**
*  @breif          : function used to set configration of bin to work correctly
*  @param  pSwitch : pointer to variable from @SWITCH_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @SWITCH_t data type must be intilized
*  @Note           : this function must be used to all Switch used in project
*/
error_t SWITCH_Init(SWITCH_t *pSwitch);


/**
*  @breif               : function used to return state of switch (pressed or not_pressed)
*  @param pSwitch       : pointer to variable from @SWITCH_t data type
*  @param pPressedState : pointer to variable from @switchState_t data type to return pressed state in it 
*  @return error_t      : !noError --> if function passed parameter is Correct
*                         !functionParameterError --> if function passed parameter is Wrong
*  @preCondition        : !variable from @SWITCH_t data type must be intilized
*                         !variable from @switchState_t data type must be intilized to return pressed state in it  
*  @Note                : this function must be used to all Switch used in project
*/
error_t SWITCH_GetPressed(SWITCH_t *pSwitch, switchState_t *pPressedState); 

#endif /* SW_INTERFACE_H_ */
