/**
 ******************************************************************************
 * @file       ecual_char_lcd.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the implementations for char LCD 
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
        
        if (8 == char_lcd->data_interface_size) {
            for (uint8_t bit_to_pin = 0; bit_to_pin < 8; bit_to_pin++) {
                ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(to_send_data, bit_to_pin));
            }
            ret = ecual_char_lcd_enable_pulse(char_lcd);
        }
        else {
            for (uint8_t bit_to_pin = 0; bit_to_pin < 4; bit_to_pin++) {
                ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(to_send_data >> 4, bit_to_pin));
            }
            ret = ecual_char_lcd_enable_pulse(char_lcd);
            for (uint8_t bit_to_pin = 0; bit_to_pin < 4; bit_to_pin++) {
                ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(to_send_data, bit_to_pin));
            }
            ret = ecual_char_lcd_enable_pulse(char_lcd);
        }
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
        ret = ecual_char_lcd_set_cursor(char_lcd, row, column);
        ret = mcal_gpio_pin_logic_write(&(char_lcd->rs_pin), HIGH);
        int i = 0;
        while('\0' != string[i]) {
            ret = ecual_char_lcd_send_data(char_lcd, string[i], HIGH);
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

Std_ReturnType ecual_char_lcd_write_int(const char_lcd_t* char_lcd, uint8_t row, uint8_t column, uint32_t num) {
    Std_ReturnType ret = E_OK;     
    if (NULL == char_lcd) {
    ret = E_NOT_OK;
    }
    else {
        ret = ecual_char_lcd_set_cursor(char_lcd, row, column);
        uint8_t arr[10] = {0};
        int8_t i = -1;
        while (num != 0){
            arr[++i] = 48 + (num % 10);
            num /= 10;
        }
        while (i >= 0) {
            ret = ecual_char_lcd_send_data(char_lcd, arr[i], HIGH);
            i--;           
        }
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_send_4_bit_data(const char_lcd_t* char_lcd, uint8_t to_send_data, logic_t rs_pin) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        ret = mcal_gpio_pin_logic_write(&(char_lcd->rs_pin), rs_pin);
        for (uint8_t bit_to_pin = 0; bit_to_pin < 4; bit_to_pin++) {
            ret = mcal_gpio_pin_logic_write(&(char_lcd->data[bit_to_pin]), READ_BIT(to_send_data, bit_to_pin));
        }
        ret = ecual_char_lcd_enable_pulse(char_lcd);
    }
    return ret;
}

Std_ReturnType ecual_char_lcd_4_bit_init(const char_lcd_t* char_lcd, const uint8_t function_set_command, const uint8_t display_control_command) {
    Std_ReturnType ret = E_OK;
    if (NULL == char_lcd) {
        ret = E_NOT_OK;
    }
    else {
        for (uint8_t i = 0; i < 4; i++) {
            mcal_gpio_pin_initialize(&(char_lcd->data[i]));
        }
        mcal_gpio_pin_initialize(&(char_lcd->rs_pin));
        mcal_gpio_pin_initialize(&(char_lcd->enable_pin));  
        // Function set (Set interface to be 4 bits long.)
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x02, LOW);
        __delay_us(50);
        // Function set (Interface is 4 bits long. Specify the number of display lines and character font.)
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x02, LOW);
        ecual_char_lcd_send_4_bit_data(char_lcd, function_set_command, LOW);
        __delay_us(50);
        // Display clear
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x00, LOW);
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x01, LOW);
        __delay_ms(100);
        // Entry mode set
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x00, LOW);
        ecual_char_lcd_send_4_bit_data(char_lcd, 0x02, LOW);
        __delay_us(50);
        // Display on
        ecual_char_lcd_send_4_bit_data(char_lcd, display_control_command >> 4, LOW);
        ecual_char_lcd_send_4_bit_data(char_lcd, display_control_command, LOW);
        __delay_us(50);
    }
    return ret;
}
