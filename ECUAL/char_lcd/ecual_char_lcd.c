/**
 ******************************************************************************
 * @file       ecual_char_lcd.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the implementations for char lcd 
 *	       interfaces
 * @date       2023-12-06
 ******************************************************************************
*/
#include "ecual_char_lcd.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType ecual_char_lcd_enable_pulse(const char_lcd_t* char_lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = mcal_gpio_pin_logic_write(&(char_lcd->enable_pin), HIGH);
        __delay_us(1);
        ret = mcal_gpio_pin_logic_write(&(char_lcd->enable_pin), LOW);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_send_data(const char_lcd_t* char_lcd, uint8_t to_send_data, logic_t rs_pin) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = mcal_gpio_pin_logic_write(&(char_lcd->rs_pin), rs_pin);
        for (int bit_to_pin = 0; bit_to_pin < 8; bit_to_pin++) {
            ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(&to_send_data, bit_to_pin));
        }
        ret = ecual_char_lcd_enable_pulse(char_lcd);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_send_instruction(const char_lcd_t* char_lcd, uint8_t instruction ) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = ecual_char_lcd_send_data(char_lcd, instruction, LOW);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_write_char(const char_lcd_t* char_lcd, uint8_t row, uint8_t column, uint8_t character) {
     Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = ecual_char_lcd_set_cursor(char_lcd, row, column);
        ret = ecual_char_lcd_send_data(char_lcd, character, HIGH);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_write_string(char_lcd_t* char_lcd, uint8_t row, uint8_t column, char string[]) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = mcal_gpio_pin_logic_write(&(char_lcd->rs_pin), HIGH);
        int i = 0;
        while('\0' != string[i]) {
            ret = ecual_char_lcd_write_char(char_lcd, row, column, string[i]);
            i++;
        }
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_set_cursor(const char_lcd_t* char_lcd, uint8_t row, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd || row > 4 || column > 20) {
        ret = E_NOT_OK;
    }
    else {
        uint8_t cursor_address;
        column--;
        switch(row) {
            case 1:
                cursor_address = 0x0 + column;
                break;
            case 2:
                cursor_address = 0x40 + column;
                break;
            case 3:
                cursor_address = 0x14 + column;
                break;
            case 4:
                cursor_address = 0x54 + column;
                break;
            default:
                ret = E_NOT_OK;              
        }
        cursor_address += 128;
        ret = ecual_char_lcd_send_data(char_lcd, cursor_address, LOW);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_set_cgram_address(char_lcd_t* char_lcd, uint8_t custom_char_address){
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {  
        ret = ecual_char_lcd_send_data(char_lcd, custom_char_address, LOW);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_add_custom_char(const char_lcd_t* char_lcd, uint8_t custom_char_posn, uint8_t custom_char[]) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        uint8_t custom_char_address = 0x40 + (custom_char_posn << 3);
        ret = ecual_char_lcd_set_cgram_address(char_lcd, custom_char_address);
        
        for (int row_number = 0; row_number < 8; row_number++) {
            ret = mcal_gpio_pin_logic_write(&(char_lcd->rs_pin), HIGH);
            for (int bit_to_pin = 0; bit_to_pin < 5; bit_to_pin++) {
                ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(&custom_char[row_number], bit_to_pin));
            } 
            ecual_char_lcd_enable_pulse(char_lcd);
            custom_char_address++;
            ret = ecual_char_lcd_set_cgram_address(char_lcd, custom_char_address);
        }

    }
    return ret;
}

Std_ReturnType ecual_char_lcd_initialize(const char_lcd_t* char_lcd, const uint8_t function_set_command, const uint8_t display_control_command) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        for (int i = 0; i < 8; i++) {
            ret = mcal_gpio_pin_initialize(&char_lcd->data[i]);
        }
        ret = mcal_gpio_pin_initialize(&char_lcd->rs_pin);
        ret = mcal_gpio_pin_initialize(&char_lcd->rw_pin);
        ret = mcal_gpio_pin_initialize(&char_lcd->enable_pin);     
        __delay_ms(25);
        ret = ecual_char_lcd_send_instruction(char_lcd, function_set_command);
        __delay_ms(15);
        ret = ecual_char_lcd_send_instruction(char_lcd, function_set_command);
        __delay_us(150);
        ret = ecual_char_lcd_send_instruction(char_lcd, function_set_command);
        __delay_ms(50);
        ret = ecual_char_lcd_send_instruction(char_lcd, function_set_command);
        __delay_us(50);
        ret = ecual_char_lcd_send_instruction(char_lcd, _LCD_CLEAR_DISPLAY);
        __delay_ms(30);
        ret = ecual_char_lcd_send_instruction(char_lcd, display_control_command);
    __delay_us(50);
    }
    return ret;
}
