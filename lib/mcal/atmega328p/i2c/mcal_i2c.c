/**
 ******************************************************************************
 * \file       mcal_mssp.c
 * \author     Abdulrhman Bahaa
 * \brief      This source file contains implementations for the MSSP module
 *             functions
 * \date       2024-2-22
 ******************************************************************************
*/
#include "mcal_i2c.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_i2c_init(i2c_config_t* i2c_config) {
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
    TWBR = ((F_CPU / (i2c_config->serial_clock)) - 16) / 2;
    I2C_ENABLE();
    return ret;
}

Std_ReturnType mcal_i2c_address_transmit(const uint8_t slave_address, i2c_master_operation_t master_operation) {
    Std_ReturnType ret = E_OK;
    mcal_i2c_byte_transmit(slave_address | master_operation);
    return ret;
}

Std_ReturnType mcal_i2c_byte_transmit(const uint8_t data_to_transmit) {
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

Std_ReturnType mcal_i2c_master_transmit(uint8_t slave_address, uint8_t* data, uint8_t size) {
    Std_ReturnType ret = E_OK;

    ret |= mcal_i2c_start_condition();
    ret |= mcal_i2c_address_transmit(slave_address, WRITE);

    for (uint8_t i = 0; i < size; i++) {
        ret |= mcal_i2c_byte_transmit(data[i]);
    }
    
    ret |= mcal_i2c_stop_condition();

    return ret;
}
