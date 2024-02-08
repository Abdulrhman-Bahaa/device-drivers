/**
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

Std_ReturnType ecual_button_invoke_on_high(const button_config_t* btn, void (*function_to_invoke)(void)) {
    Std_ReturnType ret = E_OK;
    if((NULL == btn) || (NULL == function_to_invoke)) {
        ret = E_NOT_OK;
    }
    else {
        button_status_t previous_state = BUTTON_RELEASED;
        button_status_t current_state = BUTTON_RELEASED;
        
        ret = ecual_button_read(btn, &current_state);
        __delay_ms(5);
        ret = ecual_button_read(btn, &current_state);       
                
        if ((BUTTON_PRESSED == current_state) && (BUTTON_RELEASED == previous_state )) {
            function_to_invoke();      
            previous_state = BUTTON_PRESSED;
        }
        else if (current_state == BUTTON_RELEASED){
            previous_state = BUTTON_RELEASED;
        }
        else {
            /* Nothing */
        }
    }
    return ret;
}
