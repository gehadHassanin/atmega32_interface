/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   SPI_config.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  SPI
 *
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/** 
*  >> Spi Interrupt Enable
*  @Options:
*           1- DISABLE
*           2- ENABLE
*/
#define SPI_INTERRUPT_CONTROL   DISABLE

/** 
*  >> Spi Enable
*  @Options:
*           1- DISABLE
*           2- ENABLE
*/
#define SPI_STATE   ENABLE

/** 
*   >> Spi Data Order
*   @Options:
*           1- LSB_TX_FIRST
*           2- MSB_TX_FIRST
*/
#define SPI_DATA_ORDER   MSB_TX_FIRST


/** 
*   >> Set Clock Polarity
*   @Options:
*           1- RISING_AT_LEADING_EDGE_FALLING_AT_TRAILING_EDGE
*           2- FALLING_AT_LEADING_EDGE_RISING_AT_TRAILING_EDGE
*/
#define SPI_CLOCK_POLARITY   RISING_AT_LEADING_EDGE_FALLING_AT_TRAILING_EDGE

/** 
*   >> Set Clock Phase
*   @Options:
*           1- SAMPLE_AT_LEADING_EDGE_SETUP_AT_TRAILING_EDGE
*           2- SETUP_AT_LEADING_EDGE_SAMPLE_AT_TRAILING_EDGE
*/
#define SPI_CLOCK_PHASE     SAMPLE_AT_LEADING_EDGE_SETUP_AT_TRAILING_EDGE

/** 
*   >> Clock Rate Select
*   @Options:
*           1- FREEQ_DIVIDED_BY_2  
*           2- FREEQ_DIVIDED_BY_4
*           3- FREEQ_DIVIDED_BY_8
*           4- FREEQ_DIVIDED_BY_16
*           5- FREEQ_DIVIDED_BY_32
*           6- FREEQ_DIVIDED_BY_64
*           7- FREEQ_DIVIDED_BY_128
*/
#define SPI_CLOCK_RATE_SELECT    FREEQ_DIVIDER_BY_64 

#define SPI_TIMEOUT_COUNT  (3000UL)

 #endif // SPI_CONFIG_H_