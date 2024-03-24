 /*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   ADC_program.c   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  MCAL
 *    SWC      :  ADC
 *
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"

static uint8_t ADC_State = IDEL;
static uint8_t ISR_State;
static uint8_t *pResultOfAsync = NULL;
static void (*pNotificationFunc)(void) = NULL;
static uint8_t sizeOfChain;
static uint8_t chainIndex;
static uint16 *pChainResult = NULL;
static uint8_t *pChainChannel = NULL;

void ADC_Init(void)
{
	/* Select voltage reference */
	ADMUX &= ADC_VOLT_REF_MASK;
    ADMUX |= ADC_VOLTAGE_REFERENCE;	
	
	/* Select Adjust result (right or left) */
	#if ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTMENT
	    CLR_BIT(ADMUX, ADMUX_ADLAR);
		
	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTMENT
	    SET_BIT(ADMUX, ADMUX_ADLAR);
		
	#else
		#error "Configration of ADC_ADJUSTMENT is wrong"
	#endif
	
	/* Select prescaler of ADC */
	ADCSRA &= ADC_RRESCALER_MASK;
	ADCSRA |= ADC_PRESCALER;
	
	/* Enable or Disable of ADC Peripheral */
	#if ADC_STATUS == ADC_ENABLE
	    SET_BIT(ADCSRA, ADCSRA_ADEN);
		
	#elif ADC_STATUS == ADC_DISABLE
	    CLR_BIT(ADCSRA, ADCSRA_ADEN);
		  
	#else
		#error "Configration of ADC_STATUS is wrong"
	#endif
	
	/* Enable or Disable of ADC Interrupt */
	#if ADC_INTERRUPT_STATUS == ADC_INTERRUPT_ENABLE
	    SET_BIT(ADCSRA, ADCSRA_ADIE);
		
	#elif ADC_INTERRUPT_STATUS == ADC_INTERRUPT_DISABLE
	    CLR_BIT(ADCSRA, ADCSRA_ADIE);
		  
	#else
		#error "Configration of ADC_INTERRUPT_STATUS is wrong"
	#endif
}

