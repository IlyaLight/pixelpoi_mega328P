/*
 * onebutton.h
 *
 * Created: 01.09.2016 22:04:39
 *  Author: Light
 * testing on mega328P
 */ 

#include <avr/io.h>


#ifndef ONEBUTTON_H_
#define ONEBUTTON_H_

//	Port
#define BTN_PORT			PORTD			
#define BTN_DDR				DDRD
#define BTN_PIN				PIND
#define BTN_ONE				2u				

//	timing, 1=20ms
#define RELEASE_TIMEOUT		17		// timeout for re-click, max 127
#define LONG_PRESS			50		// long press
#define SHOT_PRESS			3		// time ShorClik, software filter
 
// Mask for the return value of button_scan()
#define BSC_NotPressed		0b000	
#define BSC_ShorClik		0b001	
#define BSC_DoubClik		0b010	
#define BSC_TripClik		0b011	
#define BSC_LongClik		0b111	


uint8_t button_scan(void);			// every 20ms
void button_init(void);				// init button port
void set_max_len(uint8_t);			// set max quantity clicks

#endif /* BUTTON_H_ */