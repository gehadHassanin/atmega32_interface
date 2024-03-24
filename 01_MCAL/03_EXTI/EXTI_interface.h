/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   EXTI_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  EXTI
 *
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_



typedef enum{
	
	EXTI_INT0,
	EXTI_INT1,
	EXTI_INT2	
}sourceOfInterrupt_t;

typedef enum{
	
	EXTI_LOW_LEVEL,
	EXTI_ON_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE
}senseControl_t;

typedef enum{
	
	EXTI_DISABLE,
	EXTI_ENABLE
}InterruptState_t;


/****************************************************@data Type****************************************
*  @name         : EXTI_t
*  @intilization : EXTI_t myExternalInterrupt = {EXTI_INT0, EXTI_FALLING_EDGE, EXTI_ENABLE};
*  @Note         : !interruptNumber --> {EXTI_INT0, EXTI_INT1, EXTI_INT2} 
*                  !senseMode --> {EXTI_LOW_LEVEL, EXTI_ON_CHANGE, EXTI_FALLING_EDGE, EXTI_RISING_EDGE}
*                  !stateOfInterrupt --> {EXTI_DISABLE, EXTI_ENABLE} 
*/
typedef struct{
	
	sourceOfInterrupt_t interruptNumber;
	senseControl_t senseMode;
	InterruptState_t  stateOfInterrupt;	
}EXTI_t;


/**
*  @breif                     : function used to to initiate the External Interrupt initial state 
*  @param  pExternalInterrupt : pointer to variable from @EXTI_t data type
*  @return error_t            : !noError --> if function passed parameter is Correct
*                               !functionParameterError --> if function passed parameter is Wrong
*  @preCondition              : variable from @EXTI_t data type must be intilized
*/ 
error_t EXTI_Init(EXTI_t *pExternalInterrupt);


/**
*  @breif                 : this function used to Enable periphral interrupt Enable(PIE)
*  @param interruptNumber : interruptNumber --> {EXTI_INT0, EXTI_INT1, EXTI_INT2}
*  @return error_t        : !noError --> if function passed parameter is Correct
*                           !functionParameterError --> if function passed parameter is Wrong
*/
error_t EXTI_InterruptEnable(sourceOfInterrupt_t interruptNumber);


/**
*  @breif                 : this function used to Disable periphral interrupt Enable(PIE)
*  @param interruptNumber : interruptNumber --> {EXTI_INT0, EXTI_INT1, EXTI_INT2}
*  @return error_t        : !noError --> if function passed parameter is Correct
*                           !functionParameterError --> if function passed parameter is Wrong
*/
error_t EXTI_InterruptDisable(sourceOfInterrupt_t interruptNumber);


/**
*  @breif                 : this function used to set sense mode at run time
*  @param interruptNumber : interruptNumber --> {EXTI_INT0, EXTI_INT1, EXTI_INT2}
*  @senseMode             : senseMode --> {EXTI_LOW_LEVEL, EXTI_ON_CHANGE, EXTI_FALLING_EDGE, EXTI_RISING_EDGE}
*  @return error_t        : !noError --> if function passed parameter is Correct
*                           !functionParameterError --> if function passed parameter is Wrong
*/
error_t EXTI_SetSenseControl(sourceOfInterrupt_t interruptNumber, senseControl_t senseMode);



/**
*  @breif                 : this function used to set call back function
*  @param interruptNumber : interruptNumber --> {EXTI_INT0, EXTI_INT1, EXTI_INT2}
*  @pFunction             : pointer to the function which will execute after interrupted happened  
*  @return error_t        : !noError --> if function passed parameter is Correct
*                           !functionParameterError --> if function passed parameter is Wrong
*/
error_t EXTI_SetCallBackFunction(sourceOfInterrupt_t interruptNumber, void(*pFunction)(void));

#endif // EXTI_INTERFACE_H_
