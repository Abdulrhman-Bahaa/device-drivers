/**
 ******************************************************************************
 * \mainpage   Example Application for GPIO driver
 * \file       gpio.c
 * \author     Abdulrhman Bahaa
 * \brief      This source file contains the main function and the application
 * \date       2025-04-10
 ******************************************************************************
 */
/* Includes -----------------------------------------------------------------*/
#include <atmega328p/gpio/mcal_gpio.h>

/* Declarations -------------------------------------------------------------*/
Std_ReturnType app_init(void);

/* Variables Definitions ----------------------------------------------------*/ 
/* Pin Configuration */
const pin_config_t pin_8 = {
  .port = PORTB_INDEX,
  .pin = PIN0_INDEX,
  .direction = OUTPUT,
  .logic = LOW
};

const pin_config_t pin_9 = {
  .port = PORTB_INDEX,
  .pin = PIN1_INDEX,
  .direction = INPUT,
  .logic = LOW
};

/* Main Function ------------------------------------------------------------*/
int main(void) {
  Std_ReturnType ret = E_OK;
  if (app_init() != E_OK) {
    /* Error Handling */
    while (1);  /* Halt on init failure */ 
  }
  logic_t pin_9_logic = LOW;
  while(1) {
    if (E_OK == ret) {
      ret |= mcal_gpio_pin_logic_read(&pin_9, &pin_9_logic);
      if (HIGH == pin_9_logic) {
        ret |= mcal_gpio_pin_logic_write(&pin_8, HIGH);
      } else {
        ret |= mcal_gpio_pin_logic_write(&pin_8, LOW);
      }
    } else {
      /* Error Handling */
      ret = E_NOT_OK;
    }
  }
  return 0;
}

/* Functions Implementations -------------------------------------------------*/
/**
 * \brief       This function will include calls of functions to initialize 
 *              application's interfaces
 * \return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
*/
Std_ReturnType app_init(void) {
  Std_ReturnType ret = E_OK;
  /* Initialize GPIO */
  ret |= mcal_gpio_pin_init(&pin_8);
  ret |= mcal_gpio_pin_init(&pin_9);
  return ret;
}
