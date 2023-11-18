/**
 ******************************************************************************
 * @file       application.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes header files from ECUA_layer and
 *             function declaration.
 * @date       2023-11-18
 * @details    This header file includes header files from ECUA_layer and
 *             function declaration.
 ******************************************************************************
*/
#ifndef APPLICATION_H
#define	APPLICATION_H

/* Includes -----------------------------------------------------------------*/
#include "../MCA_layer/hal_std_types.h"     /**< Std_ReturnType, uint8, etc..*/

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
/**
 * @brief       This function will include calls of functions to initialize 
 *              application's interfaces
 * @return      Returns E_OK(0x01) or E_NOT_OK(0x00) (succeeded and not succeeded)
*/
Std_ReturnType application_initialize();

#endif	/* APPLICATION_H */

