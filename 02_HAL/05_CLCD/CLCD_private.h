/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  CLCD_private.h   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 *
 *    Author   :  Gehad Hassanein
 *    Layer    :  HAL
 *    SWC      :  CLCD
 *
 */

#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

/* Macro of commit */
#define LCD_FUNCTION_SET_8_BIT_MODE     (0x38)  // 1-line & 5x8_dot
#define LCD_FUNCTION_SET_4_BIT_MODE     (0x28)  // 1-line & 5x8_dot

                         
#define LCD_DISBLAY_ON_CURSOR_OFF       (0x0c)
#define LCD_DISBLAY_ON_CURSOR_ON        (0x0e)
#define LCD_DISBLAY_OFF_CURSOR_OFF      (0x08)


#define LCD_BLINK_ON                    (0x0f)
#define LCD_BLINK_OFF                   (0x0c)


#define LCD_ENTRY_MODE_INC_SHIFT_OFF    (0x06)
#define LCD_ENTRY_MODE_DEC_SHIFT_OFF    (0x04)
#define LCD_ENTRY_MODE_INC_SHIFT_LIFT   (0x07)
#define LCD_ENTRY_MODE_DEC_SHIFT_RIGHT  (0x05) 


#define LCD_SHIFT_LEFT                  (0x10)
#define LCD_SHIFT_RIGHT                 (0x14)


#define LCD_CLEAR_SCREEN                (0x01)
#define LCD_RETURN_HOME                 (0x02)


static error_t LCD_SendFallingEdgePulse(LCD_t *pLcd);
static error_t LCD_SendCommand(LCD_t *pLcd, uint8_t command);
static error_t LCD_SendData(LCD_t *pLcd, uint8_t data);

#endif // CLCD_PRIVATE_H_
