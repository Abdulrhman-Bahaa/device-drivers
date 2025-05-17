/**
 ******************************************************************************
 * \file       mcal_ccp1.c
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes implementations for CCP1 module
 * \date       2024-1-19
 ******************************************************************************
*/
#include "mcal_ccp1.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_pwm_init(ccp1_t* ccp1){
    Std_ReturnType ret = E_OK;
    if (NULL == ccp1) {
       ret = E_NOT_OK;
    }
    else {
        uint8_t pr2_reg_value = 0;
        RESETS_CCP1_MODULE();
        // Set the PWM period
        ret = mcal_pwm_period(ccp1, &pr2_reg_value);
        ccp1->timer2.pr2_reg_value = pr2_reg_value;
        ret = mcal_timer2_init((&ccp1->timer2));
        // Set the PWM duty cycle
        ret = mcal_pwm_duty_cycle(ccp1);
        // Make the CCPx pin an output
        ret = mcal_gpio_pin_direction_initialize(&(ccp1->ccp1_pin));
        // Configure the CCPx module for PWM operation.
        CCP1_PWM_MODE();
    }
    return ret;
    
}

Std_ReturnType mcal_pwm_period(ccp1_t* ccp1, uint8_t* pr2_reg_value){
    Std_ReturnType ret = E_OK;
    if (NULL == ccp1) {
       ret = E_NOT_OK;
    }
    else {   
        float pwm_period = 1.0 / (ccp1->pwm_frequency);
        uint8_t prescale_value = 0;
        switch(ccp1->timer2.prescale_value){
            case PRESCALE_1:
                prescale_value = 1 ;
                break;
            case PRESCALE_4:
                prescale_value = 4 ;
                break;
            case PRESCALE_16:
                prescale_value = 16 ;
                break;
            default:
                ret = E_NOT_OK;    
        }
        *pr2_reg_value = (uint8_t)(((pwm_period * (ccp1->fosc)) / (4 * prescale_value)) - 1);
    }
    return ret;
}

Std_ReturnType mcal_pwm_duty_cycle(ccp1_t* ccp1){
    Std_ReturnType ret = E_OK;
    if (NULL == ccp1) {
        ret = E_NOT_OK;
    }
    else {
        uint16_t CCPR1L_CCP1CON_5_4 = 0;
        CCPR1L_CCP1CON_5_4 = 4 * (ccp1->pwm_duty_cycle) * (PR2 + 1);
        CCP1CONbits.DC1B = CCPR1L_CCP1CON_5_4 & 0x003;
        CCPR1L = (uint8_t) (CCPR1L_CCP1CON_5_4 >> 2);
    }
     return ret;
}
