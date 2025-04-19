# OLED driver

This file contains the implementation of the ECUAL (External Control and Abstraction Layer) for controlling an OLED display. It provides a set of functions to initialize, configure, and interact with the OLED display using the I2C protocol.

## Features

- **Initialization**: Functions to initialize the OLED display and set up its configuration.
- **Drawing**: Functions to draw characters, strings, rectangles, and custom bitmaps on the OLED display.
- **Cursor Control**: Functions to set the cursor position on the display.
- **Animation**: Support for displaying animations using a sequence of images.
- **Menu System**: Functions to create and navigate a menu system on the OLED display.
- **Scrolling**: Functions to enable or disable scrolling on the display.
- **Contrast Control**: Function to adjust the display contrast.

## Functions Overview

### Initialization
- `ecual_oled_display_init`: Initializes the OLED display with default settings.

### Drawing
- `ecual_oled_display_bit_mapping`: Maps a custom bitmap to the display.
- `ecual_oled_display_char_write`: Writes a single character to the display.
- `ecual_oled_display_string_write`: Writes a string to the display.
- `ecual_oled_display_rectangle_draw`: Draws a rectangle on the display.
- `ecual_oled_display_drawer`: Draws a pattern (e.g., a line or block) on the display.
- `ecual_oled_display_clear`: Clears the display.

### Cursor Control
- `ecual_oled_display_cursor_set`: Sets the cursor position on the display.

### Animation
- `ecual_oled_display_animation`: Displays an animation using an array of images.

### Menu System
- `ecual_oled_display_menu_init`: Initializes a menu system on the display.
- `ecual_oled_display_menu_item_select`: Highlights a selected menu item.

### Scrolling
- `ecual_oled_display_scroll_status_set`: Enables or disables scrolling on the display.

### Contrast Control
- `ecual_oled_display_contrast_set`: Adjusts the display contrast.

## Dependencies

This file depends on the following:
- **MCAL I2C Layer**: Functions like `mcal_i2c_start_condition`, `mcal_i2c_data_transmit`, and `mcal_i2c_stop_condition` are used for I2C communication.
- **Font Data**: Fonts like `ssd1306xled_font6x8` and `ssd1306xled_font8x16` are used for rendering text.
- **Macros**: Macros like `READ_BIT` and constants for OLED commands are used throughout the file.

## Usage Example

```c
Std_ReturnType ret = E_OK;
oled_display_config_t oled_display = {
  .oled_display_address = 0x78
};

/* Initialize I2C */
ret |= mcal_i2c_init();
/* Initialize OLED Display */
ret |= ecual_oled_display_init(&oled_display);
/* Bitmapping an image */
ret |= ecual_oled_display_bit_mapping(&oled_display, (uint8_t*)batman, 128, 64, 0, 0);  
```

The output on the screen:
<br>
<br>

<img src="/images/batman_logo.jpg" alt="Batman logo" width="400"/>
