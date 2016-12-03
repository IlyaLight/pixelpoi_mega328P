/*
 * onebutton.c
 *
 * Created: 01.09.2016 22:04:51
 *  Author: Light
 */ 


#include "onebutton.h"
#include <avr/io.h>
#include "macros.h"


uint8_t max_len=1;		// max clicks


// scan every 20ms
uint8_t button_scan(void) 
{	
	static  int8_t	p_time=0;			// signed(!) variable time
	static  uint8_t	bt_cnt=0;			// clicks counter
	
	
	
	if (!GET(BTN_PIN,BTN_ONE))			// button is pressed, calculate the time
	{ 
		if (p_time==LONG_PRESS) return 0;	// LongClik already was
		if (p_time<0) p_time=0;
		p_time++;
		if (bt_cnt>0) return 0;			// ate it re-click
		if (p_time==LONG_PRESS)			// LongClik
		{
			return BSC_LongClik;		
		}
	}
	
	else if (p_time>=SHOT_PRESS)			//  button up
	{ 
		if (p_time==LONG_PRESS)			// after long_press
		{
			p_time=0;
			return 0;
		}
		bt_cnt++;						// quantity clicks
		p_time=0;
		if (bt_cnt==max_len)	// max clicks
		{
			uint8_t t=bt_cnt;
			bt_cnt=0;
			return t;
		}								
	} 
	
	else if (bt_cnt>0 && p_time>-RELEASE_TIMEOUT)	// Timer repeat click				
	{
		p_time--;							
	} 

	else if (bt_cnt>0)					//timeout, reset state
	{ 
		uint8_t t=bt_cnt;   
		bt_cnt=0;
		return t;
	}
	return 0;	
}

// set max quantity clicks
void set_max_len(uint8_t l)
{
	max_len=l;
}
