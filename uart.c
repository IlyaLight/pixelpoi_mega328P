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


void send_Uart(uint8_t c)//ќтправка байта
{
	while(!(UCSR0A&(1<<UDRE0)))    //  ”станавливаетс€, когда регистр свободен
	{}
	UDR0 = c;
}

//  ќтправка строки
void send_Uart_str(char *s)
{

	while (*s != 0) send_Uart(*s++);

}

//отправить байт в виде строки, в двоичном формате
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

//преобразует HEX из value в DEC записаную в buffer, 
//возвращает ссылку на начало числа в buffer
char * utoa_fast_div(uint32_t value, char *buffer)
{
	// 11 байт достаточно дл€ дес€тичного представлени€ 32-х байтного числа
	// и  завершающего нул€
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
/*¬ыгл€дит страшно и непон€тно, но на самом деле всЄ просто. —начала умножаем 
исходное число на 0.8 или 0.1100 1100 1100 1100 1100 1100 1100 1100 в двоичном 
представлении. ќчень удобно, что дробь периодическа€ и удалось обойтись всего 
п€тью сдвигами и четырьм€ сложени€ми. ƒалее делим то, что получилось на 8, 
сдвига€ на 3 разр€да вправо. ѕолучаетс€ исходное число делЄнное на 10 с 
точностью до единицы из-за ошибок округлени€. ѕосле находим остаток умножа€ 
полученное частное на 10 и вычита€ его из исходного числа. ≈сли остаток больше 
9, то корректируем его и частное.
http://we.easyelectronics.ru/Soft/preobrazuem-v-stroku-chast-1-celye-chisla.html*/
struct divmod10_t divmodu10(uint32_t n)
{
	struct divmod10_t res;
	// умножаем на 0.8
	res.quot = n >> 1;
	res.quot += res.quot >> 1;
	res.quot += res.quot >> 4;
	res.quot += res.quot >> 8;
	res.quot += res.quot >> 16;
	uint32_t qq = res.quot;
	// делим на 8
	res.quot >>= 3;
	// вычисл€ем остаток
	res.rem = (uint8_t)(n - ((res.quot << 1) + (qq & ~7ul)));
	// корректируем остаток и частное
	if(res.rem > 9)
	{
		res.rem -= 10;
		res.quot++;
	}
	return res;
}