/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  BUZ_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Buzzer
 *
 */

#ifndef BUZ_INTERFACE_H_
#define BUZ_INTERFACE_H_

 
typedef enum {
	
	ACTIVE_HIGH, // forward bias 
	ACTIVE_LOW  // reverse bias
}BUZ_connectionType_t;

 
/**
*  @name         : BUZ_t
*  @intilization : BUZ_t myBUZ = {PORTA, PIN0, ACTIVE_HIGH};
*  @Note         : !portName --> {PORTA, PORTB, PORTC, PORTD}  
*                  !pinNumber --> {PIN0, PIN1.....PIN7}
*                  !activeState --> {ACTIVE_HIGH, ACTIVE_LOW} 
*/
typedef struct {
	
	port_t portName;
    pin_t pinNumber;
    BUZ_connectionType_t activeState;
}BUZ_t;  


/** 
*  @breif          : function used to set configration of bin to work correctly
*  @param  pBUZ    : pointer to variable from @BUZ_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @BUZ_t data type must be intilized
*  @Note           : this function must be used to all BUZs used in project
*/
error_t BUZ_Init(BUZ_t *pBuzzer);


/** 
*  @breif          : function used to turn On BUZ 
*  @param  pBUZ    : pointer to variable from @BUZ_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @BUZ_t data type must be intilized
*/
error_t BUZ_On(BUZ_t *pBuzzer);


/** 
*  @breif          : function used to turn Off BUZ 
*  @param  pBUZ    : pointer to variable from @BUZ_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @BUZ_t data type must be intilized
*/
error_t BUZ_Off(BUZ_t *pBuzzer);


/** 
*  @breif          : function used to Toggle BUZ [On --> Off] or [Off --> On]
*  @param  pBUZ    : pointer to variable from @BUZ_t data type
*  @return error_t : !noError --> if function passed parameter is Correct
*                    !functionParameterError --> if function passed parameter is Wrong
*  @preCondition   : variable from @BUZ_t data type must be intilized 
*/
error_t BUZ_Toggle(BUZ_t *pBuzzer);

#endif /* BUZ_INTERFACE_H_ */