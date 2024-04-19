 /*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   USART_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  USART
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

static uint8_t USART_State = IDEL;
static uint8_t lengthOfData = 0;
static uint8_t Index = 0;
static uint8_t *pReceiveData = NULL;
static uint8_t *pTransmitterData = NULL;
static void (*pCallBackFuncAsync)(void) = NULL;

void USART_Init(void)
{
	/* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	USART_SetCharacterSize_Helper();
	USART_SetParityMode_Helper();
	USART_SetStopBit_Helper();
	USART_SetMode_Helper();
	USART_SetClockPolarity_Helper();
	/* clear UCSRC_URSEL */
	CLR_BIT(UCSRC, UCSRC_URSEL);
	USART_SetBaudRate_Helper();
	USART_TransferEnable_Helper();
	USART_InterruptControl_Helper();
}

error_t USART_SetParityMode(uint8_t parityMode)
{
	error_t errorState = noError;
	
	/* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	
	if(DISABLE == parityMode)
	{
		CLR_BIT(UCSRC, UCSRC_UPM0);
		CLR_BIT(UCSRC, UCSRC_UPM1);
		
	}else if(EVEN_PARITY == parityMode)
	{
		CLR_BIT(UCSRC, UCSRC_UPM0);
		SET_BIT(UCSRC, UCSRC_UPM1);
		
	}else if(ODD_PARITY == parityMode)
	{
		SET_BIT(UCSRC, UCSRC_UPM0);
		SET_BIT(UCSRC, UCSRC_UPM1);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}

error_t USART_SetDataSize(uint8_t dataSize)
{
	error_t errorState = noError;
	
	/* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	
	if(CHARACTER_SIZE_5_BIT == dataSize)
	{
		CLR_BIT(UCSRC, UCSRC_UCSZ0);
		CLR_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
		
	}else if(CHARACTER_SIZE_6_BIT == dataSize)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		CLR_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
		
	}else if(CHARACTER_SIZE_7_BIT == dataSize)
	{
		CLR_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
		
	}else if(CHARACTER_SIZE_8_BIT == dataSize)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		CLR_BIT(UCSRB, UCSRB_UCSZ2);
		
	}else if(CHARACTER_SIZE_9_BIT == dataSize)
	{
		SET_BIT(UCSRC, UCSRC_UCSZ0);
		SET_BIT(UCSRC, UCSRC_UCSZ1);
		SET_BIT(UCSRB, UCSRB_UCSZ2);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}

error_t USART_SetNumberOfStopBit(uint8_t stopBit)
{
	error_t errorState = noError;
	
	/* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	
	if(STOP_BIT_1_BIT == stopBit)
	{
		CLR_BIT(UCSRC, UCSRC_USBS);
		
	}else if(STOP_BIT_2_BIT == stopBit)
	{
		SET_BIT(UCSRC, UCSRC_USBS);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}

error_t USART_SetTransferMode(uint8_t mode)
{
	error_t errorState = noError;
	
    /* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	
	if(ASYNCHRONOUS_1X == mode)
	{
		CLR_BIT(UCSRC, UCSRC_UMSEL);
		CLR_BIT(UCSRA, UCSRA_U2X);
		
	}else if(ASYNCHRONOUS_2X == mode)
	{
		CLR_BIT(UCSRC, UCSRC_UMSEL);
		SET_BIT(UCSRA, UCSRA_U2X);
		
	}else if(SYNCHRONOUS == mode)
	{
		SET_BIT(UCSRC, UCSRC_UMSEL);
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}

void USART_SetBaudrRate(uint16 baudRate)
{
	uint8_t mode;
	
	USART_GetMode_Helper(&mode);
	/* clear UCSRC_URSEL */
	CLR_BIT(UCSRC, UCSRC_URSEL);
	
	switch(mode)
	{
		case ASYNCHRONOUS_1X : 
		                       UBRRH = (uint8_t_)(Calculate_UBRR(16, baudRate) >> 8);
							   UBRRL = (uint8_t_)Calculate_UBRR(16, baudRate); break;
		case ASYNCHRONOUS_2X :
		                       UBRRH = (uint8_t_)(Calculate_UBRR(8, baudRate) >> 8);
							   UBRRL = (uint8_t_)Calculate_UBRR(8, baudRate); break;
	    case SYNCHRONOUS :
		                       UBRRH = (uint8_t_)(Calculate_UBRR(2, baudRate) >> 8);
							   UBRRL = (uint8_t_)Calculate_UBRR(2, baudRate); break;							   
	}                          
}

