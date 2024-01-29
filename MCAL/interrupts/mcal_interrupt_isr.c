/**
 ******************************************************************************
 * @file       mcal_inter.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the implementations for char interrupts
 *             interfaces
 * @date       2023-12-10
 ******************************************************************************
*/
#include "mcal_interrupt_isr.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
void __interrupt(high_priority) ISR(void) {
    if (INTERRUPT_OCCURRED == INTCONbits.INT0IF) {
        int0_isr();
    }
    if (INTERRUPT_OCCURRED == INTCON3bits.INT1IF) {
        int1_isr();
    }
    if (INTERRUPT_OCCURRED == INTCON3bits.INT2IF) {
        int2_isr();
    }
    if (INTERRUPT_OCCURRED == PIR1bits.TMR2IF) {
        timer2_isr();
    }
  return;
}

void int0_isr(void){
    if (NULL != intx_isr_app_ptr[0]) {
        intx_isr_app_ptr[0]();
    }
    else {
        /* Nothing */
    }
    INT0_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
}

void int1_isr(void){
    if (NULL != intx_isr_app_ptr[1]) {
       intx_isr_app_ptr[1]();
    }
    else {
        /* Nothing */
    }
    INT1_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
}

void int2_isr(void){
    if (NULL != intx_isr_app_ptr[2]) {
        intx_isr_app_ptr[2]();
    }
    else {
        /* Nothing */
    }
    INT2_EXTERNAL_INTERRUPT_FLAGE_CLEAR();
}

void timer2_isr(void){
    if (NULL != timerx_isr_app_ptr[2]) {
       timerx_isr_app_ptr[2]();
    }
    else {
        /* Nothing */
    }
    TIMER2_INTERRUPT_FLAG_CLEAR();
}


