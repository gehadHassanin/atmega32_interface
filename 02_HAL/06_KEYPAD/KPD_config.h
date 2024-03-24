/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  KPD_config.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  Keypad
 *
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_




                                     // c1 ,  c2,  c3, c4
uint8_t keyPad_4x4_buttonsArr[4][4] = {{'7', '8', '9', '/'}, // r1
	                                   {'4', '5', '6', '*'}, // r2
								       {'1', '2', '3', '-'}, // r3
								       {'?', '0', '=', '+'}  // r4
                                      };
								  
								  
                                     // c1 ,  c2,  c3								  
uint8_t keyPad_4x3_buttonsArr[4][3] = {{'7', '8', '9'}, // r1
	                                   {'4', '5', '6'}, // r2
								       {'1', '2', '3'}, // r3
								       {'*', '0', '#'}  // r4
                                      };								  
 
#endif // KPD_CONFIG_H_
