/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   ADC_config.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  ADC
 *
 */

 #ifndef ADC_CONFIG_H_
 #define ADC_CONFIG_H_

 /**
 *  --> Select voltage reference
 *  @Options :-
 *                1- ADC_EXT_AREF
 *                2- ADC_INT_AVCC
 *                3- ADC_INT_2_56
 */
 #define ADC_VOLTAGE_REFERENCE    ADC_INT_AVCC
 
 
 
 /**
 *  --> Select Adjust result
 *  @Options :-
 *                1- ADC_LEFT_ADJUSTMENT
 *                2- ADC_RIGHT_ADJUSTMENT
 */
 #define ADC_ADJUSTMENT    ADC_RIGHT_ADJUSTMENT 
 
 
 
 /**
 *  --> Select state of ADC (Enable or Disable)
 *  @Options :-
 *                1- ADC_ENABLE
 *                2- ADC_DISABLE
 */
 #define ADC_STATUS    ADC_ENABLE 
 
 
 
 /**
 *  --> Select state of Interrupt (Enable or Disable)
 *  @Options :-
 *                1- ADC_INTERRUPT_ENABLE
 *                2- ADC_INTERRUPT_DISABLE
 */
 #define ADC_INTERRUPT_STATUS    ADC_INTERRUPT_DISABLE 
 
 
 
 /**
 *  --> Select state of Auto trigger (Enable or Disable)
 *  @Options :-
 *                1- ADC_AUTO_TRIGGER_ENABLE
 *                2- ADC_AUTO_TRIGGER_DISABLE
 */
 #define ADC_AUTO_TRIGGER_STATUS    ADC_AUTO_TRIGGER_DISABLE

 
 
 /**
 *  --> Select prescaler of ADC
 *  @Options :-
 *                1- ADC_DIVISION_FACTOR_2
 *                2- ADC_DIVISION_FACTOR_4
 *                3- ADC_DIVISION_FACTOR_8
 *                4- ADC_DIVISION_FACTOR_16
 *                5- ADC_DIVISION_FACTOR_32
 *                6- ADC_DIVISION_FACTOR_64
 *                7- ADC_DIVISION_FACTOR_128
 */
 #define ADC_PRESCALER    ADC_DIVISION_FACTOR_128
 
 
 
  /**
 *  --> Select Trigger source of ADC 
 *  @Options :-
 *                1- ADC_FREE_RUNNING
 *                2- ADC_ANALOG_COMPARATOR
 *                3- ADC_EXTI0
 *                4- ADC_TIMER0_COMPARE_MATCH
 *                5- ADC_TIMER0_OVERFLOW
 *                6- ADC_TIMER_COMPARE_MATCH_B
 *                7- ADC_TIMER1_OVERFLOW
 *                8- ADC_TIMER1_CAPTURE_EVENT
 */
 #define ADC_TRIGGER_SOURCE    ADC_FREE_RUNNING

 
 #define ADC_TIMEOUT_COUNT   (5000UL)
 
 #endif // ADC_CONFIG_H_
