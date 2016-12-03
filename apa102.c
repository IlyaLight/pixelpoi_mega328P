/*
 * apa102.c
 *
 * Created: 27.08.2016 15:25:34
 *  Author: Light
 */ 
#include "apa102.h"
#include <avr/io.h>
#include "macros.h"











// start Freme
void startFrame(void)
{
	spi_Transmit(0);
	spi_Transmit(0);
	spi_Transmit(0);
	spi_Transmit(0);
}

// transmit data on SPI
void spi_Transmit(uint8_t data)
{
//	CLI
	SPDR=data;						//start transmit
	while(!(SPSR & (1<<SPIF)));		//wait until the transmit is complete
//	SEI
}


void setPixelColorRGB(uint8_t r, uint8_t g, uint8_t b)
{
	spi_Transmit(255);
	spi_Transmit(b);
	spi_Transmit(g);
	spi_Transmit(r);
}


void setPixeslColor(uint8_t *data[])
{	

}

//clear all pixels
void clearPixes()
{
	startFrame();
	
	for (uint8_t t = numPixels; t; t--)
	{
		spi_Transmit(255);
		spi_Transmit(0);
		spi_Transmit(0);
		spi_Transmit(0);
	}
}


