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

Std_ReturnType single_command_byte(void) {
    return mcal_i2c_data_transmit(0x80);
}

Std_ReturnType command_stream(void) {
    return mcal_i2c_data_transmit(0x00);
}

Std_ReturnType single_data_byte(void) {
    return mcal_i2c_data_transmit(0xC0);
}

Std_ReturnType data_stream(void) {
    return mcal_i2c_data_transmit(0x40);
}

Std_ReturnType ecual_oled_display_addressing_mode(const oled_display_config_t* oled_display, const uint8_t mode) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        ret |= mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        ret |= command_stream();
        ret |= mcal_i2c_data_transmit(0x20);
        ret |= mcal_i2c_data_transmit(mode);
        ret |= mcal_i2c_stop_condition();  
    }
    return ret;
}

#if (OLED_DISPLAY_DRAWING_MODE == 1)
    Std_ReturnType ecual_oled_display_bit_mapping(const oled_display_config_t* oled_display,const uint8_t* array_of_bytes, const uint8_t width, const uint8_t height,  uint8_t page, uint8_t column) {
        Std_ReturnType ret = E_OK;
        if (NULL == oled_display) {
            ret = E_NOT_OK;
        }
        else {
            ret |= ecual_oled_display_addressing_mode(oled_display, 0);

            ret |= ecual_oled_display_cursor_set(oled_display, page, column);

            ret |= mcal_i2c_start_condition();
            ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
            ret |= data_stream();
        
            for (uint16_t bytes_number = 0; bytes_number < OLED_DISPLAY_WIDTH * OLED_DISPLAY_PAGES_NUMBER; bytes_number++) {
                ret |= mcal_i2c_data_transmit(pgm_read_byte_near(&array_of_bytes[bytes_number]));
            }
        
            ret |= mcal_i2c_stop_condition();
        }
        return ret;
    }
#else
    Std_ReturnType ecual_oled_display_bit_mapping(const oled_display_config_t* oled_display,const uint8_t* array_of_bytes, const uint8_t width, const uint8_t height,  uint8_t page, uint8_t column) {
        Std_ReturnType ret = E_OK;
        if (NULL == oled_display) {
            ret = E_NOT_OK;
        }
        else {
            uint16_t index = 0;
            uint8_t byte_to_send = 0, shifting = 0, h = 0, counter = height, width_in_bytes = round_up(width / 8.0);    
            ret |= ecual_oled_display_addressing_mode(oled_display, 2);
            for (uint8_t page_num = 0; page_num < round_up(height / 8.0); page_num++) {
                ret |= ecual_oled_display_cursor_set(oled_display, page + page_num, column); 
                if (counter >= 8) {
                    h = 8;
                    counter -= 8;
                }
                else {
                    h = counter;
                }
                ret |= mcal_i2c_start_condition();
                ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
                ret |= data_stream();
                for (uint8_t bytes_number = 0; bytes_number < width_in_bytes; bytes_number++) {
                    for (int8_t bit_number = 7; bit_number >= 0; bit_number--) {
                        for (uint8_t row_num = (page_num * 8); row_num < (page_num * 8) + h; row_num++) {
                            index = (row_num * width_in_bytes) + bytes_number;
                            byte_to_send |= (uint8_t)((READ_BIT(pgm_read_byte_near(array_of_bytes + index), bit_number)) << shifting);  
                            shifting++;
                        }    
                        shifting = 0;
                        ret |= mcal_i2c_data_transmit(byte_to_send); 
                        byte_to_send = 0;
                    } 
                } 
                ret |= mcal_i2c_stop_condition();
            }
        }
        return ret;
    }
#endif

Std_ReturnType ecual_oled_display_char_write(const oled_display_config_t* oled_display, const uint8_t char_to_display, const uint8_t width, const uint8_t height, uint8_t page, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        uint16_t index = 0; 
        uint8_t counter = height, shift = 0, h = 0;
        const uint8_t* font = NULL;
        switch (width * height) {
        case 48:
            font = ssd1306xled_font6x8;
            shift = 6;
            break;
        case 128:
            font = ssd1306xled_font8x16;
            shift = 16;
            break;
        case 176:
            font = courier_new_font11x16_digits;
            shift = 22;
            break;
        case 768:
            font = comic_sans_font24x32_123;
            shift = 96;
            break;
        default:
            ret |= E_NOT_OK;
            break;
        }
        for (uint8_t page_num = 0; page_num < round_up(height / 8.0); page_num++) {
            if (counter >= 8) {
                h = 8;
                counter -= 8;
            }
            else {
                h = counter;
            }
            ret |= ecual_oled_display_cursor_set(oled_display, page + page_num, column);
            mcal_i2c_start_condition();
            ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
            data_stream();
            for (uint8_t bytes_number = 0; bytes_number < width; bytes_number++) {
                index = ((page_num * width) + bytes_number) + (char_to_display - 32) * shift;
                mcal_i2c_data_transmit(pgm_read_byte_near(font + index));  
            }   
            mcal_i2c_stop_condition(); 
        }
    }
    return ret;
}

