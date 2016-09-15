/*
 * button.c
 *
 * Created: 01.09.2016 22:04:51
 *  Author: Light
 */ 

// Эта функция сканер. Она должна вызываться раз в 20мс
void button_scan(void) 
{	
	static int8_t	p_time=0;			// Переменная времени работы автомата - знаковая(!)
	static uint8_t	bt_result=0;		// Переменная результат. Бит-карта нажатий.
	static uint8_t	bt_cnt=0;			// Переменная счетчик нажатий
	
	
	
	if (Pressed)						// Кнопень придавлена. Тупо считаем время придавки.
	{ 
		if bt_result==BSC_LongClik return; // заглушка от повторного сробатывания LongClik
		if (p_time<0x7F) p_time++;
		if (p_time>=long_press)			// LongClik
		{
			bt_result=BSC_LongClik;	//		
		}
	}
	
	else if (p_time>=shot_pres)			//  Момент отпускания кнопки.
	{ 
		if (bt_result==BSC_LongClik)	// если кнопка было отпущена после long clik
		{
			p_time=0:
			bt_result=0;
			return;
		}
		
		bt_cnt++;						// фиксируем коротки клики и количество
		if (bt_cnt==command_max_len)	// если достигнут макс количтво кликов выдаем результат
		{
			bt_result=bt_cnt;			
			bt_cnt=0
		}								
		p_time=0;
	} 
	
	else if (bt_cnt>0 && p_time>-release_timeout)	// таймер повторных нажатий				
	{
		p_time--;							
	} 

	else if (bt_cnt>0)							// Таймаут комманды, сброс состояний
	{ 
		bt_result=bt_cnt;   
		bt_cnt=0;
	}
}