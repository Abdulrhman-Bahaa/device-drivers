/**
 ******************************************************************************
 * @file       mcal_gpio.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations of gpio module
 * @date       2024-2-09
 ******************************************************************************
*/
#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H

/* Includes -----------------------------------------------------------------*/
#include "../mcal_std_types.h"
#include <util/delay.h>

/* Macro Declarations -------------------------------------------------------*/
#define PORT_MAX_NUMBER         3
#define PORT_PIN_MAX_NUMBER     8

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    PORTB_INDEX = 0,
    PORTC_INDEX,
    PORTD_INDEX
}port_index_t;

typedef enum {
    PIN0_INDEX = 0,
    PIN1_INDEX,
    PIN2_INDEX,
    PIN3_INDEX,
    PIN4_INDEX,
    PIN5_INDEX,       
    PIN6_INDEX,
    PIN7_INDEX
}pin_index_t;

typedef enum {
    OUTPUT = 0,
    INPUT
}direction_t;

typedef enum {
    LOW = 0,
    HIGH
}logic_t;

typedef struct { 
    port_index_t port;           
    pin_index_t  pin ;          
    direction_t  direction ;     
    logic_t      logic ;         
}pin_config_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_gpio_pin_direction_initialize(const pin_config_t* pin_config, direction_t direction);
Std_ReturnType mcal_gpio_pin_logic_write(const pin_config_t* pin_config, logic_t logic);
Std_ReturnType mcal_gpio_pin_logic_read(const pin_config_t* pin_config, logic_t* logic);
Std_ReturnType mcal_gpio_pin_logic_toggle(const pin_config_t* pin_config);
Std_ReturnType mcal_gpio_pin_initialize(const pin_config_t* pin_config);

#endif	/* MCAL_GPIO_H */

