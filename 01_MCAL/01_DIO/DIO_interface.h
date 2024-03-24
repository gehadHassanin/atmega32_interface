/*
 * <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<   DIO_interface.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 * Author  :  Gehad Hassanein
 * Layer   :  MCAL
 * SWC     :  DIO/GPIO
 *
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

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

typedef enum {
	
	OUTPUT = 0xff,
	INPUT = 0	
}direction_t;


typedef enum {
	
	HIGH = 0xff,
	LOW = 0
}state_t;

/************************************************************* Pin *************************************************************************/

/**
 * @brief 				   : This function is used to set Data Direction Register of the Pin [OUTPUT, INPUT]
 * @param  portName 	   : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  pinNumber 	   : pinNumber --> [PIN0, PIN1, PIN2 ... PIN7]
 * @param  pinDirection    : pinDirection --> [INPUT, OUTPUT]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetPinDirection(port_t portName, pin_t pinNumber, direction_t pinDirection);


/**
 * @brief                  : This function used to set Port Register of the pin[HIGH, LOW]
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  pinNumber       : pinNumber --> [PIN0, PIN1, PIN2 ... PIN7]
 * @param  voltageLevel    : voltageLevel --> [HIGH, LOW]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetPinValue(port_t portName, pin_t pinNumber, state_t voltageLevel);


/**
 * @brief                  : This function used to Get pin voltage value[HIGH, LOW]
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  pinNumber       : pinNumber --> [PIN0, PIN1, PIN2 ... PIN7]
 * @param  *pData          : *pData --> pointer to receive pin value
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_GetPinValue(port_t portName, pin_t pinNumber, uint8_t *pData);


/**
 * @brief                  : This function used to Toggle pin value [0 ----> 1 || 1 -----> 0]
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  pinNumber       : pinNumber --> [PIN0, PIN1, PIN2 ... PIN7]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_TogglePinValue(port_t portName, pin_t pinNumber);

/************************************************************* Port *************************************************************************/

/**
 * @brief                  : This function is used to set Data Direction Register of the Port [OUTPUT, INPUT]
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  portDirection   : portDirection--> [INPUT, OUTPUT, any input ex: 0b01011110 or 0x3C]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetPortDirection(port_t portName, direction_t portDirection);


/**
 * @brief                  : This function used to set Port Register of the port[HIGH, LOW]
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  voltageLevel    : voltageLevel --> [HIGH, LOW, any input ex: 0b01011110 or 0x3f]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetPortValue(port_t portName, state_t voltageLevel);


/**
 * @brief                  : This function used to Get port voltage value
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  *pData          : *pData --> pointer to receive port value
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_GetPortValue(port_t portName, uint8_t *pData);


/**
 * @brief                  : This function used to Toggle port value
 * @param  portName        : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @return error_t         : noError --> if function passed parameter is Correct
 * 						     functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_TogglePortValue(port_t portName);

/************************************************************* High Nibble *************************************************************************/

/**
 * @brief                       : This function used to set High Nibble direction of data direction register [bit4...bit7]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  highNibbleDirection  : highNibbleDirection --> [OUTPUT, INPUT, any input ex: 0101xxxx which x => don't care]
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetHighNibbleDirection(port_t portName, uint8_t highNibbleDirection);


/**
 * @brief                       : This function used to set High Nibble voltage level of port register[bit4...bit7]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  voltageLevel         : voltageLevel --> [HIGH, LOW, any input ex: 0101xxxx which x => don't care]
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetHighNibbleValue(port_t portName, uint8_t voltageLevel); 


/**
 * @brief                       : This function used to Get High Nibble value of pin register [bit4...bit7]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  *pData               : *pData --> pointer to receive High Nibble value
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_GetHighNibbleValue(port_t portName, uint8_t *pData);

/************************************************************* Low Nibble *************************************************************************/

/**
 * @brief                       : This function used to set Low Nibble direction of data direction register [bit0...bit3]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  lowNibbleDirection   : lowNibbleDirection --> [OUTPUT, INPUT, any input ex: xxxx0101 which x => don't care]
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetLowNibbleDirection(port_t portName, uint8_t lowNibbleDirection); 


/**
 * @brief                       : This function used to set Low Nibble voltage level of port register[bit0...bit3]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  voltageLevel         : voltageLevel --> [HIGH, LOW, any input ex: xxxx0101 which x => don't care]
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_SetLowNibbleValue(port_t portName, uint8_t voltageLevel);


/**
 * @brief                       : This function used to Get Low Nibble value of pin register [bit0...bit3]
 * @param  portName             : portName --> [PORTA, PORTB, PORTC, PORTD]
 * @param  *pData               : *pData --> pointer to receive Low Nibble value
 * @return error_t              : noError --> if function passed parameter is Correct
 * 						          functionParameterError --> if function passed parameter is wrong
 */
error_t DIO_GetLowNibbleValue(port_t portName, uint8_t *pData);


/************************************************************* internal pull up *****************************************************************/


/**
 * @brief  : This function used to enable internal pull up
 * @param  : void
 * @return : void
 */
void DIO_InternalPullUpEnable(void);


/**
 * @brief  : This function used to disable internal pull up
 * @param  : void
 * @return : void
 */
void DIO_InternalPullUpDisable(void);

#endif // DIO_INTERFACE_H_