Std_ReturnType ecual_oled_display_string_write(const oled_display_config_t* oled_display, const uint8_t string[], const uint8_t width, const uint8_t height, uint8_t page, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        uint8_t i = 0, c, a = 0, page_num = page;
        ret |= ecual_oled_display_addressing_mode(oled_display, 2);
        while('\0' != string[i]) {
            c = column + (width * i) - a;
            if ((128 - c) < width) {
                a = 128;
                c = column;
                page_num += round_up(height / 8.0);
            }
            else {
                /* Nothing */
            }
            ret |= ecual_oled_display_char_write(oled_display, string[i], width, height, page_num, c);
            i++;
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
        ret |= mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        ret |= command_stream();
        // Set MUX Ratio to 64
        ret |= mcal_i2c_data_transmit(0xA8); 
        ret |= mcal_i2c_data_transmit(0x3F);
        // Set Display Offset
        ret |= mcal_i2c_data_transmit(0xD3); 
        ret |= mcal_i2c_data_transmit(0x00);
        // Set Display Start Line to 0x00
        ret |= mcal_i2c_data_transmit(0x40); 
        // Set Segment Re-map to disable
        ret |= mcal_i2c_data_transmit(0xA1);
        // Set COM Output Scan Direction to normal mode
        ret |= mcal_i2c_data_transmit(0xC8);
        // Set COM Pins Hardware Configuration
        ret |= mcal_i2c_data_transmit(0xDA);
        ret |= mcal_i2c_data_transmit(0xD2);
        // Set Contrast Control to middle
        ret |= mcal_i2c_data_transmit(0x81);
        ret |= mcal_i2c_data_transmit(0x7F);
        // Disable Entire Display On disable
        ret |= mcal_i2c_data_transmit(0xA4);
        // Set Normal Display
        ret |= mcal_i2c_data_transmit(0xA6);
        // Set Osc Frequency
        ret |= mcal_i2c_data_transmit(0xD5);
        ret |= mcal_i2c_data_transmit(0x80);
        // Enable charge pump regulator
        ret |= mcal_i2c_data_transmit(0x8D);
        ret |= mcal_i2c_data_transmit(0x14);
        // Display On
        ret |= mcal_i2c_data_transmit(OLED_DISPLAY_DISPLAY_ON); 

        ret |= mcal_i2c_stop_condition();
    }
    return ret;
}

Std_ReturnType ecual_oled_display_cursor_set(const oled_display_config_t* oled_display, uint8_t page, uint8_t column) {
    Std_ReturnType ret = E_OK;
    if ((NULL == oled_display) || (page > 7) || (column > 127)) {
        ret = E_NOT_OK;
    }
    else {
        ret |= mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        ret |= command_stream();
        // Set Page Start Address for Page Addressing Mode
        ret |= mcal_i2c_data_transmit(OLED_DISPLAY_SET_PAGE_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)page)); 
        // Set Lower Column Start Address for Page Addressing Mode
        ret |= mcal_i2c_data_transmit(OLED_DISPLAY_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)column) & 0x0F);
        // Set Higher Column Start Address for Page Addressing Mode
        ret |= mcal_i2c_data_transmit(OLED_DISPLAY_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE | ((uint8_t)column) >> 4);  
        ret |= mcal_i2c_stop_condition();
    }
    return ret;
}

Std_ReturnType ecual_oled_display_drawer(const oled_display_config_t* oled_display, uint8_t data_to_draw, uint8_t start_page, uint8_t start_column, uint8_t end_page, uint8_t end_column) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        // uint8_t column = 0;
        // ret |= ecual_oled_display_addressing_mode(oled_display, 2);
        // for (uint8_t page_num = start_page; page_num < end_page + 1; page_num++) {
        //     if (end_page == page_num) {
        //         column = end_column;
        //     }
        //     else {
        //         column = 127;
        //     }
        //     ret |= ecual_oled_display_cursor_set(oled_display, page_num, column);
        //     ret |= mcal_i2c_start_condition();
        //     ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        //     ret |= data_stream();
        //     for (uint8_t column_num = start_column; column_num < column + 1; column_num++) {
        //         ret |= mcal_i2c_data_transmit(data_to_draw); 
        //     }
        //     ret |= mcal_i2c_stop_condition();      
        // }

        ret |= ecual_oled_display_addressing_mode(oled_display, 0);
        ret |= ecual_oled_display_cursor_set(oled_display, start_page, start_column);
        ret |= mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        ret |= data_stream();
        for (uint16_t bytes_number = 0; bytes_number < ((end_page - start_page + 1) * 128) + (end_column - start_column); bytes_number++) {
            ret |= mcal_i2c_data_transmit(data_to_draw); 
        }
    }
    return ret;
}

