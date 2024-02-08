/**
 ******************************************************************************
 * @file       mcal_timer2.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for timer2 module
 * @date       2023-12-17
 ******************************************************************************
*/
#ifndef MCAL_TIMER2_H
#define	MCAL_TIMER2_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define TIMER2_ENABLE()  (T2CONbits.TMR2ON = 1)
#define TIMER2_DISABLE() (T2CONbits.TMR2ON = 0)

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    PRESCALE_1 = 0,
    PRESCALE_4,
    PRESCALE_16
}timer2_clock_prescale_t;

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
}timer2_output_postscale_t;

typedef struct {
    timer2_clock_prescale_t prescale_value;
    timer2_output_postscale_t postscale_value;
    uint8_t timer2_interrupt : 1;
    void (*timer2_callback_interrupt_function)(void);
    uint8_t pr2_reg_value;
}timer2_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_timer2_init(timer2_t* timer2);

#endif	/* MCAL_TIMER2_H */
