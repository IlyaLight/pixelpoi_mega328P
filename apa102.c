/*
 * apa102.c
 *
 * Created: 27.08.2016 15:25:34
 *  Author: Light
 */ 
#include "apa102.h"
#include <avr/io.h>







void SPI_Transmit(uint8_t data);

// Initialization SPI
void SPI_Init(void)
{
	DDR_SPI = (1<<DD_MISI)|(1<<DD_SCK)|(1<<DD_SS);					//MISO leg as out
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	//SPI on, mater, SCK 1MHz
	SPSR =	(SPI2<<SPI2X);

}

// transmit data on SPI
void SPI_Transmit(uint8_t data)
{
	SPDR=data;						//start transmit
	while(!(SPSR & (1<<SPIF)));		//wait until the transmit is complete
}

void setPixelColor(uint8_t *data[])
{	
	pixels=data;
}


void clear()
{
	
}



if (Pressed) 
{ // Кнопень придавлена. Тупо считаем время придавки.
    if (bt_time<0x7F) bt_time++;
} 
else if (bt_time>0) 
{ //  Момент отпускания кнопки.
    if (bt_time>=long_press) bt_result|=(1<<bt_cnt); // Длинное нажатие. Ставим единичку в битовое поле результата.
    bt_cnt++; // Короткое нажатие. Пропускаем установку бита.
    if (check_bit_map(bt_result, bt_cnt) || bt_cnt==command_max_len) 
    { // Первое условие - функция проверки совпадения битмапа комманды. Второе - комманда завершена по максимальному количеству нажатий(8), сброс состояний
      bt_cnt=0;
      bt_result=0;
    }
    bt_time=0; // время придавки кнопки нам больше не нужно, сбрасываем. 
} 
else if (bt_cnt>0 && bt_time>-release_timeout) 
{ // Отпущено, счетчик таймаута комманды(последовательности). Здесь мы еще ждем ввода нажатий для последовательности.
    if (bt_time>-0x7F) bt_time--; // эту же переменную используем для отсчета таймаута ожидания завершения комманды после последней нажатой кнопки. Только паузу в минусовую сторону считаем. Знаковый байт дает нам 127 значений плюса и 127 минуса. нам более чем достаточно
} 
else if (bt_result>0 || bt_cnt>0) 
{ // Таймаут комманды, сброс состояний
    check_bit_map(bt_result, bt_cnt);
    bt_cnt=0;   
    bt_result=0;
}
  SetTimerTask(bt_scan, scan_interval);    // Зациклились через диспетчер.
}