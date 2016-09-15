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


// форматы картинки
// rgm - стандартный 3 байта на пиксель
// mono - по биту на пиксель и три байта на цвет картинки

uint32_t	lastImageTime = 0L; // время споследнего изменения изображения
uint8_t		imageNumber   = 0,  // Current image being displayed
        	*imagePalette,      // -> palette data in PROGMEM
        	*imagePixels,       // -> pixel data in PROGMEM
        	imageLines,         // Number of lines in active image
         	imageLine;          // Current line number in image



#define COUNT_BYT 3		//количество байт на для хронения 1 столбца монохро картинки

void nextImage(void) {
  if(++imageNumber >= NUM_IMAGES) imageNumber = 0;
  imageInit();
}

void imageInit()
{
	imageLine = 0;

}

void imageLoop()
{
	switch(imageType) 
	{
		case PALETTE1:			// 1-bit (2 color) palette-based image
		{
			uint8_t pixelNum = 0,	//
					byteNum,		// количество байт содержащех матрицу для одной строки монохронной картинки
					bitNum,
					pixels,			// 
					idx,
					*ptr = (uint8_t *)&imagePixels[imageLine * COUNT_BYT]; //ссылка на картинку

			for(byteNum = COUNT_BYT; byteNum--; ) // перебераем байты с матрицей
			{
				pixels = pgm_read_byte(ptr++);  // 8 pixels of data (pixel 0 = LSB)
			
				for(bitNum = 8; bitNum--; pixels >>= 1) //пенребераем биты
				{
					idx = pixels & 1; // Color table index for pixel (0 or 1) обнуляем все биты кроме 0го
          			strip.setPixelColor(pixelNum++,
            		palette[idx][0], palette[idx][1], palette[idx][2]);
				}
			}
		}
		break;
	}

	case PALETTE4:					// 4-bit (16 color) palette-based image
	{ 
      uint8_t  	pixelNum, 
      			p1, 
      			p2,
              	*ptr = (uint8_t *)&imagePixels[imageLine * NUM_LEDS / 2];

      for(pixelNum = 0; pixelNum < NUM_LEDS; ) 
      {
        p2  = pgm_read_byte(ptr++); // Data for two pixels...
        p1  = p2 >> 4;              // Shift down 4 bits for first pixel
        p2 &= 0x0F;                 // Mask out low 4 bits for second pixel
        strip.setPixelColor(pixelNum++,
          palette[p1][0], palette[p1][1], palette[p1][2]);
        strip.setPixelColor(pixelNum++,
          palette[p2][0], palette[p2][1], palette[p2][2]);
      }
      break;
    }
}



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

