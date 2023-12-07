 /**
 ******************************************************************************
 * @file       ecu_char_lcd.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file contains the declarations for char lcd 
 *	       interfaces
 * @date       2023-12-06
 * @details    This header file contains the declarations for char lcd 
 *	       interfaces
 ******************************************************************************
*/
#ifndef ECU_CHAR_LCD_H
#define	ECU_CHAR_LCD_H

/* Includes -----------------------------------------------------------------*/
#include "../../MCAL/gpio/hal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/
#define LCD_FIRST_ROW                       0x01
#define LCD_SECOND_ROW                      0x02

#define _LCD_8_BIT_2_LINES_FONT_5X8_DOTS    0x38
#define _LCD_CLEAR_DISPLAY                  0x01
#define _LCD_RETURN_HOME                    0x02
#define _LCD_DISPLAY_OFF_CURSOR_OFF         0x08
#define _LCD_DISPLAY_ON_CURSOR_OFF          0x0C
#define _LCD_DISPLAY_ON_CURSOR_ON           0x0E

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef struct {
    pin_config_t rs_pin;
    pin_config_t rw_pin;
    pin_config_t enable_pin;
    pin_config_t data[8];
}char_lcd_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType ecu_char_lcd_enable_pulse(const char_lcd_t* char_lcd);
Std_ReturnType ecu_char_lcd_send_data(const char_lcd_t* char_lcd, uint8 to_send_data, logic_t rs_pin);
Std_ReturnType ecu_char_lcd_send_instruction(const char_lcd_t* char_lcd, uint8 instruction );
Std_ReturnType ecu_char_lcd_write_char(const char_lcd_t* char_lcd, uint8 row, uint8 column, uint8 character);
Std_ReturnType ecu_char_lcd_write_string(char_lcd_t* char_lcd, uint8 row, uint8 column, char string[]);
Std_ReturnType ecu_char_lcd_set_cursor(const char_lcd_t* char_lcd, uint8 row, uint8 column);
Std_ReturnType ecu_char_lcd_set_cgram_address(char_lcd_t* char_lcd, uint8 custom_char_address);
Std_ReturnType ecu_char_lcd_add_custom_char(const char_lcd_t* char_lcd, uint8 custom_char_posn, uint8 custom_char[]);
Std_ReturnType ecu_char_lcd_initialize(const char_lcd_t* char_lcd, const uint8 function_set_command, const uint8 display_control_command);

#endif	/* ECU_CHAR_LCD_H */
