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
    if (INTERRUPT_OCCURRED == INTCONbits.TMR0IF) {
        timer0_isr();
    }
    if (INTERRUPT_OCCURRED == PIR1bits.TMR1IF) {
        timer1_isr();
    }
    if (INTERRUPT_OCCURRED == PIR1bits.TMR2IF) {
        timer2_isr();
    }
    if (INTERRUPT_OCCURRED ==  PIR1bits.CCP1IF) {
        ccp1_isr();
    }
    if (INTERRUPT_OCCURRED == PIR1bits.TXIF) {
        usart_transmit_isr();
    }
    if (INTERRUPT_OCCURRED == PIR1bits.RCIF) {
        usart_receive_isr();
    }
  return;
}


void timer0_isr(void){
    if (NULL != timerx_isr_app_ptr[0]) {
       timerx_isr_app_ptr[0]();
    }
    else {
        /* Nothing */
    }
    TIMER0_INTERRUPT_FLAG_CLEAR();
}

void timer1_isr(void){
    if (NULL != timerx_isr_app_ptr[1]) {
       timerx_isr_app_ptr[1]();
    }
    else {
        /* Nothing */
    }
    TIMER1_INTERRUPT_FLAG_CLEAR();
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

void ccp1_isr(void){
    if (NULL != ccpx_isr_app_ptr[0]) {
       ccpx_isr_app_ptr[0]();
    }
    else {
        /* Nothing */
    }
    CCP1_INTERRUPT_FLAG_CLEAR();
}

void usart_transmit_isr(void){
    if (NULL != usart_transmit_isr_app_ptr) {
       usart_transmit_isr_app_ptr();
    }
    else {
        /* Nothing */
    }
}

void usart_receive_isr(void){
    if (NULL != usart_receive_isr_app_ptr) {
       usart_receive_isr_app_ptr();
    }
    else {
        /* Nothing */
    }
}

