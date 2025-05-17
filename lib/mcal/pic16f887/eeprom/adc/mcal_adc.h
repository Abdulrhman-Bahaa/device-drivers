/**
 ******************************************************************************
 * \file       mcal_adc.h
 * \author     Abdulrhman Bahaa
 * \brief      This header file contains the declaration of adc interface
 * \date       2023-12-27
 ******************************************************************************
*/
#ifndef MCAL_ADC_H
#define	MCAL_ADC_H

/* Includes -----------------------------------------------------------------*/

/* Macro Declarations -------------------------------------------------------*/

/* Macro Functions Declarations ---------------------------------------------*/
#define ADC_ENABLE   (ADCON0bits.ADON = 1)
#define ADC_DISABLE  (ADCON0bits.ADON = 0)

/* Data Type Declarations ---------------------------------------------------*/

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/

#endif	/* MCAL_ADC_H */

