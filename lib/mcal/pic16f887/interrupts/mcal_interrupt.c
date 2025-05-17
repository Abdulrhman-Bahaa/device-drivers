/**
 ******************************************************************************
 * \file       mcal_interrupt.c
 * \author     Abdulrhman Bahaa
 * \brief      This source file contains the implementations for char interrupts
 *             interfaces
 * \date       2023-12-10
 ******************************************************************************
*/
#include "mcal_interrupt.h"

/* Variables Definitions -----------------------------------------------------*/
void (*timerx_isr_app_ptr[4])(void) = {NULL, NULL, NULL, NULL};
void (*ccpx_isr_app_ptr[2])(void) = {NULL, NULL};
void (*usart_transmit_isr_app_ptr)(void) = NULL;
void (*usart_receive_isr_app_ptr)(void) = NULL;

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_interrupt_ccpx_init(ccpx_t ccp_number, void (*ccpx_callback_interrupt_function)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == ccpx_callback_interrupt_function) {
        ret = E_NOT_OK;
    }
    else {
        GLOBAL_INTERRUPT_DISABLE();
        switch(ccp_number){
            case CCP1_INDEX: 
                CCP1_INTERRUPT_FLAG_CLEAR();
                ccpx_isr_app_ptr[0] = ccpx_callback_interrupt_function;
                CCP1_INTERRUPT_ENABLE();
                break;
            case CCP2_INDEX: 
                CCP1_INTERRUPT_FLAG_CLEAR();
                ccpx_isr_app_ptr[1] = ccpx_callback_interrupt_function;
                CCP1_INTERRUPT_ENABLE();
                break;
            default:
                ret = E_NOT_OK; 
        }
        PERIPHERAL_IINTERRUPT_ENABLE();
        GLOBAL_INTERRUPT_ENABLE();
    }
    return ret;
}


Std_ReturnType mcal_interrupt_usart_init(uint8_t state, void (*usart_callback_interrupt_function)(void)){
    Std_ReturnType ret = E_OK;
    if (NULL == usart_callback_interrupt_function) {
        ret = E_NOT_OK;
    }
    else {
        GLOBAL_INTERRUPT_DISABLE();
        if (0 == state) {
            // Transmitter
            usart_transmit_isr_app_ptr = usart_callback_interrupt_function;
            USART_TRANSMIT_INTERRUPT_ENABLE();
        }
        else {
            usart_receive_isr_app_ptr = usart_callback_interrupt_function;
            USART_RECEIVE_INTERRUPT_ENABLE();    
        }    
        PERIPHERAL_IINTERRUPT_ENABLE();
        GLOBAL_INTERRUPT_ENABLE();
    }
    return ret;
}
