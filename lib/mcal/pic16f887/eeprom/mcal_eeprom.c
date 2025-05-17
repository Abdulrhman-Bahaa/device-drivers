/**
 ******************************************************************************
 * \file       mcal_eeprom.c
 * \author     Abdulrhman Bahaa
 * \brief      This source file includes implementations of eeprom interfaces
 * \date       2023-12-20
 ******************************************************************************
*/
#include "mcal_eeprom.h"

/* Variables Definitions ----------------------------------------------------*/

/* Functions Implementations -------------------------------------------------*/
Std_ReturnType mcal_eeprom_data_write(const uint16_t address, const uint8_t data){
    Std_ReturnType ret = E_OK;
    EEADR = (uint8_t)(address & 0xFF);
    EEADRH = (uint8_t)((address >> 0x08) & 0x03);
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    EECON2 = 0x55; 
    EECON2 = 0xAA;
    GLOBAL_INTERRUPT_DISABLE();
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    EECON1bits.WREN = 0;
    return ret;  
}
Std_ReturnType mcal_eeprom_data_read(const uint16_t address, uint8_t* data){
    Std_ReturnType ret = E_OK;
    if(NULL == data) {
        ret = E_NOT_OK;
    }
    else {
        EEADR = (uint8_t)(address & 0xFF);
        EEADRH = (uint8_t)((address >> 0x08) & 0x03);
        EECON1bits.EEPGD = 0;
        EECON1bits.CFGS = 0;
        EECON1bits.RD = 1;
        NOP();
        NOP();
        *data = EEDATA;
    }
    return ret;  
}
