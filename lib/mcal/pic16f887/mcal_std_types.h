/**
 ******************************************************************************
 * @file       std_types.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file includes a standard data types that be used in this project
 * @date       2023-11-18
 ******************************************************************************
*/
#ifndef HAL_STD_TYPES_H
#define	HAL_STD_TYPES_H

/* Includes -----------------------------------------------------------------*/

/* Macro Declarations -------------------------------------------------------*/
#define STD_HIGH                        0x01
#define STD_LOW                         0x00
#define STD_ON                          0x01
#define STD_OFF                         0x00
#define STD_ACTIVE                      0x01
#define STD_IDLE                        0x00
#define E_OK            (Std_ReturnType)0x01
#define E_NOT_OK        (Std_ReturnType)0x00
#define STD_ACTIVE                      0x01
#define STD_IDLE                        0x00

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef signed char      sint8_t;
typedef signed short     sint16_t;
typedef uint8_t          Std_ReturnType;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/

#endif	/* HAL_STD_TYPES_H */
