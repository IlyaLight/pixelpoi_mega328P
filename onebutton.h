/*
 * onebutton.h
 *
 * Created: 01.09.2016 22:04:39
 *  Author: Light
 */ 

#include <avr/io.h>


#ifndef ONEBUTTON_H_
#define ONEBUTTON_H_

//	настройки портов
#define BTN_PORT			PORTD			/*порт чтени€ кнопок*/
#define BTN_DDR				DDRD
#define BTN_PIN				PIND
#define BTN_ONE				2u				/*пины чтени€ кнопок*/

//	настройки циклов
#define release_timeout		25		// ћаксимум 127 при использовании типа s08 дл€ bt_time
#define long_press			50		// если держим кнопень нажатой столько циклов или больше - это длинное нажатие
#define command_max_len		3		// максимальнок количество быстрых нажатий
#define shot_pres			2		// кличество циклов после которых будет зафикслирован ShorClik, програмный фильтр помех на порту
 
// регистор статуса кнопки
static volatile uint8_t bt_result=0;		// ѕеременна€ результат. Ѕит-карта нажатий
#define BSC_NotPressed		0b000	// исходное состо€ние
#define BSC_ShorClik		0b001	// короткое нажатие
#define BSC_DoubClik		0b010	// двойное нажтие
#define BSC_TripClik		0b110	// торойное нажатие
#define BSC_LongClik		0b111	// длинное нажатие

void button_scan(void);					// цыкал опроса кнопки
void button_init(void);
uint8_t get_bt_status(void);

#endif /* BUTTON_H_ */