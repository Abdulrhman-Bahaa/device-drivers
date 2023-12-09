/**
 ******************************************************************************
 * @file       hal_gpio.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains implementations for the gpio module
 *             functions
 * @date       2023-12-06
 ******************************************************************************
*/
#include "hal_gpio.h"

/* Variables Definitions ----------------------------------------------------*/
volatile uint8_t* tris_register[PORT_MAX_NUMBER] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8_t* port_register[PORT_MAX_NUMBER] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType hal_gpio_pin_direction_initialize(const pin_config_t* pin_config){
    Std_ReturnType ret = E_OK;
    uint8_t bit_posn = pin_config->pin;
    if((NULL == pin_config) || (bit_posn > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } 
    else {
        volatile uint8_t* reg_addr = tris_register[pin_config->port];
        switch(pin_config->direction){
            case INPUT :
                SET_BIT(reg_addr,bit_posn);
                break;
            case OUTPUT :
                CLEAR_BIT(reg_addr,bit_posn);
                break;
            default : 
                ret = E_NOT_OK;
        }
    }
    return ret;  
}

Std_ReturnType hal_gpio_pin_direction_status(const pin_config_t* pin_config,direction_t* direction_status) {
    Std_ReturnType ret = E_OK;
    uint8_t bit_posn = pin_config->pin;
    if((NULL == pin_config) || (NULL == direction_status)) {
        ret = E_NOT_OK;
    }
    else {
        volatile uint8_t* reg_addr = tris_register[pin_config->port];
        *direction_status = READ_BIT(reg_addr,bit_posn);
    }
    return ret;  
}

Std_ReturnType hal_gpio_pin_logic_write(const pin_config_t* pin_config, logic_t logic) {
    Std_ReturnType ret = E_OK;
    uint8_t bit_posn = pin_config->pin;
    if((NULL == pin_config) || (bit_posn > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    } 
    else {
        volatile uint8_t* reg_addr = port_register[pin_config->port];
        switch(logic) {
            case HIGH :
                SET_BIT(reg_addr,bit_posn);
                break;
            case LOW :
                CLEAR_BIT(reg_addr,bit_posn);
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;  
}

Std_ReturnType hal_gpio_pin_logic_read(const pin_config_t* pin_config, logic_t* logic) {
    Std_ReturnType ret = E_OK;
    uint8_t bit_posn = pin_config->pin;
    if ((NULL == pin_config) || (bit_posn > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    }
    else {
        volatile uint8_t* reg_addr = port_register[pin_config->port];
        *logic = READ_BIT(reg_addr,bit_posn); 
    }
    return ret;  
}

Std_ReturnType hal_gpio_pin_initialize(const pin_config_t* pin_config) {
    Std_ReturnType ret = E_OK;
    if(NULL == pin_config) {
        ret = E_NOT_OK;
    }
    else {
        ret = hal_gpio_pin_direction_initialize(pin_config);
        ret = hal_gpio_pin_logic_write(pin_config, pin_config->logic);
    }
    return ret;  
}
