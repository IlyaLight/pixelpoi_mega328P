/*
 * apa102.h
 *
 * Created: 27.08.2016 15:25:48
 *  Author: Light
 */ 
#include <avr/io.h>

#ifndef APA102_H_
#define APA102_H_

#define  numPixels 18									// number pixels

#define DDR_SPI DDRB									//SPI port
#define DD_MISI 3										//MISO leg
#define DD_SCK	5
#define DD_SS	2

# define SPI2 1


uint8_t *pixels[];										// LED RGB values (3 bytes ea.)


void
	spi_Init(void),
	show(void),
	clear(void),										//clear all pixels
	setPixelColor(uint8_t r,uint8_t g,uint8_t b),											
	setPixeslColor(uint8_t *data[]),
	spi_Transmit(uint8_t data), 
    startFreme(void);            


#endif /* APA102_H_ */