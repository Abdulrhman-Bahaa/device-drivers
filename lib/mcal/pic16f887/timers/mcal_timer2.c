/**
 ******************************************************************************
 * \file       mcal_timer2.c
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes implementations for CCP1 module
 * \date       2024-1-26
 ******************************************************************************
*/
#include "mcal_timer2.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType  mcal_timer2_init(timer2_t* timer2){
    Std_ReturnType ret = E_OK;
    if (NULL == timer2) {
       ret = E_NOT_OK;
    }
    else {
        // Disable Timer2
        TIMER2_DISABLE();
        PR2 = timer2->pr2_reg_value;
        // Set the TMR2 prescale value
        T2CONbits.T2CKPS = timer2->prescale_value;
        // Set the output postscale value
        T2CONbits.TOUTPS = timer2->postscale_value;
        // Enable Timer2
        TIMER2_ENABLE();
    }
    return ret;
    
}
