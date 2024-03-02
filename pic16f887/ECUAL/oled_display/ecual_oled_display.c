/**
 ******************************************************************************
 * @file       ecual_oled_display.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the implementations for char lcd 
 *             interfaces
 * @date       2024-02-29
 ******************************************************************************
*/
#include "ecual_oled_display.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
int round_up(double num) {
    int integerPart = (int)num; // Get the integer part
    if (num > integerPart) { // If there is a fractional part
        return integerPart + 1; // Round up by adding 1 to the integer part
    } else {
        return integerPart; // No rounding needed
    }
}

static void single_command_byte(void) {
    mcal_mssp_data_trasnmit(0x80);
}

static void command_stream(void) {
    mcal_mssp_data_trasnmit(0x00);
}

static void single_data_byte(void) {
    mcal_mssp_data_trasnmit(0xC0);
}

static void data_stream(void) {
    mcal_mssp_data_trasnmit(0x40);
}

//Std_ReturnType ecual_oled_display_one_page_data_send(const oled_display_config_t* oled_display,const uint8_t array_of_bytes[], const uint8_t height, const uint8_t width, uint8_t page, uint8_t column) {
//    Std_ReturnType ret = E_OK;
//    if (NULL == oled_display) {
//        ret = E_NOT_OK;
//    }
//    else {
//        uint8_t index = 0;
//        uint8_t bytes_index = 0;
//        uint8_t row_num = 0;
//        uint8_t* bytes = malloc(width * sizeof(uint8_t));
//        ret |= ecual_oled_display_cursor_set(oled_display, page, column);
//
//        for (row_num = 0; row_num  < height; row_num++) {
//            mcal_mssp_start_condition();
//            ret |= mcal_mssp_address_trasnmit((oled_display->oled_display_address), WRITE);
//            data_stream();
//            for (uint8_t bytes_number = 0; bytes_number < (width / 8); bytes_number++) {
//                index = (row_num * (width / 8)) + bytes_number;
//                for (sint8_t bit_number = 7; bit_number >= 0; bit_number--) {
//                    bytes_index = (((bytes_number + 1) * 8) - 1) - bit_number;
//                    bytes[bytes_index] |= ((uint8_t)READ_BIT(array_of_bytes[index], bit_number)) << row_num;  
//                    mcal_mssp_data_trasnmit(bytes[bytes_index]); 
//                }
//            } 
//            mcal_mssp_stop_condition();
//            ret |= ecual_oled_display_cursor_set(oled_display, row_num / 8, column);             
//        } 
//        free(bytes);
//    }
//    return ret;
//}

Std_ReturnType ecual_oled_display_bit_mapping(const oled_display_config_t* oled_display,const uint8_t array_of_bytes[], const uint8_t height, const uint8_t width, uint8_t page, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        uint16_t index = 0;
        uint8_t byte_to_send = 0;    
        uint8_t counter = height;
        uint8_t shifting = 0;
        uint8_t h = 0;
        uint8_t width_in_bytes = width / 8.0;
        ret |= ecual_oled_display_cursor_set(oled_display, page, column);
        for (uint8_t page_num = 0; page_num < round_up(height / 8.0); page_num++) {
            if (counter >= 8) {
                h = 8;
                counter -= 8;
            }
            else {
                h = counter;
            }
            mcal_mssp_start_condition();
            ret |= mcal_mssp_address_trasnmit((oled_display->oled_display_address), WRITE);
            data_stream();
            for (uint8_t bytes_number = 0; bytes_number < width_in_bytes; bytes_number++) {
                for (sint8_t bit_number = 7; bit_number >= 0; bit_number--) {
                    for (uint8_t row_num = (page_num * 8); row_num < (page_num * 8) + h; row_num++) {
                        index = (row_num * width_in_bytes) + bytes_number;
                        byte_to_send |= (uint8_t)((READ_BIT(array_of_bytes[index], bit_number)) << shifting);  
                        shifting++;
                    }    
                    shifting = 0;
                    mcal_mssp_data_trasnmit(byte_to_send); 
                    byte_to_send = 0;
                } 
            } 
            mcal_mssp_stop_condition();
            ret |= ecual_oled_display_cursor_set(oled_display, page_num + 1, column); 
        }
    }
    return ret;
}

Std_ReturnType ecual_oled_display_init(const oled_display_config_t* oled_display) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        mcal_mssp_start_condition();
        ret |= mcal_mssp_address_trasnmit((oled_display->oled_display_address), WRITE);
          
        command_stream();
        // Set contrast
        // Display On
        mcal_mssp_data_trasnmit(OLED_DISPLAY_DISPLAY_ON); 

        mcal_mssp_stop_condition();
    }
    return ret;
}

Std_ReturnType ecual_oled_display_cursor_set(const oled_display_config_t* oled_display, uint8_t page, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if ((NULL == oled_display) || (page > 7) || (column > 127)) {
        ret = E_NOT_OK;
    }
    else {
        mcal_mssp_start_condition();
        ret |= mcal_mssp_address_trasnmit((oled_display->oled_display_address), WRITE);
        command_stream();
        // Set Page Start Address for Page Addressing Mode
        mcal_mssp_data_trasnmit(OLED_DISPLAY_SET_PAGE_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)page)); 
        // Set Lower Column Start Address for Page Addressing Mode
        mcal_mssp_data_trasnmit(OLED_DISPLAY_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)column) & 0x0F);
        // Set Higher Column Start Address for Page Addressing Mode
        mcal_mssp_data_trasnmit(OLED_DISPLAY_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)column) >> 4);  
        mcal_mssp_stop_condition();
    }
    return ret;
}

Std_ReturnType ecual_oled_display_clear (const oled_display_config_t* oled_display) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        for (uint8_t page_num = 0; page_num < 8; page_num++) {
            ret |= ecual_oled_display_cursor_set(oled_display, page_num, 0); 
            mcal_mssp_start_condition();
            ret |= mcal_mssp_address_trasnmit((oled_display->oled_display_address), WRITE);
            mcal_mssp_data_trasnmit(0x40);
            for (uint8_t column_num = 0; column_num  < 128; column_num++) {
                mcal_mssp_data_trasnmit(0x00); 
            }  
            mcal_mssp_stop_condition();  
        }  
    }
    return ret;
}
