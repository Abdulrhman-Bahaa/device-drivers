/**
 ******************************************************************************
 * \file       mcal_mssp.h
 * \author     Abdulrhman Bahaa
 * \brief      This header file includes declarations of MSSP module
 * \date       2024-2-22
 ******************************************************************************
*/
#ifndef MCAL_MSSP_H
#define	MCAL_MSSP_H

/* Includes -----------------------------------------------------------------*/
#include "../mcal_std_types.h"
#include "../gpio/mcal_gpio.h"
#include "../interrupts/internal/mcal_internal_interrupts.h"

/* Macro Declarations -------------------------------------------------------*/
#define MSSP_ENABLE()    (SSPCONbits.SSPEN = 1)
#define MSSP_DISABLE()   (SSPCONbits.SSPEN = 0)

/* Macro Functions Declarations ---------------------------------------------*/

/* Data Type Declarations ---------------------------------------------------*/
typedef enum {
    MSSP_SPI_MASTER_MODE_FOSC_DIV_4 = 0,
    MSSP_SPI_MASTER_MODE_FOSC_DIV_16,
    MSSP_SPI_MASTER_MODE_FOSC_DIV_64,
    MSSP_SPI_MASTER_MODE_TMR2_OUTPUT_DIV_2,
    MSSP_SPI_SLAVE_MODE_SCK_PIN_SS_PIN_CONTROL_ENABLED,
    MSSP_SPI_SLAVE_MODE_SCK_PIN_SS_PIN_CONTROL_DISABLED_SS_CAN_BE_USED_AS_IO_PIN,
    MSSP_I2C_SLAVE_MODE_7_BIT_ADDRESS,
    MSSP_I2C_SLAVE_MODE_10_BIT_ADDRESS,
    MSSP_I2C_MASTER_MODE_FOSC_DIV_BY_4_SSPADD_PLUS_1,
    MSSP_LOAD_MASK_FUNCTION,
    MSSP_RESERVED_1,
    MSSP_I2C_FIRMWARE_CONTROLLED_MASTER_MODE_SLAVE_IDLE,
    MSSP_RESERVED_2,
    MSSP_RESERVED_3,
    MSSP_I2C_SLAVE_MODE_7_BIT_ADDRESS_WITH_START_AND_STOP_BIT_INTERRUPTS_ENABLED,
    MSSP_I2C_SLAVE_MODE_10_BIT_ADDRESS_WITH_START_AND_STOP_BIT_INTERRUPTS_ENABLED
}mssp_mode_t;

typedef enum {
    WRITE = 0,
    READ
}mssp_master_operation_t;

typedef struct {
    port_index_t scl_port;
    pin_index_t scl_pin;
    port_index_t sda_port;
    pin_index_t sda_pin;
    uint32_t serial_clock;
    mssp_mode_t mode;
    uint8_t interrupt_enable : 1;
    mssp_interrupt_config_t interrupts_callbacks;
}mssp_config_t;

/* Variables Declarations ---------------------------------------------------*/

/* Functions Declarations ---------------------------------------------------*/
Std_ReturnType mcal_mssp_init(const mssp_config_t* mssp);
void mcal_mssp_start_condition(void);
void mcal_mssp_stop_condition(void);
Std_ReturnType mcal_mssp_address_trasnmit(const uint8_t slave_address, mssp_master_operation_t master_operation);
Std_ReturnType mcal_mssp_data_trasnmit(const uint8_t data_to_transmit);

#endif	/* MCAL_MSSP_H */
