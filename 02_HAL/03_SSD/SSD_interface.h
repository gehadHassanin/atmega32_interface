/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  SSD_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanien
 *    Layer    :  HAL
 *    SWC      :  Seven segment disblay
 *
 */

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

/* HW commonState :- 
 *                                            ****************                                        ___MC_________________________
 *                                          *                 *_a______________220ohm________________|
 *                                          *                 *                                      |
 *                                          *                 *_b______________220ohm________________|
 *                                          *                 *                                      |
 *                                          *                 *_c______________220ohm________________|
 *                                          *                 *                                      |
 *                                          *                 *_d______________220ohm________________|
 *                                              ***********                                          |
 *                                          *                 * e_______________220ohm_______________|
 *                                          *                 *                                      |
 *                                          *                 *_f______________220ohm________________|
 *                                          *                 *                                      |
 *                                          *                 *_g________________220ohm______________|
 *                                          *                 *                                      |
 *                                          *                 *_common_______________________________|
 *                                            ****************                                       |_____________________________
 *
 *
 */
 
typedef enum {
	
	COMMON_CATHODE,
	COMMON_ANODE
}SSD_connectionType_t;


/****************************************************@data Type****************************************
*  @name         : SSD_t
*  @intilization : SSD_t mySSD = {COMMON_CATHODE, PORTA, PORTB, PIN0} 
*  @Note         : !commonState --> {COMMON_CATHODE, COMMON_ANODE} 
*                  !dataPort --> {PORTA, PORTB, PORTC, PORTD}
*                  !enablePort --> {PORTA, PORTB, PORTC, PORTD}
*                  !enablePin --> {PIN0, PIN1, PIN2.....PIN7}
*/
typedef struct {
	
    SSD_connectionType_t commonState;	
	port_t dataPort;
	port_t enablePort; // port name of common
	pin_t enablePin; // pin number of common	
}SSD_t;


/**
*  @breif               : this function used to set configration of (data pins & common pin) to work correctly
*  @param pSevenSegment : pointer to variable from @SSD_t data type 
*  @return error_t      : !noError --> if function parameter passed is correct
*                         !functionParameterError --> if function parameter passed is wrong
*  @preCondition        : variable from @SSD_t data type must be intilized
*  @Note                : this function must be used to all seven segment used in project
*/
error_t SSD_Init(SSD_t *pSevenSegment);


/**
*  @breif               : this function used to enable seven segment(working)
*  @param pSevenSegment : pointer to variable from @SSD_t data type 
*  @return error_t      : !noError --> if function parameter passed is correct
*                         !functionParameterError --> if function parameter passed is wrong
*  @preCondition        : variable from @SSD_t data type must be intilized
*/
error_t SSD_Enable(SSD_t *pSevenSegment);


/**
*  @breif               : this function used to disable seven segment(not working)
*  @param pSevenSegment : pointer to variable from @SSD_t data type 
*  @return error_t      : !noError --> if function parameter passed is correct
*                         !functionParameterError --> if function parameter passed is wrong
*  @preCondition        : variable from @SSD_t data type must be intilized
*/
error_t SSD_Disable(SSD_t *pSevenSegment);


/**
*  @breif               : this function used to show number on seven segment
*  @param pSevenSegment : pointer to variable from @SSD_t data type
*  @param number        : must be from 0 to 9 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
*  @return error_t      : !noError --> if function parameter passed is correct
*                         !functionParameterError --> if function parameter passed is wrong
*  @preCondition        : variable from @SSD_t data type must be intilized
*/
error_t SSD_SendNumber(SSD_t *pSevenSegment, uint8_t number);

#endif /* SSD_INTERFACE_H_ */
