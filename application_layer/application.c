/**
 ******************************************************************************
 * @mainpage   8_bit_mcu_interfaces
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains the main function for the application
 * @date       2023-11-17
 * @details    Two function included : main and application_initialization
 ******************************************************************************
*/
#include "application.h"

/* Variables Definitions ----------------------------------------------------*/

/* Main Function ------------------------------------------------------------*/
int main(void) {
    Std_ReturnType ret = E_OK;
    ret = application_initialize();
    while(1) {
    }
    return 0;
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