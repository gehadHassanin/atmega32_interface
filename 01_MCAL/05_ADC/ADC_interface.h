/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   ADC_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  ADC
 *
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	
	SingleEnded_ADC0,
	SingleEnded_ADC1,
	SingleEnded_ADC2,
	SingleEnded_ADC3,
	SingleEnded_ADC4,
	SingleEnded_ADC5,
	SingleEnded_ADC6,
	SingleEnded_ADC7,
	Differential_ADC0_ADC0_10X,
	Differential_ADC1_ADC0_10X,
	Differential_ADC0_ADC0_200X,
	Differential_ADC1_ADC0_200X,
	Differential_ADC2_ADC2_10X,
	Differential_ADC3_ADC2_10X,
	Differential_ADC2_ADC2_200X,
	Differential_ADC3_ADC2_200X,
	Differential_ADC0_ADC1_1X,
	Differential_ADC1_ADC1_1X,
	Differential_ADC2_ADC1_1X,
	Differential_ADC3_ADC1_1X,
	Differential_ADC4_ADC1_1X,
	Differential_ADC5_ADC1_1X,
	Differential_ADC6_ADC1_1X,
	Differential_ADC7_ADC1_1X,
	Differential_ADC0_ADC2_1X,
	Differential_ADC1_ADC2_1X,
	Differential_ADC2_ADC2_1X,
	Differential_ADC3_ADC2_1X,
	Differential_ADC4_ADC2_1X	
}ADC_Chaanel_t;



/****************************************************@data Type****************************************
*  @name         : ADC_Chain_t
*  @intilization : ADC_Chain_t chain = {{SingleEnded_ADC0, SingleEnded_ADC1}, 2, &pArrOfResult, functionName};
*  @Note         : !pChannels --> pointer to channels {SingleEnded_ADC0, SingleEnded_ADC1 ...... Differential_ADC4_ADC2_1X}  
*                  !size --> number of channels
*                  !pResult --> pointer to array Which will store the results
*                  !pFunc --> pointer to function which will execute after interrupt end of conversion complete
*/
typedef struct{
	
	uint8_t *pChannels;
	uint8_t size;
	uint16 *pResult;
	void (*pFunc)(void);
}ADC_Chain_t;

void ADC_Init(void);
void ADC_Enable(void);
void ADC_Disable(void);
void ADC_InterruptEnable(void);
void ADC_InterruptDisable(void);
void ADC_AutoTriggerEnable(void);
void ADC_AutoTriggerDisable(void);
error_t ADC_SetPrescaler(uint8_t prescaler);
error_t ADC_SetAutoTriggerSource(uint8_t sourceOfAutoTrigger);
error_t ADC_GetResultSync(ADC_Chaanel_t channel, uint16 *pResult);
error_t ADC_StartConversionAsync(ADC_Chaanel_t channel, uint16 *pResult, void (*pFunc)(void));
error_t ADC_StatrChainConversionAsync(ADC_Chain_t *pChain);

#endif // ADC_INTERFACE_H_
