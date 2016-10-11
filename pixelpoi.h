/*------------------------------
	pixelpoi.h 16.09.2016
	based on "Adafruit Dot Star" 
	fo 18 pixel 
------------------------------*/

// форматы картинки
// rgm - стандартный 3 байта на пиксель
// mono - по биту на пиксель и три байта на цвет картинки

static uint8_t
	imageNumber = 0,			// Current image being displayed
	imageType,					// Image type: PALETTE[1,4,8] or TRUECOLOR
	*imagePalette,				// -> palette data in PROGMEM
	*imagePixels,				// -> pixel data in PROGMEM
	palette[16][3];				// RAM-based color table for 1- or 4-bit images
static uint16_t
	imageLines,					// Number of lines in active image
	imageLine;					// Current line number in image
	//uint32_t
	//lastImageTime = 0;			// Time of last image change


void	
	imageLoop(void),		// развретка картинки
	imageInit(void),		//
	nextImage(void);

	
