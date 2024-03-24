/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  LED_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  LED
 *
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

 
typedef enum {
	
	ACTIVE_HIGH, // forward bias 
	ACTIVE_LOW  // reverse bias
}LED_connectionType_t;

 
/****************************************************@data Type****************************************
*  @name         : LED_t
*  @intilization : LED_t myLed = {PORTA, PIN0, ACTIVE_HIGH};
*  @Note         : !portName --> {PORTA, PORTB, PORTC, PORTD}  
*                  !pinNumber --> {PIN0, PIN1.....PIN7}
*                  !activeState --> {ACTIVE_HIGH, ACTIVE_LOW} 
*/
typedef struct {
	
	port_t portName;
    pin_t pinNumber;
    LED_connectionType_t activeState;
}LED_t;  


/**
*  @breif          : function used to set configration of bin to work correctly
*  @param  pLed    : pointer to variable from @LED_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LED_t data type must be intilized
*  @Note           : this function must be used to all leds used in project
*/
error_t LED_Init(LED_t *pLed);


/** 
*  @breif          : function used to turn On led 
*  @param  pLed    : pointer to variable from @LED_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LED_t data type must be intilized
*/
error_t LED_On(LED_t *pLed);


/** 
*  @breif          : function used to turn Off led 
*  @param  pLed    : pointer to variable from @LED_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LED_t data type must be intilized
*/
error_t LED_Off(LED_t *pLed);


/** 
*  @breif          : function used to Toggle led [On --> Off] or [Off --> On]
*  @param  pLed    : pointer to variable from @LED_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @LED_t data type must be intilized 
*/
error_t LED_Toggle(LED_t *pLed);

#endif /* LED_INTERFACE_H_ */