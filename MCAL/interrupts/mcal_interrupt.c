/**
 ******************************************************************************
 * @file       mcal_inter.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the implementations for char interrupts
 *             interfaces
 * @date       2023-12-10
 ******************************************************************************
*/
#include "mcal_interrupt.h"

/* Variables Definitions -----------------------------------------------------*/
void (*intx_isr_app_ptr[3])(void) = {NULL, NULL, NULL};
void (*timerx_isr_app_ptr[4])(void) = {NULL, NULL, NULL, NULL};

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_interrupt_intx_initialize(const intx_interrrupt_t* intx_interrrupt) {
    Std_ReturnType ret = E_OK;
    if (NULL == intx_interrrupt) {
        ret = E_NOT_OK;
    }
    else {
        GLOBAL_INTERRUPT_DISABLE();
        switch(intx_interrrupt->intx_pin.pin){
            case PIN0_INDEX: 
                // Clear flag
                INT0_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
                // Configure pin as input
                ret = mcal_gpio_pin_direction_initialize(&(intx_interrrupt->intx_pin));
                // Configure edge
                if (INTX_INTERRUPT_FALING_EDGE == intx_interrrupt->edge) {
                    INT0_EXTERNAL_INTERRUPT_FALING_EDGE();
                }
                else {
                    INT0_EXTERNAL_INTERRUPT_RISING_EDGE();
                }
                // Enable Interrupt
                INT0_EXTERNAL_INTERRUPT_ENABLE();
                break;
            case PIN1_INDEX: 
                // Clear flag
                INT1_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
                // Configure pin as input
                ret = mcal_gpio_pin_direction_initialize(&(intx_interrrupt->intx_pin));
                // Configure edge
                if (INTX_INTERRUPT_FALING_EDGE == intx_interrrupt->edge) {
                    INT1_EXTERNAL_INTERRUPT_FALING_EDGE();
                }
                else {
                    INT1_EXTERNAL_INTERRUPT_RISING_EDGE();
                }
                // Configure priority
                if (INTX_INTERRUPT_PRIORITY_LOW == intx_interrrupt->priority) {
                    INT1_EXTERNAL_INTERRUPT_PRIORITY_LOW();
                }
                else {
                    INT1_EXTERNAL_INTERRUPT_PRIORITY_HIGH();
                }
                // Enable Interrupt
                INT1_EXTERNAL_INTERRUPT_ENABLE();
                break;
            case PIN2_INDEX: 
                 // Clear flag
                INT2_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
                // Configure pin as input
                ret = mcal_gpio_pin_direction_initialize(&(intx_interrrupt->intx_pin));
                // Configure edge
                if (INTX_INTERRUPT_FALING_EDGE == intx_interrrupt->edge) {
                    INT2_EXTERNAL_INTERRUPT_FALING_EDGE();
                }
                else {
                    INT1_EXTERNAL_INTERRUPT_RISING_EDGE();
                }
                // Configure priority
                if (INTX_INTERRUPT_PRIORITY_LOW == intx_interrrupt->priority) {
                    INT2_EXTERNAL_INTERRUPT_PRIORITY_LOW();
                }
                else {
                    INT2_EXTERNAL_INTERRUPT_PRIORITY_HIGH();
                }
                // Enable Interrupt
                INT2_EXTERNAL_INTERRUPT_ENABLE();
                break;
            default:
                ret = E_NOT_OK; 
        }
        ret = mcal_interrupt_intx_app_isr(intx_interrrupt);
        GLOBAL_INTERRUPT_ENABLE();
    }
    return ret;
}
Std_ReturnType mcal_interrupt_intx_deinitialize(const intx_interrrupt_t* intx_interrrupt){
    Std_ReturnType ret = E_OK;
    if (NULL == intx_interrrupt) {
        ret = E_NOT_OK;
    }
    else {
        uint8_t gie = INTCONbits.GIE;
        GLOBAL_INTERRUPT_DISABLE();
        switch(intx_interrrupt->intx_pin.pin){
            case PIN0_INDEX: 
                INT0_EXTERNAL_INTERRUPT_DISABLE();
                break;
            case PIN1_INDEX: 
                INT1_EXTERNAL_INTERRUPT_DISABLE();
                break;
            case PIN2_INDEX: 
                INT2_EXTERNAL_INTERRUPT_DISABLE();
                break;
            default:
                ret = E_NOT_OK; 
        }
        if (1 == gie) {
            GLOBAL_INTERRUPT_ENABLE();
        }
        else {
            /* Nothing */
        }
    }
    return ret;
}

Std_ReturnType mcal_interrupt_intx_app_isr(const intx_interrrupt_t* intx_interrrupt){
    Std_ReturnType ret = E_OK;
    if (NULL == intx_interrrupt) {
        ret = E_NOT_OK;
    }
    else {
        switch(intx_interrrupt->intx_pin.pin){
            case PIN0_INDEX: 
                intx_isr_app_ptr[0] = intx_interrrupt->intx_isr_app_ptr;
                break;
            case PIN1_INDEX: 
                intx_isr_app_ptr[1] = intx_interrrupt->intx_isr_app_ptr;
                break;
            case PIN2_INDEX: 
                intx_isr_app_ptr[2] = intx_interrrupt->intx_isr_app_ptr;
                break;
            default:
                ret = E_NOT_OK; 
        }
    }
    return ret;
}

Std_ReturnType mcal_interrupt_timerx_init(timerx_t timer_number, void (*timerx_callback_interrupt_function)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == timerx_callback_interrupt_function) {
        ret = E_NOT_OK;
    }
    else {
        GLOBAL_INTERRUPT_DISABLE();
        switch(timer_number){
            case TIMER0: 
                break;
            case TIMER1: 
                break;
            case TIMER2:
                TIMER2_INTERRUPT_FLAG_CLEAR();
                timerx_isr_app_ptr[2] = timerx_callback_interrupt_function;
                TIMER2_INTERRUPT_ENABLE();
                break;
            case TIMER3: 
                break;
            default:
                ret = E_NOT_OK; 
        }
        PERIPHERAL_IINTERRUPT_ENABLE();
        GLOBAL_INTERRUPT_ENABLE();
    }
    return ret;
}