error_t USART_SetClockPolarity(uint8_t clockPolarity)
{
	error_t errorState = noError;
	
    /* set UCSRC_URSEL */
	SET_BIT(UCSRC, UCSRC_URSEL);
	
	if(TX_AT_RISING_EDGE_RX_AT_FALLING_EDGE == clockPolarity)
	{
		CLR_BIT(UCSRC, UCSRC_UCPOL);
		
	}else if(TX_AT_FALLING_EDGE_RX_AT_RISING_EDGE == clockPolarity)
	{
		SET_BIT(UCSRC, UCSRC_UCPOL);
		
    }else
	{
		errorState = functionParameterError;
	}
	
	return errorState;	
}

ErrorType_t USART_GetErrorType(void)
{
	ErrorDetection_t errorType = Success;
	if(GET_BIT(UCSRA, UCSRA_FE) == 1)
	{
		errorType = FrameError;
	}
	if(GET_BIT(UCSRA, UCSRA_PE) == 1)
	{
		errorType = ParityError;
	}
	if(GET_BIT(UCSRA, UCSRA_DOR) == 1) 
	{
		errorType = DataOverRun;
	}
	return errorType;
}

void USART_ReceiverEnable(void)
{
	SET_BIT(UCSRB, UCSRB_RXEN);
}

void USART_TransmitterEnable(void)
{
	SET_BIT(UCSRB, UCSRB_TXEN);
}

void USART_TransmitterDisable(void)
{
	CLR_BIT(UCSRB, UCSRB_TXEN);
}

void USART_ReceiverDisable(void)
{
	CLR_BIT(UCSRB, UCSRB_RXEN);
}

