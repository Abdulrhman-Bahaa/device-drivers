/**
 ******************************************************************************
 * \file       mcal_eeprom.h
 * \author     Abdulrhman Bahaa
 * \brief      This header file contains the declaration of eeprom interface
 * \date       2023-12-20
 ******************************************************************************
*/
#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/* Includes -----------------------------------------------------------------*/
#include <xc.h>
#include "../mcal_std_types.h"
#include "../interrupts/mcal_interrupt.h"

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_eeprom_data_write(const uint16_t address, const uint8_t data);
Std_ReturnType mcal_eeprom_data_read(const uint16_t address, uint8_t* data);

#endif	/* MCAL_EEPROM_H */