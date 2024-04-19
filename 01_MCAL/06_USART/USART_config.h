/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   USART_config.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  USART
 *
 */

 #ifndef USART_CONFIG_H_
 #define USART_CONFIG_H_

#define USART_BAUD_RATE (9600)

/** 
*  RX Complete Interrupt Enable or Disable
*  Options: 
*          1- DISABLE
*          2- ENABLE
*/
#define USART_RX_COMPLETED_INTERRUPT DISABLE

/** 
*  TX Complete Interrupt Enable or Disable
*  Options: 
*          1- DISABLE
*          2- ENABLE
*/
#define USART_TX_COMPLETED_INTERRUPT DISABLE

/** 
*  USART Data Register Empty Interrupt Enable or Disable
*  Options: 
*          1- DISABLE
*          2- ENABLE
*/
#define USART_DATA_REGISTER_EMPTY DISABLE

/** 
*  Receiver Enable
*  Options: 
*          1- DISABLE
*          2- ENABLE
*/
#define USART_RX_STATE ENABLE

/** 
*  Transmitter Enable
*  Options: 
*          1- DISABLE
*          2- ENABLE
*/
#define USART_TX_STATE ENABLE

/** 
*  sets the number of data bits(Character Size) in a frame the receiver and transmitter  
*  Options: 
*           1- CHARACTER_SIZE_5_BIT
*           2- CHARACTER_SIZE_6_BIT
*           3- CHARACTER_SIZE_7_BIT             
*           4- CHARACTER_SIZE_8_BIT            
*           5- CHARACTER_SIZE_9_BIT
*/
#define USART_CHARACTER_SIZE CHARACTER_SIZE_8_BIT

/** 
*  selects between Asynchronous and Synchronous mode of operation.
*  Options: 
*          1- ASYNCHRONOUS_1X
*          2- ASYNCHRONOUS_2X
*          3- SYNCHRONOUS 
*/
#define USART_MODE_SELECT ASYNCHRONOUS_1X

/** 
*  enable and set type of parity generation
*  Options: 
*          1- DISABLE
*          2- EVEN_PARITY
*          3- ODD_PARITY 
*/            
#define USART_PARITY_MODE DISABLE

/** 
*  selects the number of Stop Bits
*  Options: 
*          1- STOP_BIT_1_BIT
*          2- STOP_BIT_2_BIT
*/
#define USART_STOP_BIT_SELECT STOP_BIT_1_BIT


/**
*  Options:
*           1- TX_AT_RISING_EDGE_RX_AT_FALLING_EDGE
*           2- TX_AT_FALLING_EDGE_RX_AT_RISING_EDGE
*/
#define USART_CLOCK_POLARITY TX_AT_RISING_EDGE_RX_AT_FALLING_EDGE

 #endif // USART_CONFIG_H_