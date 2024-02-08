/**
 ******************************************************************************
 * @file       mcal_interrupt.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for interrupts module
 * @date       2023-12-17
 ******************************************************************************
*/
//#define	MCAL_INTERRUPT_H
#ifndef MCAL_INTERRUPT_H
#define	MCAL_INTERRUPT_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0

/* Macro Functions Declarations ---------------------------------------------*/
#define GLOBAL_INTERRUPT_ENABLE()               (INTCONbits.GIE = 1)
#define GLOBAL_INTERRUPT_DISABLE()              (INTCONbits.GIE = 0)

#define PERIPHERAL_IINTERRUPT_ENABLE()          (INTCONbits.PEIE = 1)
#define PERIPHERAL_IINTERRUPT_DISABLE()          (INTCONbits.PEIE = 0)

#define RB_PORT_CHANGE_INTERRUPT_ENABLE()       (INTCONbits.RBIE = 1)
#define RB_PORT_CHANGE_INTERRUPT_DISABLE()      (INTCONbits.RBIE = 0)
#define RB_PORT_CHANGE_INTERRUPT_FLAG_CLEAR()   (INTCONbits.RBIF = 0)

#define TIMER0_INTERRUPT_ENABLE()               (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()              (INTCONbits.TMR0IE  = 0)
#define TIMER0_INTERRUPT_FLAG_CLEAR()           (INTCONbits.TMR0IF = 0)

#define TIMER1_INTERRUPT_ENABLE()               (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()              (PIE1bits.TMR1IE = 0)
#define TIMER1_INTERRUPT_FLAG_CLEAR()           (PIR1bits.TMR1IF = 0)


#define TIMER2_INTERRUPT_ENABLE()               (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()              (PIE1bits.TMR2IE  = 0)
#define TIMER2_INTERRUPT_FLAG_CLEAR()           (PIR1bits.TMR2IF = 0)

#define CCP1_INTERRUPT_ENABLE()                 (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()                (PIE1bits.CCP1IE  = 0)
#define CCP1_INTERRUPT_FLAG_CLEAR()             (PIR1bits.CCP1IF = 0)

#define USART_TRANSMIT_INTERRUPT_ENABLE()       (PIE1bits.TXIE = 1)
#define USART_TRANSMIT_INTERRUPT_DISABLE()      (PIE1bits.TXIE = 0)

#define USART_RECEIVE_INTERRUPT_ENABLE()       (PIE1bits.RCIE = 1)
#define USART_RECEIVE_INTERRUPT_DISABLE()      (PIE1bits.RCIE = 0)


/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    INTX_INTERRUPT_FALING_EDGE = 0,
    INTX_INTERRUPT_RISING_EDGE
}intx_interrupt_edge_t;

typedef enum {
    INTX_INTERRUPT_PRIORITY_LOW = 0,
    INTX_INTERRUPT_PRIORITY_HIGH
}intx_interrupt_priority_t;

typedef enum {
    RB_CHANGE_INTERRUPT_PRIORITY_LOW = 0,
    RB_CHANGE_INTERRUPT_PRIORITY_HIGH
}rb_change_interrupt_priority_t;

typedef struct {
    pin_config_t intx_pin;
    intx_interrupt_edge_t edge; 
    intx_interrupt_priority_t priority;
    void (*intx_isr_app_ptr)(void);
}intx_interrrupt_t;

typedef struct {
    rb_change_interrupt_priority_t priority;
}rb_change_interrrupt_t;

typedef enum {
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3 
}timerx_t;

typedef enum {
    CCP1_INDEX = 0,
    CCP2_INDEX
}ccpx_t;

/* Variables Declarations ---------------------------------------------------*/
extern void (*timerx_isr_app_ptr[4])(void);
extern void (*ccpx_isr_app_ptr[2])(void);
extern void (*usart_transmit_isr_app_ptr)(void);
extern void (*usart_receive_isr_app_ptr)(void);

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_interrupt_rb_change_initialize(const rb_change_interrrupt_t* rb_change_interrrupt);
Std_ReturnType mcal_interrupt_rb_change_deinitialize(const rb_change_interrrupt_t* rb_change_interrrupt);
Std_ReturnType mcal_interrupt_rb_change_app_isr(const rb_change_interrrupt_t* rb_change_interrrupt);
Std_ReturnType mcal_interrupt_timerx_init(timerx_t timer_number, void (*timerx_callback_interrupt_function)(void));
Std_ReturnType mcal_interrupt_ccpx_init(ccpx_t ccp_number, void (*ccpx_callback_interrupt_function)(void));
Std_ReturnType mcal_interrupt_usart_init(uint8_t state, void (*usart_callback_interrupt_function)(void));

#endif	/* MCAL_INTERRUPT_H */