void ADC_Enable(void)
{
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

void ADC_Disable(void)
{
	CLR_BIT(ADCSRA, ADCSRA_ADEN);
}

void ADC_InterruptEnable(void)
{
	SET_BIT(ADCSRA, ADCSRA_ADIE);
}

void ADC_InterruptDisable(void)
{
	CLR_BIT(ADCSRA, ADCSRA_ADIE);
}

void ADC_AutoTriggerEnable(void)
{
	SET_BIT(ADCSRA, ADCSRA_ADATE);
}

void ADC_AutoTriggerDisable(void)
{
	CLR_BIT(ADCSRA, ADCSRA_ADATE);
}

error_t ADC_SetPrescaler(uint8_t prescaler)
{
	error_t errorState = noError;
	
	if(prescaler >= ADC_DIVISION_FACTOR_2 && prescaler <= ADC_DIVISION_FACTOR_128)
	{
		ADCSRA &= ADC_RRESCALER_MASK;
	    ADCSRA |= prescaler;
		
	}else
	{
		errorState = functionParameterError;
	} 
	
	return errorState;
}

error_t ADC_SetAutoTriggerSource(uint8_t sourceOfAutoTrigger)
{
	error_t errorState = noError;
	
	if(sourceOfAutoTrigger == ADC_FREE_RUNNING || 
	   sourceOfAutoTrigger == ADC_ANALOG_COMPARATOR || 
	   sourceOfAutoTrigger == ADC_EXTI0 || 
	   sourceOfAutoTrigger == ADC_TIMER0_COMPARE_MATCH || 
	   sourceOfAutoTrigger == ADC_TIMER0_OVERFLOW || 
	   sourceOfAutoTrigger == ADC_TIMER_COMPARE_MATCH_B ||
	   sourceOfAutoTrigger == ADC_TIMER1_OVERFLOW ||
	   sourceOfAutoTrigger == ADC_TIMER1_CAPTURE_EVENT
	   )
	{
		SFIOR_REG &= ADC_AUTO_TRIGGER_MASK ;
	    SFIOR_REG |= sourceOfAutoTrigger;
		
	}else
	{
		errorState = functionParameterError;
	}
	
	return errorState;
}

error_t ADC_GetResultSync(ADC_Chaanel_t channel, uint16 *pResult)
{
	error_t errorState = noError;
	uint8_t TimeoutCounter = 0;
	
	if(channel >= SingleEnded_ADC0 && channel <= Differential_ADC4_ADC2_1X && pResult != NULL)
	{
		if(ADC_State == IDEL)
		{
			ADC_State = BUSY;
			
			/* Select channel of ADC */
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= channel;
			
			/* Start of conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			while(GET_BIT(ADCSRA, ADCSRA_ADIF) == LOW && TimerCounter != ADC_TIMEOUT_COUNT)
			{
				TimerCounter++;
			}
			
			if(TimerCounter != ADC_TIMEOUT_COUNT)
			{
				/* Clear flag */
				SET_BIT(ADCSRA, ADCSRA_ADIF);
				
				#if ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTMENT
				       *pResult = (ADCL | (ADCH << 8)); 
					
				#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTMENT
				      *pResult = ((ADCL >> 6) | (ADCH << 2));
					  
				#else
					#error "Configration of ADC_ADJUSTMENT is wrong"
				#endif
				
			}else
			{
				errorState = TimeoutError;
			}
			
			ADC_State = IDEL;
			
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

error_t ADC_StartConversionAsync(ADC_Chaanel_t channel, uint16 *pResult, void (*pFunc)(void))
{
	error_t errorState = noError;
	
	if(channel >= SingleEnded_ADC0 && channel <= Differential_ADC4_ADC2_1X && pResult != NULL && pFunc != NULL)
	{
		if(ADC_State == IDEL)
		{
			ADC_State = BUSY;
			ISR_State = ADC_CHAIN_CHANNEL;
			
			/* Select channel */
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= channel;
			
			pResultOfAsync  = pResult;
			pNotificationFunc = pFunc;
			
			/* Start of conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			/* Enable of ADC Interrupt */
			SET_BIT(ADCSRA, ADCSRA_ADIE);
			
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

error_t ADC_StatrChainConversionAsync(ADC_Chain_t *pChain)
{
	error_t errorState = noError;
	
	if(pChain != NULL && pChain->pChannels != Null && pChain->pFunc != NULL && pChain->pResult != NULL)
	{
		if(ADC_State == IDEL)
		{
			ADC_State = BUSY;
			ISR_State = ADC_CHAIN_CHANNEL;
			
			pChainResult  = pChain->pResult;
			pNotificationFunc = pChain->pFunc;
			pChainChannel = pChain->pChannels;
            sizeOfChain	= pChain->size;
			chainIndex = 0;
			
			/* Select channel */
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= pChain->pChannels[chainIndex++];
			
			/* Start of conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			/* Enable of ADC Interrupt */
			SET_BIT(ADCSRA, ADCSRA_ADIE);
			
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

/*************************************************************ISR Implementation******************************************************/

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(ADC_SINGLE_CHANNEL == ISR_State)
	{
		ADC_State = IDEL;
		
	    #if ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTMENT
	           *pResultOfAsync = (ADCL | (ADCH << 8)); 
	    	
	    #elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTMENT
	          *pResultOfAsync = ((ADCL >> 6) | (ADCH << 2));
	    	  
	    #else
	    	#error "Configration of ADC_ADJUSTMENT is wrong"
	    #endif
		
		(*pNotificationFunc)();
		
		/* Disable of ADC Interrupt */
		CLR_BIT(ADCSRA, ADCSRA_ADIE);
		
	}else
	{
	    #if ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTMENT
	           pChainResult[chainIndex - 1] = (ADCL | (ADCH << 8)); 
	    	
	    #elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTMENT
	          pChainResult[chainIndex - 1] = ((ADCL >> 6) | (ADCH << 2));
	    	  
	    #else
	    	#error "Configration of ADC_ADJUSTMENT is wrong"
	    #endif

        if(chainIndex == sizeOfChain)	
		{
			ADC_State = IDEL;
			
			(*pNotificationFunc)();
			
			/* Disable of ADC Interrupt */
			CLR_BIT(ADCSRA, ADCSRA_ADIE);
			
		}else
		{
			/* Select channel */
			ADMUX &= ADC_CHANNEL_MASK;
			ADMUX |= pChain->pChannels[chainIndex++];
			
			/* Start of conversion */
			SET_BIT(ADCSRA, ADCSRA_ADSC);			
		}			
	}
}