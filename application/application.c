/**
 ******************************************************************************
 * @mainpage   8_bit_mcu_interfaces
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the main function for the application
 * @date       2023-11-17
 ******************************************************************************
*/
#include "application.h"

void fun0();
void fun1();
void fun2();

/* Variables Definitions ----------------------------------------------------*/ 
pin_config_t led0 = {
  .port = PORTC_INDEX,
.pin  = PIN0_INDEX,
  .direction = OUTPUT,
  .logic = LOW
};

pin_config_t led1 = {
  .port = PORTC_INDEX,
.pin  = PIN1_INDEX,
  .direction = OUTPUT,
  .logic = LOW
};

pin_config_t led2 = {
  .port = PORTC_INDEX,
.pin  = PIN2_INDEX,
  .direction = OUTPUT,
  .logic = LOW
};

intx_interrrupt_t int0 = {
  .intx_pin.port = PORTB_INDEX,
  .intx_pin.pin  = PIN0_INDEX,
  .intx_pin.direction = INPUT,
  .intx_pin.logic = LOW,
  .edge = INTX_INTERRUPT_RISING_EDGE,
  .priority = INTX_INTERRUPT_PRIORITY_HIGH,
  .intx_isr_app_ptr = &fun0
};

intx_interrrupt_t int1 = {
  .intx_pin.port = PORTB_INDEX,
  .intx_pin.pin  = PIN1_INDEX,
  .intx_pin.direction = INPUT,
  .intx_pin.logic = LOW,
  .edge = INTX_INTERRUPT_RISING_EDGE,
  .priority = INTX_INTERRUPT_PRIORITY_HIGH,
  .intx_isr_app_ptr = &fun1
};

intx_interrrupt_t int2 = {
  .intx_pin.port = PORTB_INDEX,
  .intx_pin.pin  = PIN2_INDEX,
  .intx_pin.direction = INPUT,
  .intx_pin.logic = LOW,
  .edge = INTX_INTERRUPT_FALING_EDGE,
  .priority = INTX_INTERRUPT_PRIORITY_HIGH,
  .intx_isr_app_ptr = &fun2
};

/* Main Function ------------------------------------------------------------*/
int main(void) {
    Std_ReturnType ret = E_OK;
    ret = application_initialize();
    ret = mcal_gpio_pin_initialize(&led0);
    ret = mcal_gpio_pin_initialize(&led1);
    ret = mcal_gpio_pin_initialize(&led2);
    ret = mcal_interrupt_intx_initialize(&int0);
    ret = mcal_interrupt_intx_initialize(&int1);
    ret = mcal_interrupt_intx_initialize(&int2);
    while(1) {
    }
    return (EXIT_SUCCESS);
}

/* Functions Implementations -------------------------------------------------*/
/**
 * @brief       This function will include calls of functions to initialize 
 *              application's interfaces
 * @return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
*/
Std_ReturnType application_initialize(void) {
    Std_ReturnType ret = E_OK;
    return ret;
}

void fun0(){
    mcal_gpio_pin_logic_write(&led0, HIGH);
}
void fun1(){
    mcal_gpio_pin_logic_write(&led1, HIGH);
}
void fun2(){
    mcal_gpio_pin_logic_write(&led2, HIGH);
}