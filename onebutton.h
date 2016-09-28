/*
 * onebutton.h
 *
 * Created: 01.09.2016 22:04:39
 *  Author: Light
 */ 

#include <avr/io.h>


#ifndef ONEBUTTON_H_
#define ONEBUTTON_H_

//	��������� ������
#define BTN_PORT			PORTD			/*���� ������ ������*/
#define BTN_DDR				DDRD
#define BTN_PIN				PIND
#define BTN_ONE				2u				/*���� ������ ������*/

//	��������� ������
#define release_timeout		25		// �������� 127 ��� ������������� ���� s08 ��� bt_time
#define long_press			50		// ���� ������ ������� ������� ������� ������ ��� ������ - ��� ������� �������
#define command_max_len		3		// ������������ ���������� ������� �������
#define shot_pres			2		// ��������� ������ ����� ������� ����� ������������� ShorClik, ���������� ������ ����� �� �����
 
// �������� ������� ������
static volatile uint8_t bt_result=0;		// ���������� ���������. ���-����� �������
#define BSC_NotPressed		0b000	// �������� ���������
#define BSC_ShorClik		0b001	// �������� �������
#define BSC_DoubClik		0b010	// ������� ������
#define BSC_TripClik		0b110	// �������� �������
#define BSC_LongClik		0b111	// ������� �������

void button_scan(void);					// ����� ������ ������
void button_init(void);
uint8_t get_bt_status(void);

#endif /* BUTTON_H_ */