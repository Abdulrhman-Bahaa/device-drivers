/**
 ******************************************************************************
 * @file       mcal_interrupt.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes declarations for interrupts module
 * @date       2023-12-17
 ******************************************************************************
*/
#ifndef MCAL_INTERRUPT_H
#define	MCAL_INTERRUPT_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../gpio/mcal_gpio.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define GLOBAL_INTERRUPT_ENABLE()               (INTCONbits.GIE = 1)
#define GLOBAL_INTERRUPT_DISABLE()              (INTCONbits.GIE = 0)

#define INT0_EXTERNAL_INTERRUPT_ENABLE()        (INTCONbits.INT0IE = 1) 
#define INT0_EXTERNAL_INTERRUPT_DISABLE()       (INTCONbits.INT0IE = 0) 
#define INT0_EXTERNAL_INTERRUPT_FLAGE_CLEAR()   (INTCONbits.INT0IF = 0) 
#define INT0_EXTERNAL_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG0 = 1) 
#define INT0_EXTERNAL_INTERRUPT_FALING_EDGE()   (INTCON2bits.INTEDG0 = 0) 

#define INT1_EXTERNAL_INTERRUPT_ENABLE()        (INTCON3bits.INT1IE = 1) 
#define INT1_EXTERNAL_INTERRUPT_DISABLE()       (INTCON3bits.INT1IE = 0) 
#define INT1_EXTERNAL_INTERRUPT_FLAGE_CLEAR()   (INTCON3bits.INT1IF = 0)
#define INT1_EXTERNAL_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG1 = 1) 
#define INT1_EXTERNAL_INTERRUPT_FALING_EDGE()   (INTCON2bits.INTEDG1 = 0) 
#define INT1_EXTERNAL_INTERRUPT_PRIORITY_HIGH() (INTCON3bits.INT1IP = 1)
#define INT1_EXTERNAL_INTERRUPT_PRIORITY_LOW()  (INTCON3bits.INT1IP = 0) 

#define INT2_EXTERNAL_INTERRUPT_ENABLE()        (INTCON3bits.INT2IE = 1) 
#define INT2_EXTERNAL_INTERRUPT_DISABLE()       (INTCON3bits.INT2IE = 0) 
#define INT2_EXTERNAL_INTERRUPT_FLAGE_CLEAR()   (INTCON3bits.INT2IF = 0)
#define INT2_EXTERNAL_INTERRUPT_RISING_EDGE()   (INTCON2bits.INTEDG2 = 1) 
#define INT2_EXTERNAL_INTERRUPT_FALING_EDGE()   (INTCON2bits.INTEDG2 = 0) 
#define INT2_EXTERNAL_INTERRUPT_PRIORITY_HIGH() (INTCON3bits.INT2IP = 1)
#define INT2_EXTERNAL_INTERRUPT_PRIORITY_LOW()  (INTCON3bits.INT2IP = 0) 

#define RB_PORT_CHANGE_INTERRUPT_ENABLE()       (INTCONbits.RBIE = 1)
#define RB_PORT_CHANGE_INTERRUPT_DISABLE()      (INTCONbits.RBIE = 1)
#define RB_PORT_CHANGE_INTERRUPT_FLAG_CLEAR()   (INTCONbits.RBIF = 0)
#define RB_PORT_CHANGE_INTERRUPT_PRIORITY_HIGH()(INTCON2bits.RBIP = 1)
#define RB_PORT_CHANGE_INTERRUPT_PRIORITY_LOW() (INTCON2bits.RBIP = 0)

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

/* Variables Declarations ---------------------------------------------------*/
extern void (*isr_app_ptr[4])(void);

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_interrupt_intx_initialize(const intx_interrrupt_t* intx_interrrupt);
Std_ReturnType mcal_interrupt_intx_deinitialize(const intx_interrrupt_t* intx_interrrupt);
Std_ReturnType mcal_interrupt_intx_app_isr(const intx_interrrupt_t* intx_interrrupt);
Std_ReturnType mcal_interrupt_rb_change_initialize(const rb_change_interrrupt_t* rb_change_interrrupt);
Std_ReturnType mcal_interrupt_rb_change_deinitialize(const rb_change_interrrupt_t* rb_change_interrrupt);
Std_ReturnType mcal_interrupt_rb_change_app_isr(const rb_change_interrrupt_t* rb_change_interrrupt);


#endif	/* MCAL_INTERRUPT_H */






