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

#define DTLOOP 5

//------------------------------------------------------
//INCLUDE
//------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "apa102.h"
#include "apa102.h"
#include "onebutton.h"
#include "macros.h"

//------------------------------------------------------
//GLOBAL VARIABLES
//------------------------------------------------------

static uint8_t tenmscout=DTLOOP;		//дополнительный делитель для таймера
static volatile uint8_t status=0;
#define TICK 0


//------------------------------------------------------
//INTERRUPT
//------------------------------------------------------

// переполнение таймера 0
ISR(TIMER0_COMPA_vect)
{	
	if(--tenmscout==0)
	{
		SET(status,TICK);
		tenmscout=DTLOOP;

			//if (!GET(PIND,2u))
			//{
				//SET(PORTB,5u);
			//}
			//else
			//{
				//CLR(PORTB,5u);
			//}
			
	}
}

//------------------------------------------------------
//MAIN
//------------------------------------------------------

int main(void)
{
	button_init();
	spi_Init();
	
	//настройка таймеров
	TCCR0A=00<<COM0A0|00<<COM0B0|2<<WGM00;	//порт отключен, режим сброса при совподении с OCR0A
	TCCR0B=00<<FOC0B|0<<WGM02|0b100<<CS00;	//,,делитель 256
	TCNT1=0x00;								//здесь увеличиваются тики
	OCR0A=(125-1);
	
	//включаем прерывания
	TIMSK0|=0<<TOIE0|1<<OCIE0A;		//on interrupt overflow timer
	asm("sei");						//on global interrupt
	
	

    /* Replace with your application code */
	while (1) 
	{
		if (GET(status,TICK))
		{
			switch(button_scan())
			{
				case BSC_ShorClik:
					startFreme();
					setPixelColor(10,10,0);
					setPixelColor(20,20,0);
					setPixelColor(40,40,0);
					setPixelColor(80,80,0);
					setPixelColor(125,125,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
				break;
			
				case BSC_LongClik:
					startFreme();
					setPixelColor(20,0,0);
					setPixelColor(40,0,0);
					setPixelColor(105,0,0);
					setPixelColor(170,0,0);
					setPixelColor(225,0,0);		
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);	
				break;
			
				case BSC_DoubClik:
					startFreme();
					setPixelColor(0,20,0);
					setPixelColor(0,40,0);
					setPixelColor(0,225,0);
					setPixelColor(0,0,0);
					setPixelColor(0,20,0);
					setPixelColor(0,40,0);
					setPixelColor(0,225,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
					setPixelColor(0,0,0);
				break;
			
				case BSC_TripClik:
					startFreme();
					setPixelColor(0,0,20);
					setPixelColor(0,0,40);
					setPixelColor(0,0,225);
					setPixelColor(0,0,0);
					setPixelColor(0,0,20);
					setPixelColor(0,0,40);
					setPixelColor(0,0,225);
					setPixelColor(0,0,0);
					setPixelColor(0,0,20);
					setPixelColor(0,0,40);
					setPixelColor(0,0,225);
					setPixelColor(0,0,0);
				break;
			
			}
			
			CLR(status, TICK);
		}
	}
    
}

