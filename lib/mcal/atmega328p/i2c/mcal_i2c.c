/**
 ******************************************************************************
 * @file       mcal_mssp.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains implementations for the MSSP module
 *             functions
 * @date       2024-2-22
 ******************************************************************************
*/
#include "mcal_i2c.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_i2c_init(void) {
    Std_ReturnType ret = E_OK;

    pin_config_t pin_scl = {
        .location = {
            .port = PORTC_INDEX,
            .pin = PIN4_INDEX
        },
        .direction = INPUT,
        .logic = HIGH
    };

    pin_config_t pin_sda = {
        .location = {
            .port = PORTC_INDEX,
            .pin = PIN5_INDEX
        },
        .direction = INPUT,
        .logic = HIGH
    };
    // Initialize SCL and SDA pins
    ret |= mcal_gpio_pin_init(&pin_scl);
    ret |= mcal_gpio_pin_init(&pin_sda);

    I2C_DISABLE();
    // Set bit rate 100 kHz
    TWBR = 72; // Bit rate register value for 100 kHz at 16 MHz CPU clock
    I2C_ENABLE();
    return ret;
}

Std_ReturnType mcal_i2c_address_transmit(const uint8_t slave_address, i2c_master_operation_t master_operation) {
    Std_ReturnType ret = E_OK;
    mcal_i2c_data_transmit(slave_address | master_operation);
    return ret;
}

Std_ReturnType mcal_i2c_data_transmit(const uint8_t data_to_transmit) {
    Std_ReturnType ret = E_OK;
    TWDR = data_to_transmit;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if (0x28 != (TWSR & 0xF8)) {
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType mcal_i2c_start_condition(void) {
    Std_ReturnType ret = E_OK;
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    if (0x08 != (TWSR & 0xF8)) {
        ret = E_NOT_OK;
    }
    return ret;
}

Std_ReturnType mcal_i2c_stop_condition(void) {
    Std_ReturnType ret = E_OK;
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
    return ret;
}
