/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   USART_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  USART
 *
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

typedef enum{
	
	FrameError,
	DataOverRun,
	ParityError,
	Success
}ErrorType_t;

void USART_Init(void);
void USART_SetBaudrRate(uint16 baudRate);
error_t USART_SetParityMode(uint8_t parityMode);
error_t USART_SetNumberOfStopBit(uint8_t stopBit);
error_t USART_SetTransferMode(uint8_t mode);
error_t USART_SetDataSize(uint8_t dataSize);
error_t USART_SetClockPolarity(uint8_t clockPolarity);

ErrorType_t USART_GetErrorType(void);

error_t USART_TransmitDataSync(uint8_t data);
error_t USART_ReceiveDataSync(uint8_t *pData);
error_t USART_TransmitStringSync(uint8_t *pString);
error_t USART_ReceiveStringSync(uint8_t *pString, uint8_t lengthOfString);

error_t USART_ReceiveDataAsync(uint8_t *pData, void (*pFunc)(void));
error_t USART_TransmitStringAsync(uint8_t *pString, void (*pFunc)(void));
error_t USART_ReceiveStringAsync(uint8_t *pString, uint8_t lengthOfString, void (*pFunc)(void));

error_t USART_TxInterruptControl(uint8_t state);
error_t USART_RxInterruptControl(uint8_t state);

void USART_ReceiverEnable(void);
void USART_TransmitterEnable(void);
void USART_TransmitterDisable(void);
void USART_ReceiverDisable(void);


#endif // USART_INTERFACE_H_ 
