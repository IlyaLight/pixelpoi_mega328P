/*
 * uart.h
 *
 * Created: 02.11.2016 0:28:35
 *  Author: Light
 */ 


#ifndef UART_H_
#define UART_H_


void send_Uart(uint8_t);
void send_Uart_str(char*);
void send_Uart_BIN(uint8_t);
void send_Uart_DEC(uint32_t);
void send_Uart_DECM(uint8_t c[]);



#endif /*  UART_H_ */