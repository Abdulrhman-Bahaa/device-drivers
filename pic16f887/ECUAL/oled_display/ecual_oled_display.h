/**
 ******************************************************************************
 * @file       ecual_oled_display.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations of OLED display module
 * @date       2024-2-29
 ******************************************************************************
*/
#ifndef ECUAL_OLED_DISPLAY_H
#define	ECUAL_OLED_DISPLAY_H

/* Includes -----------------------------------------------------------------*/
#include "../../MCAL/i2c/mcal_i2c.h"
#include "ecual_oled_display_addons.h"

/* Macro Declarations -------------------------------------------------------*/
#define OLED_DISPLAY_DISPLAY_ON                                              0xAF
#define OLED_DISPLAY_SET_PAGE_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE         0xB0
#define OLED_DISPLAY_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE 0x00
#define OLED_DISPLAY_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE 0x10

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef struct {
    uint8_t oled_display_address;
}oled_display_config_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType ecual_oled_display_bit_mapping(const oled_display_config_t* oled_display,
                                                    const uint8_t *array_of_bytes, const uint8_t height,
                                                    const uint8_t width, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_cursor_set(const oled_display_config_t* oled_display, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_init(const oled_display_config_t* oled_display);
Std_ReturnType ecual_oled_display_clear (const oled_display_config_t* oled_display);
Std_ReturnType ecual_oled_display_contrast_set(const oled_display_config_t* oled_display, uint8_t contrast);
Std_ReturnType ecual_oled_display_char_write(const oled_display_config_t* oled_display, const uint8_t char_to_display, const uint8_t height, const uint8_t width, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_string_write(const oled_display_config_t* oled_display, const uint8_t string[], const uint8_t height, const uint8_t width, uint8_t page, uint8_t column);

void single_command_byte(void);

void command_stream(void);

void single_data_byte(void);

void data_stream(void);

#endif	/* ECUAL_OLED_DISPLAY_H */
