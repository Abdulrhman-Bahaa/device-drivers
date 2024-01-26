/**
 ******************************************************************************
 * @file       mcal_timer1.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for timer1 module
 * @date       2023-12-17
 ******************************************************************************
*/
#ifndef MCAL_TIMER1_H
#define	MCAL_TIMER1_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define TIMER1_ENABLE()                            (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                           (T1CONbits.TMR1ON = 0)
#define EXTERNAL_CLOCK_FROM_RC0()                  (T1CONbits.TMR1CS = 1)
#define INTERNAL_CLOCK()                           (T1CONbits.TMR1CS = 0)
#define SYNCHRONIZE_EXTERNAL_CLOCK _INPUT()        (T1CONbits.T1SYNC = 0)
#define DO_NOT_SYNCHRONIZE_EXTERNAL_CLOCK _INPUT() (T1CONbits.T1SYNC = 1)
#define TIMER1_OSCILLATOR_ENABLE                   (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE                  (T1CONbits.T1OSCEN = 0)

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    PRESCALE_1 = 0,
    PRESCALE_4,
    PRESCALE_16
}timer1_clock_prescale_t;

typedef enum {
    POSTSCALE_1 = 0,
    POSTSCALE_2,
    POSTSCALE_3,
    POSTSCALE_4,
    POSTSCALE_5,
    POSTSCALE_6,
    POSTSCALE_7,
    POSTSCALE_8,
    POSTSCALE_9,
    POSTSCALE_10,
    POSTSCALE_11,
    POSTSCALE_12,
    POSTSCALE_13,
    POSTSCALE_14,
    POSTSCALE_15,
    POSTSCALE_16
}timer1_output_postscale_t;

typedef struct {
    timer1_clock_prescale_t prescale_value;
    timer1_output_postscale_t postscale_value;
    uint8_t timer1_interrupt : 1;
    void (*timer1_callback_interrupt_function)(void);
    uint8_t pr1_reg_value;
}timer1_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_timer1_init(timer1_t* timer1);

#endif	/* MCAL_TIMER1_H */
