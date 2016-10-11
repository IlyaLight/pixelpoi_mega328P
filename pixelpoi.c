/*------------------------------
	pixelpoi.c 16.09.2016
	based on "Adafruit Dot Star" 
	fo 18 pixel 
------------------------------*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "graphics.h"
#include "pixelpoi.h"
#include "apa102.h"

#define COUNT_BYT 2		//количество байт на для хронения 1 столбца монохромной картинки

// GLOBAL STATE STUFF ------------------------------------------------------





void imageInit(void)
{
	imageType    = pgm_read_byte(&images[imageNumber].type);
	imageLines   = pgm_read_word(&images[imageNumber].lines);
	imageLine = 0;
	imagePalette = (uint8_t *)pgm_read_word(&images[imageNumber].palette);
  	imagePixels  = (uint8_t *)pgm_read_word(&images[imageNumber].pixels);
  	if(imageType == PALETTE1)      memcpy_P(palette, imagePalette,  2 * 3);   
  	else if(imageType == PALETTE4) memcpy_P(palette, imagePalette, 16 * 3);
  	//lastImageTime = millis(); // Save time of image init for next auto-cycle
}

void nextImage(void) 
{
  	if(++imageNumber >= NUM_IMAGES) imageNumber = 0;
  	imageInit();
}

// развретка картинки
void imageLoop(void)
{
	switch(imageType) 
	{
		case PALETTE1:			// 1-bit (2 color) palette-based image
		{
			uint8_t 
				//pixelNum = 0,	//
				byteNum,		// количество байт содержащех матрицу для одной строки монохронной картинки
				bitNum,
				pixels,			// 
				idx,
				*ptr = (uint8_t *)&imagePixels[imageLine * COUNT_BYT]; //ссылка на строку картинки
				
				
			startFrame();		//готовимся для отправки стрчки кортики
			for(byteNum = COUNT_BYT; byteNum--; )		// перебераем байты страки картинки
			{
				pixels = pgm_read_byte(ptr++);			// 8 pixels of data (pixel 0 = LSB)
				for(bitNum = 8; bitNum--; pixels >>= 1) //пенребераем биты сдвигая их
				{
					idx = pixels & 1;					// Color table index for pixel (0 or 1) обнуляем все биты кроме 0го
          			setPixelColorRGB(palette[idx][0], palette[idx][1], palette[idx][2]);
				}
			}
		}
		break;

		//case PALETTE4:					// 4-bit (16 color) palette-based image
		//{ 
		  //uint8_t  	pixelNum, 
      				//p1, 
      				//p2,
              		//*ptr = (uint8_t *)&imagePixels[imageLine * NUM_LEDS / 2];
//
		  //for(pixelNum = 0; pixelNum < NUM_LEDS; ) 
		  //{
			//p2  = pgm_read_byte(ptr++); // Data for two pixels...
			//p1  = p2 >> 4;              // Shift down 4 bits for first pixel
			//p2 &= 0x0F;                 // Mask out low 4 bits for second pixel
			//strip.setPixelColorRGB(pixelNum++,
			  //palette[p1][0], palette[p1][1], palette[p1][2]);
			//strip.setPixelColor(pixelNum++,
			  //palette[p2][0], palette[p2][1], palette[p2][2]);
		  //}
		  //break;
		//}
	}
	if(++imageLine >= imageLines) imageLine = 0; // Next scanline, wrap around
}