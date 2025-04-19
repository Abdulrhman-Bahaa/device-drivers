/**
 ******************************************************************************
 * @file       mcal_std_types.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes a standard data types that be used in this project
 * @date       2024-2-09
 ******************************************************************************
*/
#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Includes -----------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>

/* Macro Declarations -------------------------------------------------------*/
#define BIT_MASK                        0x01
#define STD_ON                          0x01
#define STD_OFF                         0x00
#define E_OK            (Std_ReturnType)0x00
#define E_NOT_OK        (Std_ReturnType)0x01

/* Macro Functions Declarations ---------------------------------------------*/
#define SET_BIT(REG, BIT_POSN)               (REG |= (BIT_MASK <<  BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)             (REG &= ~(BIT_MASK <<  BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)            (REG ^= (BIT_MASK <<  BIT_POSN))
#define READ_BIT(REG, BIT_POSN)              ((REG >> BIT_POSN) & BIT_MASK )

/* Data Type Declarations ---------------------------------------------------*/
typedef uint8_t         Std_ReturnType;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/

#endif	/* MCAL_STD_TYPES_H */
