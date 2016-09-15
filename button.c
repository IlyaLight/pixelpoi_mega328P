/*
 * button.c
 *
 * Created: 01.09.2016 22:04:51
 *  Author: Light
 */ 

// ��� ������� ������. ��� ������ ���������� ��� � 20��
void button_scan(void) 
{	
	static int8_t	p_time=0;			// ���������� ������� ������ �������� - ��������(!)
	static uint8_t	bt_result=0;		// ���������� ���������. ���-����� �������.
	static uint8_t	bt_cnt=0;			// ���������� ������� �������
	
	
	
	if (Pressed)						// ������� ����������. ���� ������� ����� ��������.
	{ 
		if bt_result==BSC_LongClik return; // �������� �� ���������� ������������ LongClik
		if (p_time<0x7F) p_time++;
		if (p_time>=long_press)			// LongClik
		{
			bt_result=BSC_LongClik;	//		
		}
	}
	
	else if (p_time>=shot_pres)			//  ������ ���������� ������.
	{ 
		if (bt_result==BSC_LongClik)	// ���� ������ ���� �������� ����� long clik
		{
			p_time=0:
			bt_result=0;
			return;
		}
		
		bt_cnt++;						// ��������� ������� ����� � ����������
		if (bt_cnt==command_max_len)	// ���� ��������� ���� �������� ������ ������ ���������
		{
			bt_result=bt_cnt;			
			bt_cnt=0
		}								
		p_time=0;
	} 
	
	else if (bt_cnt>0 && p_time>-release_timeout)	// ������ ��������� �������				
	{
		p_time--;							
	} 

	else if (bt_cnt>0)							// ������� ��������, ����� ���������
	{ 
		bt_result=bt_cnt;   
		bt_cnt=0;
	}
}