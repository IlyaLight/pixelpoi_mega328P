/*------------------------------
	pixelpoi.h 16.09.2016
	based on "Adafruit Dot Star" 
	fo 18 pixel 
------------------------------*/

// форматы картинки
// rgm - стандартный 3 байта на пиксель
// mono - по биту на пиксель и три байта на цвет картинки

uint32_t	lastImageTime = 0L; // время споследнего изменения изображения
uint8_t		imageNumber   = 0,  // Current image being displayed
        	*imagePalette,      // -> palette data in PROGMEM
        	*imagePixels,       // -> pixel data in PROGMEM
        	imageLines,         // Number of lines in active image
         	imageLine;          // Current line number in image

void	
	void imageLoop(),		// развретка картинки
	void imageInit(),		//
	void nextImage(),

	
