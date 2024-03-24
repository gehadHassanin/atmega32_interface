/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   ADC_private.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  ADC
 *
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define ADMUX          *((volatile uint8_t*) 0x27)
#define ADMUX_ADLAR    (5)


#define ADCSRA         *((volatile uint8_t*) 0x26)
#define ADCSRA_ADIE    (3)
#define ADCSRA_ADIF    (4)
#define ADCSRA_ADATE   (5)
#define ADCSRA_ADSC    (6)
#define ADCSRA_ADEN    (7)


#define ADCL           *((volatile uint8_t*) 0x24)
#define ADCH           *((volatile uint8_t*) 0x25)
#define ADC_DATA_REG   *((volatile uint16*) 0x24)


#ifndef SFIOR_REG 
#define SFIOR_REG      *((volatile uint8_t*) 0x50)
#endif 

/**********************************************************************************************************************************/

#define ADC_EXT_AREF        (0b00000000)
#define ADC_INT_AVCC        (0b01000000)
#define ADC_INT_2_56        (0b11000000)


#define ADC_LEFT_ADJUSTMENT   (1)
#define ADC_RIGHT_ADJUSTMENT  (0)


#define ADC_ENABLE   (1)
#define ADC_DISABLE  (0)


#define ADC_INTERRUPT_ENABLE   (1)
#define ADC_INTERRUPT_DISABLE  (0)


#define ADC_AUTO_TRIGGER_ENABLE   (1)
#define ADC_AUTO_TRIGGER_DISABLE  (0)



#define ADC_DIVISION_FACTOR_2     (0b00000000)
#define ADC_DIVISION_FACTOR_4     (0b00000010)
#define ADC_DIVISION_FACTOR_8     (0b00000011)
#define ADC_DIVISION_FACTOR_16    (0b00000100)
#define ADC_DIVISION_FACTOR_32    (0b00000101)
#define ADC_DIVISION_FACTOR_64    (0b00000110)
#define ADC_DIVISION_FACTOR_128   (0b00000111)


#define ADC_FREE_RUNNING             (0b00000000)
#define ADC_ANALOG_COMPARATOR        (0b00100000)
#define ADC_EXTI0                    (0b01000000)
#define ADC_TIMER0_COMPARE_MATCH     (0b01100000)
#define ADC_TIMER0_OVERFLOW          (0b10000000)
#define ADC_TIMER_COMPARE_MATCH_B    (0b10100000)
#define ADC_TIMER1_OVERFLOW          (0b11000000)
#define ADC_TIMER1_CAPTURE_EVENT     (0b11100000)


#define ADC_VOLT_REF_MASK         (0b00111111)
#define ADC_RRESCALER_MASK        (0b11111000)
#define ADC_AUTO_TRIGGER_MASK     (0b00011111)
#define ADC_CHANNEL_MASK          (0b11100000)

#define IDEL   (1)
#define BUSY   (0)

#define ADC_SINGLE_CHANNEL   (0)
#define ADC_CHAIN_CHANNEL    (1)

#endif // ADC_PRIVATE_H_
