/**
 ******************************************************************************
 * \file       mcal_usart.c
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes implementations for USART module
 *             The specific model used is PIC16F887.
 * \date       2024-1-31
 ******************************************************************************
*/
#include "mcal_usart.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_usart_init(const usart_t* usart) {
    Std_ReturnType ret = E_OK;
    if(NULL == usart){
        ret = E_NOT_OK;
    }
    else {        
        ret = mcal_usart_brg_init(usart);
        
        if (USART_ASYNCHRONOUS_MODE == usart->mode) {
            USART_ASYNCHRONOUS_MODE();
        }
        else {
            USART_SYNCHRONOUS_MODE();
        }
        
        USART_SERIAL_PORT_ENABLE();
     
        if (USART_TRANSMITTER == usart->device_state) {
            if (1 == usart->usart_interrupt) {
                ret = mcal_interrupt_usart_init(USART_TRANSMITTER, (usart->usart_callback_interrupt_function));
            }
            else {
                USART_TRANSMIT_INTERRUPT_DISABLE();
            }
            
            if (USART_8_BIT_DATA == usart->size) {
                USART_8_BIT_TRANSMISSION();
            }
            else {
                USART_9_BIT_TRANSMISSION();
            }
            
            USART_ENABLE_TRANSMISSION();
        }
        else {
            if (1 == usart->usart_interrupt) {
                ret = mcal_interrupt_usart_init(USART_RECEIVER, (usart->usart_callback_interrupt_function));
            }
            else {
                USART_RECEIVE_INTERRUPT_DISABLE();
            }
            
            if (USART_8_BIT_DATA == usart->size) {
                USART_8_BIT_RECEPTION();
            }
            else {
                USART_9_BIT_RECEPTION();
            }
            
            USART_CONTINUOUS_RECEIVE_ENABLE();
        }
    }
    return ret; 
}

Std_ReturnType mcal_usart_brg_reg_value_calc(const usart_t* usart) {
    Std_ReturnType ret = E_OK;
    if(NULL == usart){
        ret = E_NOT_OK;
    }
    else {
        if(USART_ASYNCHRONOUS_MODE == usart->mode) {
            if(0 == usart->brg_16_bit){
                if(0 == usart->high_baud_rate) {
                    SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 64) - 1;
                }
                else {
                    SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 16) - 1;
                }
            }
            else{
                if(0 == usart->high_baud_rate) {
                    SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 16) - 1;
                    SPBRGH = ((((usart->fosc) / (usart->baud_rate_speed)) / 16) - 1) >> 8;
                }
                else {
                    SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 4) - 1;
                    SPBRGH = ((((usart->fosc) / (usart->baud_rate_speed)) / 4) - 1) >> 8;
                }
            }
        }
        else {
            if(0 == usart->brg_16_bit) {
                SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 4) - 1;
            }
            else {
                SPBRG = (((usart->fosc) / (usart->baud_rate_speed)) / 4) - 1;
                SPBRGH = ((((usart->fosc) / (usart->baud_rate_speed)) / 4) - 1) >> 8;
            }
        }
    }
    return ret; 
}

Std_ReturnType mcal_usart_brg_init(const usart_t* usart) {
    Std_ReturnType ret = E_OK;
    if(NULL == usart) {
        ret = E_NOT_OK;
    }
    else {            
        if (1 == usart->brg_16_bit) {
            BRG_16_BIT();
        }
        else {
            BRG_8_BIT();
        }

        if (1 == usart->high_baud_rate) {
            BRG_HIGH_BAUD_RATE();
        }
        else {
            BRG_LOW_BAUD_RATE();
        }
        ret = mcal_usart_brg_reg_value_calc(usart);
    }
    return ret; 
}

Std_ReturnType mcal_usart_transmit_data(const usart_t* usart, uint8_t byte_to_transmit, uint8_t bit_to_transmit) {
    Std_ReturnType ret = E_OK;
    if(NULL == usart) {
        ret = E_NOT_OK;
    }
    else {
        if (USART_9_BIT_DATA == usart->size) {
            TXSTAbits.TX9D = bit_to_transmit;
        }
        else {
            /* Nothing */
        }
        while(!TXSTAbits.TRMT);        
        TXREG = byte_to_transmit;
    }
    return ret; 
}

Std_ReturnType mcal_usart_receive_data(const usart_t* usart, uint8_t* received_byte, uint8_t* received_bit) {
    Std_ReturnType ret = E_OK;
    if((NULL == usart) && (NULL == received_byte)) {
        ret = E_NOT_OK;
    }
    else {        
        if (USART_9_BIT_DATA == usart->size) {
            *received_bit = RCSTAbits.RX9D;
        }
        else {
            /* Nothing */
        }  
        *received_byte = RCREG;
    }
    return ret; 
}

Std_ReturnType mcal_usart_transmit_string(const usart_t* usart, char string[]) {
    Std_ReturnType ret = E_OK;
    if(NULL == usart) {
        ret = E_NOT_OK;
    }
    else {        
        uint8_t i = 0;
        while('\0' != string[i]) {
            ret = mcal_usart_transmit_data(&usart, (uint8_t)string[i], 0);
            i++;
        }
         ret = mcal_usart_transmit_data(&usart, (uint8_t)'\0', 0);
    }
    return ret; 
}
