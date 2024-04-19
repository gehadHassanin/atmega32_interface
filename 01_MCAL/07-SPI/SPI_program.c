 /*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   SPI_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  SPI
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"

static uint8_t SPI_State = IDEL;

void SPI_ConfigOfSlavePinsDirection(void)
{
	CLR_BIT(DDRB_REG, PIN5);
	SET_BIT(DDRB_REG, PIN6);
	CLR_BIT(DDRB_REG, PIN7);
	CLR_BIT(DDRB_REG, PIN4); 
}

error_t SPI_ConfigOfMasterPinsDirection(slaveSelectConfig_t slaveSelectConfigArr[], uint8_t numberOfSlave);
{
	error_t errorState = noError;
	uint8_t Iterator;
	
	SET_BIT(DDRB_REG, PIN5);
	CLR_BIT(DDRB_REG, PIN6);
	SET_BIT(DDRB_REG, PIN7);
	
	for(Iterator = 0; Iterator < numberOfSlave; Iterator++)
	{
	    switch(slaveSelectConfigArr[Iterator].SS_port)
	    {
	    	case PORTA: SET_BIT(DDRA_REG, slaveSelectConfigArr[Iterator].SS_pin); break; 
	    	case PORTB: SET_BIT(DDRB_REG, slaveSelectConfigArr[Iterator].SS_pin); break; 
	    	case PORTC: SET_BIT(DDRC_REG, slaveSelectConfigArr[Iterator].SS_pin); break; 
	    	case PORTD: SET_BIT(DDRD_REG, slaveSelectConfigArr[Iterator].SS_pin); break; 
	    	default : errorState = functionParameterError;
	    }		
	}

	return errorState;	
}

void SPI_MasterInit(void)
{
	SPI_SetDataOrder_Helper();
	SPI_SetClockPolarity_Helper();
	SPI_SetClockPhase_Helper();
	SPI_SelectClockRate_Helper();
	SPI_Enable_Helper();
	SPI_InterruptControl_Helper();
}

void SPI_SlaveInit(void)
{
	SPI_SetDataOrder_Helper();
	SPI_SetClockPolarity_Helper();
	SPI_SetClockPhase_Helper();
	SPI_Enable_Helper();
	SPI_InterruptControl_Helper();
}

error_t SPI_TranceiveChar(uint8_t data, uint8_t *pData)
{
	error_t errorState = noError;
	uint32_t TimeoutCounter = 0;
	if(pData != NULL)
	{
	    if(IDEL == SPI_State)
	    {
	    	SPI_State = BUSY;
			SPDR = data; 
	    	while((GET_BIT(SPCR, SPCR_SPIE) == 0) && TimeoutCounter < SPI_TIMEOUT_COUNT)
	    	{
	    		TimeoutCounter++;
	    	}
	    	if(TimeoutCounter == SPI_TIMEOUT_COUNT)
	    	{
	    		errorState = TimeoutError;
	    		
	    	}else
	    	{
	    		*pData = SPDR;
	    	}
	    	
			SPI_State = IDEL;
			
	    }else if(BUSY == SPI_State)
	    {
	    	errorState = BusyError;
	    }	
		
	}else
	{
		errorState = functionParameterError;
	}

	return errorState;		
}

error_t SPI_TranceiveStringSync(uint8_t *pTX_String, uint8_t *pRX_String, uint8_t sizeOfString)
{
	error_t errorState = noError;
	uint8_t Iterator = 0;
	if(pTX_String != NULL && pRX_String != NULL)
	{
		while(Iterator < sizeOfString)
		{
			errorState = SPI_TranceiveChar(pTX_String[Iterator], &pRX_String[Iterator]);
			Iterator++;
		}
		
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;
}

void SPI_Enable(void)
{
	SET_BIT(SPCR, SPCR_SPE);
}

void SPI_Disable(void)
{
	CLR_BIT(SPCR, SPCR_SPE);
}

error_t SPI_InterruptControl(uint8_t state)
{
	error_t errorState = noError;	
	switch(state)
	{
		case ENABLE :  SET_BIT(SPCR, SPCR_SPIE); break;
		case DISABLE : CLR_BIT(SPCR, SPCR_SPIE); break;
		default : errorState = functionParameterError;
	}
	return errorState;
}

error_t SPI_SetDataOrder(uint8_t dataOrder)
{
	error_t errorState = noError;
	switch(dataOrder)
	{
		case LSB_TX_FIRST: SET_BIT(SPCR, SPCR_DORD); break;
		case MSB_TX_FIRST: CLR_BIT(SPCR, SPCR_DORD); break;
		default : errorState = functionParameterError;
	}
	return errorState;
}

error_t SPI_SetClockPolarity(uint8_t clockPolarity)
{
	error_t errorState = noError;
	switch(clockPolarity)
	{
		case RISING_AT_LEADING_EDGE_FALLING_AT_TRAILING_EDGE: CLR_BIT(SPCR, SPCR_CPOL); break;
		case FALLING_AT_LEADING_EDGE_RISING_AT_TRAILING_EDGE: SET_BIT(SPCR, SPCR_CPOL); break;
		default : errorState = functionParameterError;
	}
	return errorState;	
}

error_t SPI_SetClockPhase(uint8_t clockPhase)
{
	error_t errorState = noError;
	switch(clockPhase)
	{
		case SAMPLE_AT_LEADING_EDGE_SETUP_AT_TRAILING_EDGE: CLR_BIT(SPCR, SPCR_CPHA); break;
		case SETUP_AT_LEADING_EDGE_SAMPLE_AT_TRAILING_EDGE: SET_BIT(SPCR, SPCR_CPHA); break;
		default : errorState = functionParameterError;
	}
	return errorState;		
}

error_t SPI_SelectClockRate(uint8_t clockRate)
{
	error_t errorState = noError;
	if(FREEQ_DIVIDED_BY_2 == clockRate)
	{
		CLR_BIT(SPCR, SPCR_SPR0);
		CLR_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
		
	}else if(FREEQ_DIVIDED_BY_4 == clockRate)
	{
		CLR_BIT(SPCR, SPCR_SPR0); 
		CLR_BIT(SPCR, SPCR_SPR1); 
		CLR_BIT(SPSR, SPSR_SPI2X);
		
	}else if(FREEQ_DIVIDED_BY_8 == clockRate)
	{
		SET_BIT(SPCR, SPCR_SPR0); 
		CLR_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
		
	}else if(FREEQ_DIVIDED_BY_16 == clockRate)
	{
		SET_BIT(SPCR, SPCR_SPR0); 
		CLR_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
		
	}else if(FREEQ_DIVIDED_BY_32 == clockRate)
	{
		CLR_BIT(SPCR, SPCR_SPR0); 
		SET_BIT(SPCR, SPCR_SPR1);
		SET_BIT(SPSR, SPSR_SPI2X);
		
	}else if(FREEQ_DIVIDED_BY_64 == clockRate)
	{
		CLR_BIT(SPCR, SPCR_SPR0); 
		SET_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
				
	}else if(FREEQ_DIVIDED_BY_128 == clockRate)
	{
		SET_BIT(SPCR, SPCR_SPR0); 
		SET_BIT(SPCR, SPCR_SPR1);
		CLR_BIT(SPSR, SPSR_SPI2X);
		
	}else
	{
		errorState = functionParameterError;
	}
	return errorState;	
}

/********************************************************************* Helper Functions *******************************************************/


