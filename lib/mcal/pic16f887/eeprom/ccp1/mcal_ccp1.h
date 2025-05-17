/**
 ******************************************************************************
 * \file       mcal_ccp1.h
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes declarations for CCP2 module
 * \date       2024-1-19
 ******************************************************************************
*/
#ifndef MCAL_CCP1_H
#define	MCAL_CCP1_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"
#include "../timers/mcal_timer2.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define CCP1_PWM_MODE() (CCP1CONbits.CCP1M = 0xF)
#define RESETS_CCP1_MODULE() (CCP1CON = 0)

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    RESETS_CCP1_MODULE = 0,
    RESERVED0,
    COMPARE_MODE_TOGGLE_OUTPUT_ON_MATCH,
    RESERVED1,
    CAPTURE_MODE_EVERY_FALLING_EDGE,
    CAPTURE_MODE_EVERY_RISING_EDGE,
    CAPTURE_MODE_EVER_4TH_RISING_EDGE,
    CAPTURE_EVERY_16TH_RISING_EDGE,
    COMPARE_INITIALIZE_CCP1_PIN_LOW_ON_COMPARE_MATCH_FORCE_CCP1_PIN_HIGH,
    COMPARE_INITIALIZE_CCP1_PIN_HIGH_ON_COMPARE_MATCH_FORCE_CCP1_PIN_LOW,
    COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT_ON_COMPARE_MATCH,
    COMPARE_MODE_TRIGGER_SPECIAL_EVENT_RESET_TIMER_CCP1_MATCH_STARTS_AD_CONVERSION,
    PWM_MODE
}ccp1_mode_select_t;

typedef struct {
    uint32_t fosc;
    timer2_t timer2;
    pin_config_t ccp1_pin;
    ccp1_mode_select_t ccp1_mode;
    uint32_t pwm_frequency;
    double pwm_duty_cycle;
}ccp1_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_pwm_period(ccp1_t* ccp1, uint8_t* pr2_reg_value);
Std_ReturnType mcal_pwm_duty_cycle(ccp1_t* ccp1);
Std_ReturnType mcal_pwm_init(ccp1_t* ccp1);

#endif	/* MCAL_CCP1_H */