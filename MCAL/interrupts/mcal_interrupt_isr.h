/**
 ******************************************************************************
 * @file       mcal_inter.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for interrupts module
 * @date       2023-12-10
 ******************************************************************************
*/
#ifndef MCAL_INTERRUPT_ISR_H
#define	MCAL_INTERRUPT_ISR_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "mcal_interrupt.h"

/* Macro Declarations -------------------------------------------------------*/
#define INTERRUPT_OCCURRED   0X01

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
void int0_isr(void);
void int1_isr(void);
void int2_isr(void);
#endif	/* MCAL_INTERRUPT_ISR_H */






