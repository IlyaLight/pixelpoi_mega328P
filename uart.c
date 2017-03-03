/*
 * uart.c
 *
 * Created: 02.11.2016 0:21:48
 *  Author: Light
 */ 


#include <avr/io.h>
#include "macros.h"

struct divmod10_t
{
	uint32_t quot;
	uint8_t rem;
};


char * utoa_fast_div(uint32_t , char *);
struct divmod10_t divmodu10(uint32_t);


void send_Uart(uint8_t c)//�������� �����
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

//��������� ���� � ���� ������, � �������� �������
void send_Uart_BIN(uint8_t c)
{
	send_Uart_str("0b");
	for(uint8_t t = 8; t!=0;)
	{
		t--;
		if GET(c,t) send_Uart(0x31);
		else send_Uart(0x30);
	}
	
}

void send_Uart_DEC(uint32_t c)
{
	char buffer[11];
	send_Uart_str(utoa_fast_div(c, buffer));
}

void send_Uart_DECM(uint8_t c[])
{	
	uint32_t value=0;
	for(uint8_t t = 4; t!=0;)
	{
		t--;
		value+=(((uint32_t)c[t])<<(t*8));
	}
	send_Uart_DEC(value);
}

//����������� HEX �� value � DEC ��������� � buffer, 
//���������� ������ �� ������ ����� � buffer
char * utoa_fast_div(uint32_t value, char *buffer)
{
	// 11 ���� ���������� ��� ����������� ������������� 32-� �������� �����
	// �  ������������ ����
	buffer += 11;
	*--buffer = 0;
	do
	{
		struct divmod10_t res = divmodu10(value);
		*--buffer = res.rem + '0';
		value = res.quot;
	}
	while (value != 0);
	return buffer;
}
/*�������� ������� � ���������, �� �� ����� ���� �� ������. ������� �������� 
�������� ����� �� 0.8 ��� 0.1100 1100 1100 1100 1100 1100 1100 1100 � �������� 
�������������. ����� ������, ��� ����� ������������� � ������� �������� ����� 
����� �������� � �������� ����������. ����� ����� ��, ��� ���������� �� 8, 
������� �� 3 ������� ������. ���������� �������� ����� ������� �� 10 � 
��������� �� ������� ��-�� ������ ����������. ����� ������� ������� ������� 
���������� ������� �� 10 � ������� ��� �� ��������� �����. ���� ������� ������ 
9, �� ������������ ��� � �������.
http://we.easyelectronics.ru/Soft/preobrazuem-v-stroku-chast-1-celye-chisla.html*/
struct divmod10_t divmodu10(uint32_t n)
{
	struct divmod10_t res;
	// �������� �� 0.8
	res.quot = n >> 1;
	res.quot += res.quot >> 1;
	res.quot += res.quot >> 4;
	res.quot += res.quot >> 8;
	res.quot += res.quot >> 16;
	uint32_t qq = res.quot;
	// ����� �� 8
	res.quot >>= 3;
	// ��������� �������
	res.rem = (uint8_t)(n - ((res.quot << 1) + (qq & ~7ul)));
	// ������������ ������� � �������
	if(res.rem > 9)
	{
		res.rem -= 10;
		res.quot++;
	}
	return res;
}