Std_ReturnType ecual_oled_display_clear(const oled_display_config_t* oled_display) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        ret |= ecual_oled_display_drawer(oled_display, 0x00, 0, 0, 7, 127);
    }
    return ret;
}

Std_ReturnType ecual_oled_display_rectangle_draw(const oled_display_config_t* oled_display, uint8_t thickness, uint8_t page, uint8_t column, uint8_t width, uint8_t height) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        // Height
        uint8_t thickness = 1;
        for (uint8_t i = 0; i < thickness; i++) {
            for (uint8_t vertical_line = 0; vertical_line < (height / 8); vertical_line++) {
                // Left side
                ret |= ecual_oled_display_drawer(oled_display, 0xff, page + vertical_line, column + i, page + vertical_line,  column + 1 + i);
                // Right side
                ret |= ecual_oled_display_drawer(oled_display, 0xff, page + vertical_line, width - thickness - 2 + column , page + vertical_line,  width - thickness + i - 1 + column) ;
            }
        }
        // Width
        if (8 != height) {
            ret |= ecual_oled_display_drawer(oled_display, pow(2, thickness) - 1, page, column + thickness, page, column + (width - 2) - thickness);
            ret |= ecual_oled_display_drawer(oled_display, ((uint8_t)(pow(2, thickness) - 1)) << (8 - thickness), page + (height / 8) - 1 , column + thickness, page + (height / 8) - 1,  column + (width - 2) - thickness);
        }
        else {
            ret |= ecual_oled_display_drawer(oled_display, ((uint8_t)(pow(2, thickness) - 1)) << (8 - thickness) | ((uint8_t)pow(2, thickness) - 1), page, column + thickness, page, column + (width - 2) - thickness);
        }
    }
    return ret;
}


Std_ReturnType ecual_oled_display_contrast_set(const oled_display_config_t* oled_display, uint8_t contrast) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        command_stream();
        mcal_i2c_data_transmit(0x81);
        mcal_i2c_data_transmit(contrast);
        mcal_i2c_stop_condition();
    }
    return ret;
}

Std_ReturnType ecual_oled_display_animation(const oled_display_config_t* oled_display, const uint8_t** array_of_images, 
                                            const uint8_t width, const uint8_t height,  uint8_t page, 
                                            uint8_t column, uint8_t frames_num, int16_t delay_time) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        static uint8_t i = 0;
        ret |= ecual_oled_display_bit_mapping(oled_display, array_of_images[i], width, height, page, column);
        if (frames_num - 1 == i) {
            i = 0;
        }
        else {
            i++;
        }
        _delay_ms(delay_time);
    }
    return ret;
}

Std_ReturnType ecual_oled_display_scroll_status_set(const oled_display_config_t* oled_display, uint8_t status) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display) {
        ret = E_NOT_OK;
    }
    else {
        mcal_i2c_start_condition();
        ret |= mcal_i2c_address_transmit((oled_display->oled_display_address), WRITE);
        single_command_byte();
        if (1 == status) {
            mcal_i2c_data_transmit(0x2F); 
        }
        else if (0 == status){
            mcal_i2c_data_transmit(0x2E); 
        }
        else {
            ret |= E_NOT_OK;
        }
        mcal_i2c_stop_condition();      
    }
    return ret;
}

Std_ReturnType ecual_oled_display_menu_init(const oled_display_menu_config_t* oled_display_menu, uint8_t item_to_select) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display_menu) {
        ret = E_NOT_OK;
    }
    else {
		uint8_t width = oled_display_menu->font_width, height = oled_display_menu->font_height;
        ret |= ecual_oled_display_clear(oled_display_menu->oled_display);
		// Create outline 
        ret |= ecual_oled_display_string_write(oled_display_menu->oled_display, "<", width, height, (height / 8) * item_to_select, 112); 
		// Draw menu items
		for (uint8_t i = 0; i < oled_display_menu->number_of_items; i++) {
			ret |= ecual_oled_display_string_write(oled_display_menu->oled_display, oled_display_menu->array_of_items[i], width, height, i * (height / 8), 8);
		}
    }
    return ret;
}

Std_ReturnType ecual_oled_display_menu_item_select(const oled_display_menu_config_t* oled_display_menu, uint8_t item_to_select) {
    Std_ReturnType ret = E_OK;
    if (NULL == oled_display_menu) {
        ret = E_NOT_OK;
    }
    else {
		uint8_t width = oled_display_menu->font_width, height = oled_display_menu->font_height;
		static uint8_t previous_item = 0;

        ret |= ecual_oled_display_drawer(oled_display_menu->oled_display, 0x00, previous_item * (height / 8), 112, (previous_item * (height / 8)) + ((height / 8) - 1),  128);
        previous_item = item_to_select;
        ret |= ecual_oled_display_string_write(oled_display_menu->oled_display, "<", width, height, (height / 8) * item_to_select, 112); 
    }
    return ret;
}

