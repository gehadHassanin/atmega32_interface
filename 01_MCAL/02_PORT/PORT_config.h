/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    PORT_config.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 *  Author : Gehad Hassanein 
 *  Layer  : MCAL
 *  SWC    : PORT
 *
 */ 
 
#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

/**
*   ---> Set direction of pins
*   Options :-
*               1- OUTPUT
*               2- INPUT
*/

#define PORTA_PIN0_DIR   INPUT  
#define PORTA_PIN1_DIR   INPUT 
#define PORTA_PIN2_DIR   INPUT 
#define PORTA_PIN3_DIR   INPUT  
#define PORTA_PIN4_DIR   INPUT  
#define PORTA_PIN5_DIR   INPUT 
#define PORTA_PIN6_DIR   INPUT 
#define PORTA_PIN7_DIR   INPUT 



#define PORTB_PIN0_DIR   INPUT  
#define PORTB_PIN1_DIR   INPUT 
#define PORTB_PIN2_DIR   INPUT 
#define PORTB_PIN3_DIR   INPUT  
#define PORTB_PIN4_DIR   INPUT  
#define PORTB_PIN5_DIR   INPUT 
#define PORTB_PIN6_DIR   INPUT 
#define PORTB_PIN7_DIR   INPUT 



#define PORTC_PIN0_DIR   INPUT  
#define PORTC_PIN1_DIR   INPUT 
#define PORTC_PIN2_DIR   INPUT 
#define PORTC_PIN3_DIR   INPUT  
#define PORTC_PIN4_DIR   INPUT  
#define PORTC_PIN5_DIR   INPUT 
#define PORTC_PIN6_DIR   INPUT 
#define PORTC_PIN7_DIR   INPUT 



#define PORTD_PIN0_DIR   INPUT  
#define PORTD_PIN1_DIR   INPUT 
#define PORTD_PIN2_DIR   INPUT 
#define PORTD_PIN3_DIR   INPUT  
#define PORTD_PIN4_DIR   INPUT  
#define PORTD_PIN5_DIR   INPUT 
#define PORTD_PIN6_DIR   INPUT 
#define PORTD_PIN7_DIR   INPUT 





/**
*  --> Set initialize value of pins
*  @Options :-
               $In case pin is input :
*                                      1- INPUT_PULL_UP
*                                      2- INPUT_FLOATING
*              $In case pin is output :
*                                      1- OUTPUT_HIGH
*                                      2- OUTPUT_LOW
*
*/

#define PORTA_PIN0_INITVAL   INPUT_FLOATING  
#define PORTA_PIN1_INITVAL   INPUT_FLOATING 
#define PORTA_PIN2_INITVAL   INPUT_FLOATING 
#define PORTA_PIN3_INITVAL   INPUT_FLOATING  
#define PORTA_PIN4_INITVAL   INPUT_FLOATING  
#define PORTA_PIN5_INITVAL   INPUT_FLOATING 
#define PORTA_PIN6_INITVAL   INPUT_FLOATING 
#define PORTA_PIN7_INITVAL   INPUT_FLOATING 



#define PORTB_PIN0_INITVAL   INPUT_FLOATING  
#define PORTB_PIN1_INITVAL   INPUT_FLOATING 
#define PORTB_PIN2_INITVAL   INPUT_FLOATING 
#define PORTB_PIN3_INITVAL   INPUT_FLOATING  
#define PORTB_PIN4_INITVAL   INPUT_FLOATING  
#define PORTB_PIN5_INITVAL   INPUT_FLOATING 
#define PORTB_PIN6_INITVAL   INPUT_FLOATING 
#define PORTB_PIN7_INITVAL   INPUT_FLOATING 



#define PORTC_PIN0_INITVAL   INPUT_FLOATING  
#define PORTC_PIN1_INITVAL   INPUT_FLOATING 
#define PORTC_PIN2_INITVAL   INPUT_FLOATING 
#define PORTC_PIN3_INITVAL   INPUT_FLOATING  
#define PORTC_PIN4_INITVAL   INPUT_FLOATING  
#define PORTC_PIN5_INITVAL   INPUT_FLOATING 
#define PORTC_PIN6_INITVAL   INPUT_FLOATING 
#define PORTC_PIN7_INITVAL   INPUT_FLOATING 



#define PORTD_PIN0_INITVAL   INPUT_FLOATING  
#define PORTD_PIN1_INITVAL   INPUT_FLOATING 
#define PORTD_PIN2_INITVAL   INPUT_FLOATING 
#define PORTD_PIN3_INITVAL   INPUT_FLOATING  
#define PORTD_PIN4_INITVAL   INPUT_FLOATING  
#define PORTD_PIN5_INITVAL   INPUT_FLOATING 
#define PORTD_PIN6_INITVAL   INPUT_FLOATING 
#define PORTD_PIN7_INITVAL   INPUT_FLOATING 


#endif
