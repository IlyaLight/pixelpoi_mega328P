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

//------------------------------------------------------
//INCLUDE
//------------------------------------------------------

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <pgmspace.h>
#include "apa102.h"

//------------------------------------------------------
//GLOBAL VARIABLES
//------------------------------------------------------



//------------------------------------------------------
//INTERRUPT
//------------------------------------------------------



//------------------------------------------------------
//MAIN
//------------------------------------------------------

int main(void)
{
	SPI_Init();
    /* Replace with your application code */
    while (1) 
    {
		setPixelColor(0,0,0,0);
		for(uint8_t i=0; i<20; i++) setPixelColor(255,255,0,0);
		_delay_ms(1000);
		setPixelColor(0,0,0,0);
		for(uint8_t i=0; i<20; i++) setPixelColor(255,0,255,0);
		_delay_ms(1000);
		setPixelColor(0,0,0,0);
		for(uint8_t i=0; i<20; i++) setPixelColor(255,0,0,255);
		_delay_ms(1000);
		setPixelColor(0,0,0,0);
		for(uint8_t i=0; i<20; i++) setPixelColor(255,255,255,255);
		_delay_ms(1000);
    }
}

