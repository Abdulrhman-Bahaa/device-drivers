/*
 ******************************************************************************
 * @file           : ecu_button.c
 * @author         : Abdulrhman Bahaa
 * @brief          : Contains the functionality of my application
 ******************************************************************************
*/
#include "ecual_button.h"

/* Global Variables ---------------------------------------------------------*/

/* Functions Implementations ------------------------------------------------*/
Std_ReturnType ecual_button_initialize(const button_config_t* btn){
    Std_ReturnType ret = E_OK;
    if((NULL == btn)) {
        ret = E_NOT_OK;
    }
    else {
        mcal_gpio_pin_direction_initialize(&(btn->pin), INPUT); 
    }
    return ret;
}

Std_ReturnType ecual_button_read(const button_config_t* btn,button_status_t* btn_status) {
    Std_ReturnType ret = E_OK;
    if((NULL == btn) || (NULL == btn_status)) {
        ret = E_NOT_OK;
    }
    else {
        logic_t logic;
        ret = mcal_gpio_pin_logic_read(&(btn->pin), &logic);
        if (ACTIVE_HIGH == btn->connection) {
            if (HIGH == logic) {
                *btn_status = BUTTON_PRESSED;
            }
            else if (LOW == logic) {
                *btn_status = BUTTON_RELEASED;
            }
        }
        else if (ACTIVE_LOW == btn->connection) {
            if (HIGH == logic) {
                *btn_status = BUTTON_RELEASED;
            }
            else if (LOW == logic) {
                *btn_status = BUTTON_PRESSED;
            }
        }
    }
    return ret;
}

/*
 ******************************************************************************
 User          Date                 Brief
 ******************************************************************************
*/
