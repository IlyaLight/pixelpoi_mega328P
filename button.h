/*
 * button.h
 *
 * Created: 01.09.2016 22:04:39
 *  Author: Light
 */ 




#ifndef BUTTON_H_
#define BUTTON_H_

#define release_timeout		25		// �������� 127 ��� ������������� ���� s08 ��� bt_time
#define long_press			50		// ���� ������ ������� ������� ������� ������ ��� ������ - ��� ������� �������
#define command_max_len		3		// ������������ ���������� ������� �������
#define shot_pres			2		// ��������� ������ ����� ������� ����� ������������� ShorClik, ���������� ������ ����� �� �����
 
#define Released	(BTN_PIN & 1<<BTN)
#define Pressed		(!Released)

uint8_t bt_status;					//�������� �������� � ���� ������ �������� ������

#define BSC_NotPressed  = 0b000		//�������� ���������
#define BSC_ShorClik	= 0b001		//�������� �������
#define BSC_DoubClik	= 0b010		//������� ������
#define BSC_TripClik	= 0b011		//������� �������
#define BSC_LongClik	= 0b111		//������� �������

void button_scan(void);

#endif /* BUTTON_H_ */