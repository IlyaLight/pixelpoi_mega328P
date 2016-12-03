/*
 * uart.c
 *
 * Created: 02.11.2016 0:21:48
 *  Author: Light
 */ 


#include <avr/io.h>
#include "macros.h"



void send_Uart(uint8_t c)//   �������� �����
{
	while(!(UCSR0A&(1<<UDRE0)))    //  ���������������, ����� ������� ��������
	{}
	UDR0 = c;
}

//  �������� ������
void send_Uart_str(char *s)
{

	while (*s != 0) send_Uart(*s++);

}

//��������� ���� � ���� ������ � ������ ("1" "0")
void send_Uart_SHbit(uint8_t c)
{
	send_Uart_str("0b");
	for(uint8_t t = 8; t!=0;)
	{
		t--;
		if GET(c,t) send_Uart(0x31);
		else send_Uart(0x30);
	}
	
}