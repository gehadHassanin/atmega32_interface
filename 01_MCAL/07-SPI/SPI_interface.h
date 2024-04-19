/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   SPI_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  SPI
 *
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

typedef enum {
	
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}pin_t;

typedef enum {
	
	PORTA,
	PORTB,
	PORTC,
	PORTD
}port_t;

typedef struct{
	
	port_t SS_port;
	pin_t SS_pin;
}slaveSelectConfig_t;

void SPI_ConfigOfSlavePinsDirection(void);
error_t SPI_ConfigOfMasterPinsDirection(slaveSelectConfig_t slaveSelectConfigArr[], uint8_t numberOfSlave);

void SPI_MasterInit(void);
void SPI_SlaveInit(void);

error_t SPI_TranceiveChar(uint8_t data, uint8_t *pData);
error_t SPI_TranceiveStringSync(uint8_t *pTX_String, uint8_t *pRX_String, uint8_t sizeOfString);

void SPI_Enable(void);
void SPI_Disable(void);
error_t SPI_InterruptControl(uint8_t state);

error_t SPI_SetDataOrder(uint8_t dataOrder);
error_t SPI_SetClockPolarity(uint8_t clockPolarity);
error_t SPI_SetClockPhase(uint8_t clockPhase);
error_t SPI_SelectClockRate(uint8_t clockRate);


#endif // SPI_INTERFACE_H_ 
