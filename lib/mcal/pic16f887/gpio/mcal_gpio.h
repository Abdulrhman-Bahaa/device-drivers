/**
 ******************************************************************************
 * @file       mcal_gpio.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations of gpio module
 * @date       2023-12-05
 ******************************************************************************
*/
#ifndef mcal_GPIO_H
#define	mcal_GPIO_H

/* Includes -----------------------------------------------------------------*/
#include "../mcal_std_types.h"

/* Macro Declarations -------------------------------------------------------*/
#define _XTAL_FREQ                          8000
#define BIT_MASK                            0x01
#define PORT_PIN_MAX_NUMBER                 0x08
#define PORT_MAX_NUMBER                     0x05

/* Macro Functions Declarations ---------------------------------------------*/
#define SET_BIT(REG,BIT_POSN)               (*REG |= (BIT_MASK <<  BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)             (*REG &= ~(BIT_MASK <<  BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)            (*REG ^= (BIT_MASK <<  BIT_POSN))
#define READ_BIT(REG,BIT_POSN)              ((*REG >> BIT_POSN) & BIT_MASK )

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
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
    port_index_t port;           /* @ref port_index_t */
    pin_index_t  pin ;           /* @ref pin_index_t */
    direction_t  direction ;     /* @ref direction_t */
    logic_t      logic ;         /* @ref logic_t */
}pin_config_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_gpio_pin_direction_initialize(const pin_config_t* pin_config, direction_t direction);
Std_ReturnType mcal_gpio_pin_direction_status(const pin_config_t* pin_config, direction_t* direction_status);
Std_ReturnType mcal_gpio_pin_logic_write(const pin_config_t* pin_config, logic_t logic);
Std_ReturnType mcal_gpio_pin_logic_read(const pin_config_t* pin_config, logic_t* logic);
Std_ReturnType mcal_gpio_pin_initialize(const pin_config_t* pin_config);

#endif	/* mcal_GPIO_H */

