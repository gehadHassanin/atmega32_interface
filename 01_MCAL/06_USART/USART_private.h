/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   USART_private.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  USART
 *
 */

#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define UDR *((volatile uint8_t*) 0x2C)

#define UCSRA *((volatile uint8_t*) 0x2B)
#define UCSRA_MPCM (0)
#define UCSRA_U2X  (1)
#define UCSRA_PE   (2)
#define UCSRA_DOR  (3)
#define UCSRA_FE   (4)
#define UCSRA_UDRE (5)
#define UCSRA_TXC  (6)
#define UCSRA_RXC  (7)

#define UCSRB *((volatile uint8_t*) 0x2A)
#define UCSRB_TXB8   (0)
#define UCSRB_RXB8   (1)
#define UCSRB_UCSZ2  (2)
#define UCSRB_TXEN   (3)
#define UCSRB_RXEN   (4)
#define UCSRB_UDRIE  (5)
#define UCSRB_TXCIE  (6)
#define UCSRB_RXCIE  (7)

#define UCSRC *((volatile uint8_t*) 0x40)
#define UCSRC_UCPOL  (0)
#define UCSRC_UCSZ0  (1)
#define UCSRC_UCSZ1  (2)
#define UCSRC_USBS   (3)
#define UCSRC_UPM0   (4)
#define UCSRC_UPM1   (5)
#define UCSRC_UMSEL  (6)
#define UCSRC_URSEL  (7)

#define UBRRH *((volatile uint8_t*) 0x40)
#define UBRRL *((volatile uint8_t*) 0x29)

#define DISABLE (0)
#define ENABLE  (1)

#define CHARACTER_SIZE_5_BIT (0)
#define CHARACTER_SIZE_6_BIT (1)
#define CHARACTER_SIZE_7_BIT (2)
#define CHARACTER_SIZE_8_BIT (3)
#define CHARACTER_SIZE_9_BIT (4) 

#define ASYNCHRONOUS_1X (0)
#define ASYNCHRONOUS_2X (1)
#define SYNCHRONOUS     (2) 

#define EVEN_PARITY (2)
#define ODD_PARITY  (3)

#define STOP_BIT_1_BIT (0)
#define STOP_BIT_2_BIT (1)

#define TX_AT_RISING_EDGE_RX_AT_FALLING_EDGE   (0)
#define TX_AT_FALLING_EDGE_RX_AT_RISING_EDGE   (1)

static void USART_SetCharacterSize_Helper(void);
static void USART_SetParityMode_Helper(void);
static void USART_SetStopBit_Helper(void);
static void USART_SetMode_Helper(void);
static void USART_GetMode_Helper(void);
static void USART_SetBaudRate_Helper(void);
static void USART_SetClockPolarity_Helper(void);
static void USART_TransferEnable_Helper(void);
static void USART_InterruptControl_Helper(void);

#define ATMEGA32_CLK (8000000UL)
#define USART_TIMEOUT_COUNT (30000UL)
#define Calculate_UBRR(divisor, baudRate) ((uint16)((ATMEGA32_CLK / (baudRate * divisor)) - 1))

#define ISR(ID) void __vector_ID (void) __attribute__ ((signal)) ;\
                void __vector_ID (void)
				
#endif // USART_PRIVATE_H_