error_t USART_TxInterruptControl(uint8_t state)
{
	error_t errorState = noError;
	if(DISABLE == state)
	{
		CLR_BIT(UCSRB, UCSRB_TXCIE);
		
	}else if(ENABLE == state)
	{
		SET_BIT(UCSRB, UCSRB_TXCIE);
		
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;
}

error_t USART_RxInterruptControl(uint8_t state)
{
	error_t errorState = noError;
	if(DISABLE == state)
	{
		CLR_BIT(UCSRB, UCSRB_RXCIE);
		
	}else if(ENABLE == state)
	{
		SET_BIT(UCSRB, UCSRB_RXCIE);
		
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;	
}

error_t USART_TransmitDataSync(uint8_t data)
{
	error_t errorState = noError;
	uint32_t TimeoutCounter = 0;
	
	if(IDEL == USART_State)
	{
		USART_State = BUSY;
		while((GET_BIT(UCSRA, UCSRA_UDRE) == 0) && TimeoutCounter < USART_TIMEOUT_COUNT)
		{
			TimeoutCounter++;
		}
		if(TimeoutCounter == USART_TIMEOUT_COUNT)
		{
			errorState = TimeoutError;
			
		}else
		{
			UDR = data;
		}
		
		while(GET_BIT(UCSRA, UCSRA_TXC) == 0);
		USART_State = IDEL;
		
	}else if(BUSY == USART_State)
	{
		errorState = BusyError;
	}
	
	return errorState;
}

error_t USART_ReceiveDataSync(uint8_t *pData)
{
	error_t errorState = noError;
	uint32_t TimeoutCounter = 0;
	if(pData != NULL)
	{
	    if(IDEL == USART_State)
	    {
	    	USART_State = BUSY;
	    	while((GET_BIT(UCSRA, UCSRA_RXC) == 0) && TimeoutCounter < USART_TIMEOUT_COUNT)
	    	{
	    		TimeoutCounter++;
	    	}
	    	if(TimeoutCounter == USART_TIMEOUT_COUNT)
	    	{
	    		errorState = TimeoutError;
	    		
	    	}else
	    	{
	    		*pData = UDR;
	    	}
	    	
			USART_State = IDEL;
			
	    }else if(BUSY == USART_State)
	    {
	    	errorState = BusyError;
	    }	
		
	}else
	{
		errorState = functionParameterError;
	}

	return errorState;
}

error_t USART_TransmitStringSync(uint8_t *pString)
{
	uint32_t Iterator = 0;
	error_t errorState = noError;
	while(pString[Iterator] != '\0')
	{
		errorState = USART_TransmitDataSync(pString[Iterator++]);
	}
	return errorState;
}

error_t USART_ReceiveStringSync(uint8_t *pString, uint8_t lengthOfString)
{
	uint32_t Iterator = 0;
	error_t errorState = noError;
	while(Iterator < lengthOfString)
	{
		errorState = USART_ReceiveDataSync(&pString[Iterator++]);
	}
	pString[Iterator] = '\0';
	return errorState;	
}

error_t USART_ReceiveDataAsync(uint8_t *pData, void (*pFunc)(void))
{
	error_t errorState = noError;
	if(pData != NULL && pFunc != NULL)
	{
		if(IDEL == USART_State)
		{
			USART_State = BUSY;
			lengthOfData = 1;
			pReceiveData = pData;
			pCallBackFuncAsync = pFunc;
			/*Receiver Interrupt Enable*/
			SET_BIT(UCSRB, UCSRB_RXCIE);
			
		}else
		{
			errorState = BusyError;
		}
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;	
}

error_t USART_TransmitStringAsync(uint8_t *pString, void (*pFunc)(void))
{
	error_t errorState = noError;
	if(pString != NULL && pFunc != NULL)
	{
		if(IDEL == USART_State)
		{
			USART_State = BUSY;
			pTransmitterData = pString;
			pCallBackFuncAsync = pFunc;
			UDR = pTransmitterData[Index];
			/*Transmitter Interrupt Enable*/
			SET_BIT(UCSRB, UCSRB_TXCIE);
			
		}else
		{
			errorState = BusyError;
		}
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;	
}

error_t USART_ReceiveStringAsync(uint8_t *pString, uint8_t lengthOfString, void (*pFunc)(void))
{
	error_t errorState = noError;
	if(pString != NULL && pFunc != NULL)
	{
		if(IDEL == USART_State)
		{
			USART_State = BUSY;
			lengthOfData = lengthOfString;
			pReceiveData = pString;
			pCallBackFuncAsync = pFunc;
			/*Receiver Interrupt Enable*/
			SET_BIT(UCSRB, UCSRB_RXCIE);
			
		}else
		{
			errorState = BusyError;
		}
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;	
}
/************************************************************ Helper functions *****************************************************/

static void USART_InterruptControl_Helper(void)
{
	#if USART_RX_COMPLETED_INTERRUPT == ENABLE
	   SET_BIT(UCSRB, UCSRB_RXCIE);
	   
	#elif USART_RX_COMPLETED_INTERRUPT == DISABLE
	   CLR_BIT(UCSRB, UCSRB_RXCIE);
	   
	#else
	   #error "config of USART_RX_COMPLETED_INTERRUPT is wrong"
    #endif
	
	#if USART_TX_COMPLETED_INTERRUPT == ENABLE
	   SET_BIT(UCSRB, UCSRB_TXCIE);
	   
	#elif USART_TX_COMPLETED_INTERRUPT == DISABLE
	   CLR_BIT(UCSRB, UCSRB_TXCIE);
	   
	#else
	   #error "config of USART_TX_COMPLETED_INTERRUPT is wrong"
    #endif	
	
	#if USART_DATA_REGISTER_EMPTY == ENABLE
	   SET_BIT(UCSRB, UCSRB_UDRIE);
	   
	#elif USART_DATA_REGISTER_EMPTY == DISABLE
	   CLR_BIT(UCSRB, UCSRB_UDRIE);
	   
	#else
	   #error "config of USART_DATA_REGISTER_EMPTY is wrong"
    #endif	
}

static void USART_TransferEnable_Helper(void)
{
	#if USART_RX_STATE == ENABLE
	   SET_BIT(UCSRB, UCSRB_RXEN);
	   
	#elif USART_RX_STATE == DISABLE
	   CLR_BIT(UCSRB, UCSRB_RXEN);
	   
	#else
	   #error "config of USART_RX_STATE is wrong"
    #endif
	
	#if USART_TX_STATE == ENABLE
	   SET_BIT(UCSRB, UCSRB_TXEN);
	   
	#elif USART_TX_STATE == DISABLE
	   CLR_BIT(UCSRB, UCSRB_TXEN);
	   
	#else
	   #error "config of USART_TX_STATE is wrong"
    #endif
}

static void USART_SetBaudRate_Helper(void)
{
	#if USART_MODE_SELECT == ASYNCHRONOUS_1X
	   UBRRH = (uint8_t_)(Calculate_UBRR(16, USART_BAUD_RATE) >> 8);
	   UBRRL = (uint8_t_)Calculate_UBRR(16, USART_BAUD_RATE);
	   
	#elif USART_MODE_SELECT == ASYNCHRONOUS_2X
	   UBRRH = (uint8_t_)(Calculate_UBRR(8, USART_BAUD_RATE) >> 8);
	   UBRRL = (uint8_t_)Calculate_UBRR(8, USART_BAUD_RATE);
	   
	#elif USART_MODE_SELECT == SYNCHRONOUS
	   UBRRH = (uint8_t_)(Calculate_UBRR(2, USART_BAUD_RATE) >> 8);
	   UBRRL = (uint8_t_)Calculate_UBRR(2, USART_BAUD_RATE);
	   
	#else
	   #error "config of USART_MODE_SELECT is wrong"
    #endif
}

static void USART_GetMode_Helper(uint8_t *pMode)
{
	if(GET_BIT(UCSRC, UCSRC_UMSEL) == 0)
	{
		*pMode = SYNCHRONOUS;
		
	}else if (GET_BIT(UCSRC, UCSRC_UMSEL) == 1)
	{
		if(GET_BIT(UCSRA, UCSRA_U2X) == 0)
		{
			*pMode = SYNCHRONOUS_1X;
			
		}else if(GET_BIT(UCSRA, UCSRA_U2X) == 1)
		{
			*pMode = SYNCHRONOUS_2X;
		}
	}
}

static void USART_SetMode_Helper(void)
{
	#if USART_MODE_SELECT == ASYNCHRONOUS_1X
	   CLR_BIT(UCSRC, UCSRC_UMSEL);
	   CLR_BIT(UCSRA, UCSRA_U2X);
	   
	#elif USART_MODE_SELECT == ASYNCHRONOUS_2X
	   CLR_BIT(UCSRC, UCSRC_UMSEL);
	   SET_BIT(UCSRA, UCSRA_U2X);
	   
	#elif USART_MODE_SELECT == SYNCHRONOUS
	   SET_BIT(UCSRC, UCSRC_UMSEL);
	   
	#else
	   #error "config of USART_MODE_SELECT is wrong"
    #endif	 
}

static void USART_SetStopBit_Helper(void)
{
	#if USART_STOP_BIT_SELECT == STOP_BIT_1_BIT
	   CLR_BIT(UCSRC, UCSRC_USBS);
	   
	#if USART_STOP_BIT_SELECT == STOP_BIT_2_BIT
	   SET_BIT(UCSRC, UCSRC_USBS);

	#else
	   #error "config of USART_STOP_BIT_SELECT is wrong"
    #endif	    
}

static void USART_SetParityMode_Helper(void)
{
	#if USART_PARITY_MODE == DISABLE
	   CLR_BIT(UCSRC, UCSRC_UPM0);
       CLR_BIT(UCSRC, UCSRC_UPM1);
	   
	#elif USART_PARITY_MODE == EVEN_PARITY
	   CLR_BIT(UCSRC, UCSRC_UPM0);
       SET_BIT(UCSRC, UCSRC_UPM1);
	   
	#elif USART_PARITY_MODE == ODD_PARITY
	   SET_BIT(UCSRC, UCSRC_UPM0);
       SET_BIT(UCSRC, UCSRC_UPM1);
	   
	#else
	   #error "config of USART_PARITY_MODE is wrong"
    #endif
}

static void USART_SetClockPolarity_Helper(void)
{
	#if USART_MODE_SELECT == SYNCHRONOUS
	   #if USART_CLOCK_POLARITY == TX_AT_RISING_EDGE_RX_AT_FALLING_EDGE
	      CLR_BIT(UCSRC, UCSRC_UCPOL);
		  
	   #elif USART_CLOCK_POLARITY == TX_AT_FALLING_EDGE_RX_AT_RISING_EDGE 
	      SET_BIT(UCSRC, UCSRC_UCPOL);
		  
	   #else
		  #error "config of USART_CLOCK_POLARITY is wrong"
		  
	   #endif
	#endif	
}

static void USART_SetCharacterSize_Helper(void)
{
	#if USART_CHARACTER_SIZE == CHARACTER_SIZE_5_BIT
	   CLR_BIT(UCSRC, UCSRC_UCSZ0);
	   CLR_BIT(UCSRC, UCSRC_UCSZ1);
	   CLR_BIT(UCSRB, UCSRB_UCSZ2);
	   
	#elif USART_CHARACTER_SIZE == CHARACTER_SIZE_6_BIT
	   SET_BIT(UCSRC, UCSRC_UCSZ0);
	   CLR_BIT(UCSRC, UCSRC_UCSZ1);
	   CLR_BIT(UCSRB, UCSRB_UCSZ2);
	   
	#elif USART_CHARACTER_SIZE == CHARACTER_SIZE_7_BIT
	   CLR_BIT(UCSRC, UCSRC_UCSZ0);
	   SET_BIT(UCSRC, UCSRC_UCSZ1);
	   CLR_BIT(UCSRB, UCSRB_UCSZ2);
	   
	#elif USART_CHARACTER_SIZE == CHARACTER_SIZE_8_BIT
	   SET_BIT(UCSRC, UCSRC_UCSZ0);
	   SET_BIT(UCSRC, UCSRC_UCSZ1);
	   CLR_BIT(UCSRB, UCSRB_UCSZ2);
	   
	#elif USART_CHARACTER_SIZE == CHARACTER_SIZE_9_BIT
	   SET_BIT(UCSRC, UCSRC_UCSZ0);
	   SET_BIT(UCSRC, UCSRC_UCSZ1);
	   SET_BIT(UCSRB, UCSRB_UCSZ2);
	   
	#else
	   #error "config of USART_CHARACTER_SIZE is wrong"
    #endif
}

/*********************************************************************** ISR Implementation ********************************************************/

/* ISR Of TX */
ISR(15)
{
	if(pTransmitterData[Index] == '\0')
	{
	{
		USART_State = IDEL;
		Index = 0;	
        (*pCallBackFuncAsync)();		
		/*Transmitter Interrupt Disable*/
		CLR_BIT(UCSRB, UCSRB_TXCIE);
	}else
	{
		UDR = pTransmitterData[++Index];
	}
}

/* ISR Of RX */
ISR(13)
{
	pReceiveData[Index++] = UDR;
	if(Index == lengthOfData)
	{
			USART_State = IDEL;
			Index = 0;
			(*pCallBackFuncAsync)();
			/*Receiver Interrupt Disable*/
			CLR_BIT(UCSRB, UCSRB_RXCIE);
	    	
	}else
	{
		/*Do Nothing*/
	}
		
}