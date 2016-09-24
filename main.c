/*
 * pixelpoi_mega328P.c
 *
 * Created: 26.08.2016 2:06:59
 * Author : Light
 */ 


//------------------------------------------------------
//F_CPU
//------------------------------------------------------

#define F_CPU 8000000UL

#define DTLOOP 3125

//------------------------------------------------------
//INCLUDE
//------------------------------------------------------

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "apa102.h"
#include "onebutton.h"
#include "macros.h"

//------------------------------------------------------
//GLOBAL VARIABLES
//------------------------------------------------------

static uint16_t tenmscout=DTLOOP;		//дополнительный делитель для таймера


//------------------------------------------------------
//INTERRUPT
//------------------------------------------------------

// переполнение таймера 0
ISR(TIMER0_COMPA_vect)
{
	
	tenmscout--;
	if (tenmscout==0)
	{
		tenmscout=DTLOOP;
		//button_scan(); //опрос кнопоки
		//PORTB^=(1<<5);		//XOR
		if (!GET(BTN_PIN,BTN_ONE))
		{
			SET(PORTB,5u);
		}
		else
		{
			CLR(PORTB,5u);
		}
	}
}

//------------------------------------------------------
//MAIN
//------------------------------------------------------

int main(void)
{
	buttonInit();
	SPI_Init();
	
	//настройка таймеров
	TCCR0A=00<<COM0A0|00<<COM0B0|2<<WGM00;	//порт отключен, режим сброса при совподении
	TCCR0B=00<<FOC0B|0<<WGM02|0b100<<CS00;	//,,делитель 256
	OCR0A=124;
	
	

    /* Replace with your application code */
    while (1) 
    {
		//setPixelColor(0,0,0,0);
		//for(uint8_t i=0; i<20; i++) setPixelColor(255,255,0,0);
		//_delay_ms(1000);
		//setPixelColor(0,0,0,0);
		//for(uint8_t i=0; i<20; i++) setPixelColor(255,0,255,0);
		//_delay_ms(1000);
		//setPixelColor(0,0,0,0);
		//for(uint8_t i=0; i<20; i++) setPixelColor(255,0,0,255);
		//_delay_ms(1000);
		//setPixelColor(0,0,0,0);
		//for(uint8_t i=0; i<20; i++) setPixelColor(255,255,255,255);
		//_delay_ms(1000);
    }
}

