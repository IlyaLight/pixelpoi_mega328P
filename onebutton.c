/*
 * onebutton.c
 *
 * Created: 01.09.2016 22:04:51
 *  Author: Light
 */ 


#include "onebutton.h"
#include <avr/io.h>
#include "macros.h"



void button_init(void)
{
	BTN_DDR &= ~(1<<BTN_ONE);			//�� ����
	BTN_PORT |= (1<<BTN_ONE);			//�������� ���
}


// ��� ������� ������. ��� ������ ���������� ��� � 20��
void button_scan(void) 
{	
	static int8_t	p_time=0;			// ���������� ������� ������ �������� - ��������(!)
	static uint8_t	bt_cnt=0;			// ���������� ������� �������
	
	
	if (!GET(BTN_PIN,BTN_ONE))			// ������� ����������. ���� ������� ����� ��������.
	{ 
		if (p_time==long_press) return;	//LongClik ��� ���������
		p_time++;
		if (p_time==long_press)			// LongClik
		{
			bt_result=BSC_LongClik;		
		}
	}
	
	else if (p_time>=shot_pres)			//  ������ ���������� ������.
	{ 
		if (p_time==long_press)	// ���� ������ ���� �������� ����� long clik
		{
			p_time=0;
			return;
		}
		
		bt_cnt++;						// ��������� ������� ����� � ����������
		if (bt_cnt==command_max_len)	// ���� ��������� ���� �������� ������ ������ ���������
		{
			bt_result=bt_cnt;			
			bt_cnt=0;
		}								
		p_time=0;
	} 
	
	else if (bt_cnt>0 && p_time>-release_timeout)	// ������ ��������� �������				
	{
		p_time--;							
	} 

	else if (bt_cnt>0)					// ������� ��������, ����� ���������
	{ 
		bt_result=bt_cnt;   
		bt_cnt=0;
	}
}

uint8_t get_bt_status(void)
{
	return bt_result;
	bt_result=0;
}