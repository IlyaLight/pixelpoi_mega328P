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
#include "pixelpoi.h"
#include "macros.h"


//------------------------------------------------------
//GLOBAL VARIABLES
//------------------------------------------------------

static uint8_t tenmscout=DTLOOP;		//�������������� �������� ��� �������
static volatile uint8_t status=0;
#define TICK	0
#define SHOWIMG	1


//------------------------------------------------------
//INTERRUPT
//------------------------------------------------------

// ������������ ������� 0
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
	
	//��������� ��������
	TCCR0A=00<<COM0A0|00<<COM0B0|2<<WGM00;	//���� ��������, ����� ������ ��� ���������� � OCR0A
	TCCR0B=00<<FOC0B|0<<WGM02|0b100<<CS00;	//,,�������� 256
	TCNT1=0x00;								//����� ������������� ����
	OCR0A=(125-1);
	
	//�������� ����������
	TIMSK0|=0<<TOIE0|1<<OCIE0A;		//on interrupt overflow timer
	asm("sei");						//on global interrupt
	
	
	
	imageInit();

    /* Replace with your application code */
	while (1) 
	{
		
		
		if(GET(status,SHOWIMG))
		{
			imageLoop();
		}
		else
		{
			clearPixes();
		}
		if (GET(status,TICK))
		{
			switch(button_scan())
			{
				case BSC_ShorClik:
				XOR(status, SHOWIMG);
				break;
				
				case BSC_LongClik:
				nextImage();
				break;
				
				case BSC_DoubClik:
				
				break;
				
				case BSC_TripClik:
				
				break;
				
			}
			
			CLR(status, TICK);
		}
		
		
	}
    
}

