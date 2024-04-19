/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   SPI_private.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  SPI
 *
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPCR *((volatile uint8_t*) 0x2D)
#define SPCR_SPR0  (0)
#define SPCR_SPR1  (1)
#define SPCR_CPHA  (2)
#define SPCR_CPOL  (3)
#define SPCR_MSTR  (4)
#define SPCR_DORD  (5)
#define SPCR_SPE   (6)
#define SPCR_SPIE  (7)

#define SPSR *((volatile uint8_t*) 0x2E)
#define SPSR_SPI2X (0)
#define SPSR_WCOL  (6)
#define SPSR_SPIF  (7)

#define SPDR *((volatile uint8_t*) 0x2F)

/*Data direction register*/
#ifndef DDRA_REG
#define DDRA_REG       *((volatile uint8_t*) 0x3A)
#endif

#ifndef DDRB_REG
#define DDRB_REG       *((volatile uint8_t*) 0x37)
#endif

#ifndef DDRC_REG
#define DDRC_REG       *((volatile uint8_t*) 0x34)
#endif

#ifndef DDRD_REG
#define DDRD_REG       *((volatile uint8_t*) 0x31)
#endif

#define DISABLE (0)
#define ENABLE  (1)

#define LSB_TX_FIRST (0)
#define MSB_TX_FIRST (1)

#define RISING_AT_LEADING_EDGE_FALLING_AT_TRAILING_EDGE  (0)
#define FALLING_AT_LEADING_EDGE_RISING_AT_TRAILING_EDGE  (1)

#define SAMPLE_AT_LEADING_EDGE_SETUP_AT_TRAILING_EDGE   (0)
#define SETUP_AT_LEADING_EDGE_SAMPLE_AT_TRAILING_EDGE   (1)


#define FREEQ_DIVIDED_BY_2    (0)
#define FREEQ_DIVIDED_BY_4    (1) 
#define FREEQ_DIVIDED_BY_8    (2)
#define FREEQ_DIVIDED_BY_16   (3)
#define FREEQ_DIVIDED_BY_32   (4)
#define FREEQ_DIVIDED_BY_64   (5)
#define FREEQ_DIVIDED_BY_128  (6)


#define ISR(ID) void __vector_ID (void) __attribute__ ((signal)) ;\
                void __vector_ID (void)
				
				
static void SPI_Enable_Helper(void);
static void SPI_InterruptControl_Helper(void);
static void SPI_SetDataOrder_Helper(void);
static void SPI_SetClockPolarity_Helper(void);
static void SPI_SetClockPhase_Helper(void);
static void SPI_SelectClockRate_Helper(void);
				
#endif // SPI_PRIVATE_H_
