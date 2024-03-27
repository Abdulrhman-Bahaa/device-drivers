 /**
 ******************************************************************************
 * @file       ecual_wifi_module.h
 * @author     Abdulrhman Bahaa
 * @brief      This header file contains the implementations for wifi module
 *             interfaces
 * @date       2024-3-08
 ******************************************************************************
*/
#include "ecual_wifi_module.h"

/* Global Variables ---------------------------------------------------------*/

/* Functions Implementations ------------------------------------------------*/
Std_ReturnType ecual_wifi_module_init(void) {
    Std_ReturnType ret = E_OK;
    usart_config_t usart_local = {
        .mode = USART_ASYNCHRONOUS_MODE,
        .ubrr_value = 16,
        .device_state = USART_TRANSMITTER_RECEIVER,
        .usart_interrupt = 0,
        .usart_receive_callback_interrupt_function = NULL
    };
    ret |= mcal_usart_init(&usart_local);
    return ret;
}

Std_ReturnType ecual_wifi_module_wifi_connect(const char* wifi_ssid, const char* wifi_pwd) {
    Std_ReturnType ret = E_OK;
    // Station mode
    ret |= mcal_usart_transmit_string("AT+CWMODE=1\r\n");
    _delay_ms(100);
    uint8_t command[60] =  "AT+CWJAP=\"";
    uint8_t i = 0;
    strcat(command, wifi_ssid);
    strcat(command, "\",\"");
    strcat(command, wifi_pwd);
    strcat(command, "\"\r\n");
    ret |= mcal_usart_transmit_string(command);
    return ret;
}

Std_ReturnType ecual_wifi_module_http_request(const char* method, const char* host, const char* target_path) {
    Std_ReturnType ret = E_OK;
     uint8_t tcp_connection[39] =  "AT+CIPSTART=\"TCP\",\"";
     uint8_t data_length_str[5];
     uint8_t data_length = 41;
     strcat(tcp_connection, host);
     strcat(tcp_connection, "\",80\r\n");
    data_length += strlen(method);
    data_length += strlen(target_path);
    data_length += strlen(host);
    ret |= mcal_usart_transmit_string(tcp_connection);
    _delay_ms(1000);
    sprintf(data_length_str, "%d", data_length);
    ret |= mcal_usart_transmit_string("AT+CIPSEND=");
    ret |= mcal_usart_transmit_string(data_length_str);
    ret |= mcal_usart_transmit_string("\r\n");
    _delay_ms(500);
    ret |= mcal_usart_transmit_string(method);
    ret != mcal_usart_transmit_data(' ');
    ret |= mcal_usart_transmit_string(target_path);
    ret |= mcal_usart_transmit_string(" HTTP/1.1\r\n");
    ret |= mcal_usart_transmit_string("Host: ");
    ret |= mcal_usart_transmit_string(host);
    ret |= mcal_usart_transmit_string("\r\n");
    ret |= mcal_usart_transmit_string("Connection: close\r\n\r\n");
    return ret;
}


