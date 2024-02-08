/**
 ******************************************************************************
 * @file       mcal_usart.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for USART module
 *             The specific model used is PIC16F887.
 * @date       2024-1-31
 ******************************************************************************
*/
#ifndef MCAL_USART_H
#define	MCAL_USART_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"
#include "../interrupts/mcal_interrupt.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define BRG_16_BIT() (BAUDCTLbits.BRG16 = 1)
#define BRG_8_BIT() (BAUDCTLbits.BRG16 = 0)
#define BRG_HIGH_BAUD_RATE() (TXSTAbits.BRGH = 1)
#define BRG_LOW_BAUD_RATE() (TXSTAbits.BRGH = 0)

#define USART_SYNCHRONOUS_MODE() (TXSTAbits.SYNC = 1)
#define USART_ASYNCHRONOUS_MODE() (TXSTAbits.SYNC = 0)

#define USART_SERIAL_PORT_ENABLE() (RCSTAbits.SPEN = 1)
#define USART_SERIAL_PORT_DISABLE() (RCSTAbits.SPEN = 0)

#define USART_9_BIT_TRANSMISSION() (TXSTAbits.TX9 = 1)
#define USART_8_BIT_TRANSMISSION() (TXSTAbits.TX9 = 0)
#define USART_ENABLE_TRANSMISSION() (TXSTAbits.TXEN = 1)
#define USART_DISABLE_TRANSMISSION() (TXSTAbits.TXEN = 0)

#define USART_9_BIT_RECEPTION() (RCSTAbits.RX9 = 1)
#define USART_8_BIT_RECEPTION() (RCSTAbits.RX9 = 0)
#define USART_SINGLE_RECEPTION_ENABLE() (RCSTAbits.SREN = 1)
#define USART_SINGLE_RECEPTION_DISABLE() (RCSTAbits.SREN = 0)
#define USART_CONTINUOUS_RECEIVE_ENABLE() (RCSTAbits.CREN = 1)
#define USART_CONTINUOUS_RECEIVE_DISABLE() (RCSTAbits.CREN = 0)

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    USART_ASYNCHRONOUS_MODE = 0,
    USART_SYNCHRONOUS_MODE
}usart_mode_t;

typedef enum {
    USART_TRANSMITTER = 0,
    USART_RECEIVER
}usart_device_state_t;

typedef enum {
    USART_8_BIT_DATA = 0,
    USART_9_BIT_DATA
}data_size_t;

typedef struct {
    usart_mode_t mode;
    uint32_t fosc; 
    uint8_t brg_16_bit : 1;
    uint8_t high_baud_rate : 1;
    uint32_t baud_rate_speed; 
    usart_device_state_t device_state;
    uint8_t usart_interrupt : 1;
    void (*usart_callback_interrupt_function)(void);
    data_size_t size;
}usart_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_usart_brg_reg_value_calc(const usart_t* usart);
Std_ReturnType mcal_usart_init(const usart_t* usart);
Std_ReturnType mcal_usart_brg_init(const usart_t* usart);
Std_ReturnType mcal_usart_transmit_data(const usart_t* usart, uint8_t byte_to_transmit, uint8_t bit_to_transmit);
Std_ReturnType mcal_usart_receive_data(const usart_t* usart, uint8_t* received_byte, uint8_t* received_bit);
Std_ReturnType mcal_usart_transmit_string(const usart_t* usart, char string[]);

#endif	/* MCAL_USART_H */
