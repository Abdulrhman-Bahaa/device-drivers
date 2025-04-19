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
<img src="images/batman_logo.jpg" alt="Batman logo" width="200"/>
