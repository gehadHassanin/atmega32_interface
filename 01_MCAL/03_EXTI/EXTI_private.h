/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   EXTI_private.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  EXTI
 *
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define MCUCR_REG    *((volatile uint8_t*) 0x55)
#define MCUCR_ISC00  (0)
#define MCUCR_ISC01  (1)
#define MCUCR_ISC10  (2)
#define MCUCR_ISC11  (3)


#define MCUCSR_REG   *((volatile uint8_t*) 0x54)
#define MCUCSR_ISC2  (6)


#define GICR_REG     *((volatile uint8_t*) 0x5B)
#define GICR_INT2    (5)
#define GICR_INT0    (6)
#define GICR_INT1    (7)


#define GIFR_REG     *((volatile uint8_t*) 0x5A)
#define GIFR_INTF2   (5)
#define GIFR_INTF0   (6)
#define GIFR_INTF1   (7)


#define NUM_OF_INTERRPUT_SOURCE   (3)

#endif // EXTI_PRIVATE_H_
