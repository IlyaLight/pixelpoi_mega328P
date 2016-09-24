/*
 * apa102.c
 *
 * Created: 27.08.2016 15:25:34
 *  Author: Light
 */ 
#include "apa102.h"
#include <avr/io.h>










// start Freme
void startFreme(void)
{
	spi_Transmit(0);
	spi_Transmit(0);
	spi_Transmit(0);
	spi_Transmit(0);
}

// transmit data on SPI
void spi_Transmit(uint8_t data)
{
	SPDR=data;						//start transmit
	while(!(SPSR & (1<<SPIF)));		//wait until the transmit is complete
}



// Initialization SPI
void spi_Init(void)
{
	DDR_SPI = (1<<DD_MISI)|(1<<DD_SCK)|(1<<DD_SS);	//MISO leg as out
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	//SPI on, mater, SCK 1MHz
	SPSR =	(SPI2<<SPI2X);

}


void setPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
	spi_Transmit(255);
	spi_Transmit(r);
	spi_Transmit(g);
	spi_Transmit(b);
}


void setPixeslColor(uint8_t *data[])
{	

}

//clear all pixels
void clearPixes()
{
	startFreme();
	
	for (uint8_t t = numPixels; t; t--)
	{
		spi_Transmit(255);
		spi_Transmit(0);
		spi_Transmit(0);
		spi_Transmit(0);
	}
}