static void SPI_SetDataOrder_Helper(void)
{
	#if SPI_DATA_ORDER == MSB_TX_FIRST
	   CLR_BIT(SPCR, SPCR_DORD);
	
	#elif SPI_DATA_ORDER == LSB_TX_FIRST
	   SET_BIT(SPCR, SPCR_DORD);
	   
	#else
	   #error "Config of SPI_DATA_ORDER is Wrong"
    #endif
}

static void SPI_Enable_Helper(void)
{
	#if SPI_STATE == ENABLE
	  SET_BIT(SPCR, SPCR_SPE);
	  
	#elif SPI_STATE == DISABLE
	  CLR_BIT(SPCR, SPCR_SPE);
	  
	#else
	   #error "Config of SPI_STATE is Wrong"
    #endif
}

static void SPI_InterruptControl_Helper(void)
{
	#if SPI_INTERRUPT_CONTROL == ENABLE
	  SET_BIT(SPCR, SPCR_SPIE);
	  
	#elif SPI_INTERRUPT_CONTROL == DISABLE
	  CLR_BIT(SPCR, SPCR_SPIE); 
	  
	#else
	   #error "Config of SPI_INTERRUPT_CONTROL is Wrong"
    #endif	
}

static void SPI_SetClockPolarity_Helper(void)
{
	#if SPI_CLOCK_POLARITY == RISING_AT_LEADING_EDGE_FALLING_AT_TRAILING_EDGE
	   CLR_BIT(SPCR, SPCR_CPOL);
	
	#elif SPI_CLOCK_POLARITY == FALLING_AT_LEADING_EDGE_RISING_AT_TRAILING_EDGE
	   SET_BIT(SPCR, SPCR_CPOL);
	   
	#else
	   #error "Config of SPI_CLOCK_POLARITY is Wrong"
    #endif
}

static void SPI_SetClockPhase_Helper(void)
{
	#if SPI_CLOCK_PHASE == SAMPLE_AT_LEADING_EDGE_SETUP_AT_TRAILING_EDGE
	   CLR_BIT(SPCR, SPCR_CPHA);
	
	#elif SPI_CLOCK_PHASE == SETUP_AT_LEADING_EDGE_SAMPLE_AT_TRAILING_EDGE
	   SET_BIT(SPCR, SPCR_CPHA);
	   
	#else
	   #error "Config of SPI_CLOCK_PHASE is Wrong"
    #endif	
}

static void SPI_SelectClockRate_Helper(void)
{
	#if SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_2
	   CLR_BIT(SPCR, SPCR_SPR0);
	   CLR_BIT(SPCR, SPCR_SPR1);
	   SET_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_4
	   CLR_BIT(SPCR, SPCR_SPR0);  
	   CLR_BIT(SPCR, SPCR_SPR1); 
	   CLR_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_8
	   SET_BIT(SPCR, SPCR_SPR0); 
	   CLR_BIT(SPCR, SPCR_SPR1);
	   SET_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_16
	   SET_BIT(SPCR, SPCR_SPR0); 
	   CLR_BIT(SPCR, SPCR_SPR1);
	   CLR_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_32
	   CLR_BIT(SPCR, SPCR_SPR0); 
	   SET_BIT(SPCR, SPCR_SPR1);
	   SET_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_64
	   CLR_BIT(SPCR, SPCR_SPR0); 
	   SET_BIT(SPCR, SPCR_SPR1);
	   CLR_BIT(SPSR, SPSR_SPI2X);
	   
	#elif SPI_CLOCK_RATE_SELECT == FREEQ_DIVIDED_BY_128
	   SET_BIT(SPCR, SPCR_SPR0); 
	   SET_BIT(SPCR, SPCR_SPR1);
	   CLR_BIT(SPSR, SPSR_SPI2X);
	   
	#else
	   #error "Config of SPI_CLOCK_RATE_SELECT is Wrong"
    #endif	
}