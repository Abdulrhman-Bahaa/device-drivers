/**
 ******************************************************************************
 * @file       mcal_mssp.c
 * @author     Abdulrhman Bahaa
 * @brief      This source file contains implementations for the MSSP module
 *             functions
 * @date       2024-2-22
 ******************************************************************************
*/
#include "mcal_mssp.h"

/* Variables Definitions -----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_mssp_init(const mssp_config_t* mssp) {
    Std_ReturnType ret = E_OK;
    if (NULL == mssp) {
        ret |= E_NOT_OK;
    }
    else {
        MSSP_DISABLE();
        pin_config_t scl_local = {.port = mssp->scl_port, .pin = mssp->scl_pin};
        pin_config_t sda_local = {.port = mssp->sda_port, .pin = mssp->sda_pin};       
        // Configure SCL and SDA as inputs
        ret |= mcal_gpio_pin_direction_initialize(&scl_local, INPUT);
        ret |= mcal_gpio_pin_direction_initialize(&sda_local, INPUT); 
        switch(mssp->mode) {
            case MSSP_I2C_MASTER_MODE_FOSC_DIV_BY_4_SSPADD_PLUS_1:
                SSPCONbits.SSPM = MSSP_I2C_MASTER_MODE_FOSC_DIV_BY_4_SSPADD_PLUS_1;
                SSPADD = (_XTAL_FREQ / ((mssp->serial_clock) * 4)) - 1;
                break;       
            default:
                ret = E_NOT_OK;
        }
        
        if (INERRUPT_ENABLED == mssp->interrupt_enable) {
            ret |= mcal_interrupt_mssp_init(&(mssp->interrupts_callbacks));
        }    
        else {
            MSSP_INTERRUPT_DISABLE();
        }
        SSPCON2bits.ACKSTAT = 1;
        MSSP_ENABLE();
    }
    return ret;
}

Std_ReturnType mcal_mssp_address_trasnmit(const uint8_t slave_address, mssp_master_operation_t master_operation) {
    Std_ReturnType ret = E_OK;
    mcal_mssp_data_trasnmit(slave_address | master_operation);
    return ret;
}

Std_ReturnType mcal_mssp_data_trasnmit(const uint8_t data_to_transmit) {
    Std_ReturnType ret = E_OK;
    SSPBUF = data_to_transmit;
    while(SSPSTATbits.R_W);
    return ret;
}

void mcal_mssp_start_condition(void) {
    SSPCON2bits.SEN = 1;
    while(SSPCON2bits.SEN);
}

void mcal_mssp_stop_condition(void) {
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
}
