/*------------------------------
	pixelpoi.h 16.09.2016
	based on "Adafruit Dot Star" 
	fo 18 pixel 
------------------------------*/

#include "define.h"

// форматы картинки
// rgm - стандартный 3 байта на пиксель
// mono - по биту на пиксель и три байта на цвет картинки


	//uint32_t
	//lastImageTime = 0;			// Time of last image change


void	
	imageLoop(void),		// развретка картинки
	imageInit(void),		//
	setImage(uint8_t),
	nextImage(void);

	
