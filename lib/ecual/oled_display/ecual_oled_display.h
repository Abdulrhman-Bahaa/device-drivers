/**
 ******************************************************************************
 * \file       ecual_oled_display.h
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes declarations of OLED display module
 * \date       2024-2-29
 ******************************************************************************
*/
#ifndef ECUAL_OLED_DISPLAY_H
#define	ECUAL_OLED_DISPLAY_H

/* Includes -----------------------------------------------------------------*/
#include <atmega328p/i2c/mcal_i2c.h>
#include <stddef.h>
#include "ssd1306_fonts.h"
#include "ssd1306_images.h"
#include "ssd1306_gifs.h"
#include <util/delay.h>

/* Macro Declarations -------------------------------------------------------*/
#define OLED_DISPLAY_WIDTH                                                    128
#define OLED_DISPLAY_HEIGHT                                                   64
#define OLED_DISPLAY_PAGES_NUMBER                                             8
#define OLED_DISPLAY_DISPLAY_ON                                               0xAF
#define OLED_DISPLAY_SET_PAGE_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE          0xB0
#define OLED_DISPLAY_SET_LOWER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE  0x00
#define OLED_DISPLAY_SET_HIGHER_COLUMN_START_ADDRESS_FOR_PAGE_ADDRESSING_MODE 0x10
/* If OLED_DISPLAY_DRAWING_MODE is one, the oled expects vertical draw bitmap */
#define OLED_DISPLAY_DRAWING_MODE                                             0x00
#define SINGLE_COMMAND_BYTE                                                   0x80
#define COMMAND_STREAM                                                        0x00
#define SINGLE_DATA_BYTE                                                      0xC0
#define DATA_STREAM                                                           0x40



/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef struct {
    uint8_t oled_display_address;
}oled_display_config_t;

typedef struct {
    oled_display_config_t* const oled_display;
    uint8_t number_of_items;
    uint8_t font_width;
    uint8_t font_height;
    uint8_t** array_of_items;
}oled_display_menu_config_t;

/* Variables Declarations ---------------------------------------------------*/
extern uint8_t framebuffer[OLED_DISPLAY_PAGES_NUMBER][OLED_DISPLAY_WIDTH]; // For a 128x64 display

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType single_command_byte(void);
Std_ReturnType command_stream(void);
Std_ReturnType single_data_byte(void);
Std_ReturnType data_stream(void);
Std_ReturnType ecual_oled_display_addressing_mode(const oled_display_config_t* oled_display, const uint8_t mode);
Std_ReturnType ecual_oled_display_bit_mapping(const oled_display_config_t* oled_display,
                                                    const uint8_t *array_of_bytes, const uint8_t width,
                                                    const uint8_t height, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_cursor_set(const oled_display_config_t* oled_display, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_init(const oled_display_config_t* oled_display);
Std_ReturnType ecual_oled_display_drawer(const oled_display_config_t* oled_display, uint8_t data_to_draw, uint8_t start_page, uint8_t start_column, uint8_t end_page, uint8_t end_column);

/**
 * \brief       This function will write a pixel on the OLED display
 * \param[in]   oled_display: pointer to the OLED display configuration structure
 * \param[in]   value: value of the pixel (0 or 1)
 * \param[in]   x: x coordinate of the pixel
 * \param[in]   y: y coordinate of the pixel
 * \return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
 */
Std_ReturnType ecual_oled_write_pixel(const oled_display_config_t* oled_display, uint8_t value, uint8_t x, uint8_t y);

/**
 * \brief       This function will create a line between two points
 * \param[in]   oled_display: pointer to the OLED display configuration structure
 * \param[in]   x_start: starting x coordinate of the line
 * \param[in]   y_start: starting y coordinate of the line
 * \param[in]   x_end: ending x coordinate of the line
 * \param[in]   y_end: ending y coordinate of the line
 * \return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
 */
Std_ReturnType ecual_oled_create_line(const oled_display_config_t* oled_display, uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end);

Std_ReturnType ecual_oled_display_rectangle_draw(const oled_display_config_t* oled_display, uint8_t thickness, uint8_t page, uint8_t column, uint8_t width, uint8_t height);
Std_ReturnType ecual_oled_display_clear(const oled_display_config_t* oled_display);
Std_ReturnType ecual_oled_display_contrast_set(const oled_display_config_t* oled_display, uint8_t contrast);
Std_ReturnType ecual_oled_display_char_write(const oled_display_config_t* oled_display, const uint8_t char_to_display, const uint8_t width, const uint8_t height, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_string_write(const oled_display_config_t* oled_display, const uint8_t string[], const uint8_t width, const uint8_t height, uint8_t page, uint8_t column);
Std_ReturnType ecual_oled_display_animation(const oled_display_config_t* oled_display, const uint8_t** array_of_images, 
    const uint8_t width, const uint8_t height,  uint8_t page, 
    uint8_t column, uint8_t frames_num, int16_t delay_time);
Std_ReturnType ecual_oled_display_scroll_status_set(const oled_display_config_t* oled_display, uint8_t status);
Std_ReturnType ecual_oled_display_menu_init(const oled_display_menu_config_t* oled_display_menu, uint8_t item_to_select);
Std_ReturnType ecual_oled_display_menu_item_select(const oled_display_menu_config_t* oled_display_menu, uint8_t item_to_select);

#endif	/* ECUAL_OLED_DISPLAY_H */
