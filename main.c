/*
 * pixelpoi_mega328P.c
 *
 * Created: 26.08.2016 2:06:59
 * Author : Light
 */ 


/*------------------------------
//F_CPU
------------------------------*/

//#define F_CPU 8000000UL



/*------------------------------
	INCLUDE
------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "define.h"
#include "apa102.h"
#include "apa102.h"
#include "onebutton.h"
#include "pixelpoi.h"
#include "macros.h"
#include "init_mega328.h"
#include "uart.h"
#include "nrf24.h"
#include "nRF24L01.h"



/*------------------------------
	GLOBAL VARIABLES
------------------------------*/


#define TICK	0
#define SHOWIMG	1
#define BUF_SIZE 96
#define DTLOOP 5	//дополнительный делитель для таймера

static volatile uint8_t status=0;
static uint8_t buff_RX[BUF_SIZE] _U_, IN_RX _U_, OUT_RX _U_;//тут у нас буфер в который складываем принимаемые данные до 256 байт
static uint8_t buff_TX[BUF_SIZE] _U_, IN_TX _U_, OUT_TX _U_;//А сюда кладем данные для отправки до 256 байт
static uint8_t tenmscout=DTLOOP;		//дополнительный делитель для таймера

/*------------------------------
	INTERRUPT
------------------------------*/

// переполнение таймера 0
ISR(TIMER0_COMPA_vect)
{	
	if(--tenmscout==0)
	{
		SetBit(status,TICK);
		tenmscout=DTLOOP;

			//if (!GET(PIND,2u))
			//{
				//SET(PORTB,5u);
			//}
			//else
			//{
				//CLR(PORTB,5u);
			//}
			
	}
}

/*------------------------------
	MAIN
------------------------------*/





int main(void)
{
	
	
	
	init();
		
		
	
	//настройка таймеров
	//TCCR0A=00<<COM0A0|00<<COM0B0|2<<WGM00;	//порт отключен, режим сброса при совподении с OCR0A
	//TCCR0B=00<<FOC0B|0<<WGM02|0b100<<CS00;	//,,делитель 256
	//TCNT1=0x00;								//здесь увеличиваются тики
	//OCR0A=(125-1);
	
	//включаем прерывания
	//TIMSK0|=0<<TOIE0|1<<OCIE0A;		//on interrupt overflow timer
	sei();							//on global interrupt
	
	send_Uart_str("Hello_World\r");
	
	_delay_ms(100);
	
	
	
	send_Uart_str("nrf24_init\t");
	send_Uart(nrf24_init());
	send_Uart_str("\r");
	_delay_ms(2);
	
	send_Uart_str("CONFIG\t\t");
	uint8_t conf = nrf24_GetReg(CONFIG);
	send_Uart_SHbit(conf);
	send_Uart_str("\r");
	
	send_Uart_str("PRIM_RX = 0");
	nrf24_SetReg(CONFIG, conf & ~(1 << PRIM_RX));
	send_Uart_str("\r");
	
	send_Uart_str("CONFIG\t\t");
	send_Uart_SHbit(nrf24_GetReg(CONFIG));
	send_Uart_str("\r");
	
	send_Uart_str("FIFO_STATUS\t");
	send_Uart_SHbit(nrf24_GetReg(FIFO_STATUS));
	send_Uart_str("\r");
	
	send_Uart_str("TX_EMPTY\t");
	if (!(nrf24_GetReg(FIFO_STATUS) & (1 << TX_EMPTY)))
	send_Uart_str("1");
	else
	send_Uart_str("0");
	send_Uart_str("\r");
	send_Uart_str("\r");
	
	
	
	
	send_Uart_str("W_TX_PAYLOAD = pac\t\t");
	send_Uart_str("\r");
	send_Uart_str("TX_EMPTY\t");
	uint8_t pac = 0xAC;
	nrf24_SetRegBuf(W_TX_PAYLOAD, &pac, 1);
	if (!(nrf24_GetReg(FIFO_STATUS) & (1 << TX_EMPTY)))
		send_Uart_str("1");
	else
		send_Uart_str("0");
	send_Uart_str("\r");
		send_Uart_str("\r");
	
	
	send_Uart_str("nrf24_is_interrupt_return\t");
	send_Uart_SHbit(nrf24_is_interrupt());
	send_Uart_str("\r");
	
	
	
	send_Uart_str("IRQ\t");
	if (!(PIN_nrf_IEQ) & (1 << IRQ))
	send_Uart_str("1");
	else
	send_Uart_str("0");
	send_Uart_str("\r");
	
	
	send_Uart_str("IRQ\t\t");
	if (nrf24_is_interrupt()!=0)
	send_Uart_str("on");
	else 
	send_Uart_str("off");
	send_Uart_str("\r");
		
	
	send_Uart_str("Send pac in space");
	send_Uart_str("\r");
	
	ce_Low();
	nrf24_SetReg(CONFIG,(1<<PWR_UP)|(1<<EN_CRC)|(0<<PRIM_RX));
	ce_High();
	_delay_us(15);
	ce_Low();
	_delay_us(135);


	send_Uart_str("TX_EMPTY\t\t");
	if (!(nrf24_GetReg(FIFO_STATUS) & (1 << TX_EMPTY)))
	send_Uart_str("1");
	else
	send_Uart_str("0");
	send_Uart_str("\r");
	send_Uart_str("\r");

	
	send_Uart_str("IRQ\t\t");
	if (nrf24_is_interrupt()!=0)
		send_Uart_str("on");
	else
		send_Uart_str("off");
	send_Uart_str("\r");
	
	
	
	send_Uart_str("PIN_nrf_IEQ\t");
	send_Uart_SHbit(PIN_nrf_IEQ);
	send_Uart_str("\r");
	//ce_High();
	
	
	
	//imageInit();

    /* Replace with your application code */
	while (1) 
	{
	//uint8_t test = 0xAF;
	//
	//send_Uart_str("send_data\t\t");	
	//send_Uart(nrf24_send_data(&test, 1));
		//
	//send_Uart_str("\r");
	//
	//_delay_ms(500);
		//
	//send_Uart_str("check_radio\t\t");		
	//send_Uart(nrf24_check_radio());
	//send_Uart_str("\r");	
		
		//if(GET(status,SHOWIMG))
		//{
			//imageLoop();
		//}
		//else
		//{
			//clearPixes();
		//}
		//if (GET(status,TICK))
		//{
			//switch(button_scan())
			//{
				//case BSC_ShorClik:
				//XOR(status, SHOWIMG);
				//break;
				//
				//case BSC_LongClik:
				//nextImage();
				//break;
				//
				//case BSC_DoubClik:
				//
				//break;
				//
				//case BSC_TripClik:
				//
				//break;
				//
			//}
			//
			//CLR(status, TICK);
		//}
		
		
	}
    
}

