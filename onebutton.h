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
#define release_timeout		17		// timeout for re-click, max 127
#define long_press			50		// long press
#define command_max_len		3		// max clicks
#define shot_pres			3		// time ShorClik, software filter
 
// Mask for the return value of button_scan()
#define BSC_NotPressed		0b000	
#define BSC_ShorClik		0b001	
#define BSC_DoubClik		0b010	
#define BSC_TripClik		0b110	
#define BSC_LongClik		0b111	

uint8_t button_scan(void);			// every 20ms
void button_init(void);

#endif /* BUTTON_H_ */