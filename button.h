/*
 * button.h
 *
 * Created: 01.09.2016 22:04:39
 *  Author: Light
 */ 




#ifndef BUTTON_H_
#define BUTTON_H_

#define release_timeout		25		// Максимум 127 при использовании типа s08 для bt_time
#define long_press			50		// если держим кнопень нажатой столько циклов или больше - это длинное нажатие
#define command_max_len		3		// максимальнок количество быстрых нажатий
#define shot_pres			2		// кличество циклов после которых будет зафикслирован ShorClik, програмный фильтр помех на порту
 
#define Released	(BTN_PIN & 1<<BTN)
#define Pressed		(!Released)

uint8_t bt_status;					//регистор содержит в себе флагио состояня кнопки

#define BSC_NotPressed  = 0b000		//исходное состояние
#define BSC_ShorClik	= 0b001		//короткое нажатие
#define BSC_DoubClik	= 0b010		//двойное нажтие
#define BSC_TripClik	= 0b011		//длинное нажатие
#define BSC_LongClik	= 0b111		//длинное нажатие

void button_scan(void);

#endif /* BUTTON_H_ */