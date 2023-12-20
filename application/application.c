/**
 ******************************************************************************
 * @mainpage   8_bit_mcu_interfaces
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the main function for the application
 * @date       2023-11-17
 ******************************************************************************
*/
#include "application.h"

/* Variables Definitions ----------------------------------------------------*/ 
pin_config_t led0 = {
  .port = PORTC_INDEX,
.pin  = PIN0_INDEX,
  .direction = OUTPUT,
  .logic = LOW
};

/* Main Function ------------------------------------------------------------*/
int main(void) {
    Std_ReturnType ret = E_OK;
    ret = application_initialize();
    ret = mcal_gpio_pin_initialize(&led0);
    uint8_t data = 0;
    ret = mcal_eeprom_data_write(0x0ff, 1);
    ret = mcal_eeprom_data_read(0x3ff, &data);
    ret = mcal_gpio_pin_logic_write(&led0, data);
    while(1) {
    }
    return (EXIT_SUCCESS);
}

/* Functions Implementations -------------------------------------------------*/
/**
 * @brief       This function will include calls of functions to initialize 
 *              application's interfaces
 * @return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
*/
Std_ReturnType application_initialize(void) {
    Std_ReturnType ret = E_OK;
    return ret;
}