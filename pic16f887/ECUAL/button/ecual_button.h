/*
 ******************************************************************************
 * @file           : ecual_button.h
 * @author         : Abdulrhman Bahaa
 * @brief          : Contains the functionality of my application
 ******************************************************************************
*/
#ifndef ECUAL_BUTTON_H
#define	ECUAL_BUTTON_H

/* Includes -----------------------------------------------------------------*/
#include "../../MCAL/gpio/mcal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    BUTTON_RELEASED = 0,
    BUTTON_PRESSED
}button_status_t;

typedef enum {
    ACTIVE_LOW = 0,
    ACTIVE_HIGH
}button_active_t;

typedef struct {
    pin_config_t pin;
    button_active_t connection;
}button_config_t;

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType ecual_button_initialize(const button_config_t* btn);
Std_ReturnType ecual_button_read(const button_config_t* btn, button_status_t* btn_status);
Std_ReturnType ecual_button_invoke_on_high(const button_config_t* btn, void (*function_to_invoke)(void));

#endif /* ECUAL_BUTTON_H */

