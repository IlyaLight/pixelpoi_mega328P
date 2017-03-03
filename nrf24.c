/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* This library is based on this library: 
*   https://github.com/aaronds/arduino-nrf24l01
* Which is based on this library: 
*   http://www.tinkerer.eu/AVRLib/nRF24L01
* -----------------------------------------------------------------------------
*/
#include <avr/io.h>
#include "nrf24.h"
#include "nRF24L01.h"
#include "macros.h"
#include "uart.h"
#include "define.h"
#include <util/delay.h>


void csn_High();
void csn_Low();
void ce_High();
void ce_Low();
uint8_t nrf24_is_interrupt();
uint8_t spi_transfer(uint8_t);

uint8_t nrf24_SetReg(uint8_t, uint8_t);
uint8_t nrf24_SetCmd(uint8_t);
uint8_t nrf24_GetReg(uint8_t);
uint8_t nrf24_SetRegBuf(uint8_t, uint8_t*, uint8_t);
uint8_t nrf24_GetRegBuf(uint8_t, uint8_t*, uint8_t);


/* configure the module */
/*функция инициализации всех регистров модуля*/
uint8_t  nrf24_init()
{
	_delay_ms(100);			//задержка на случай если толькочто подали питание и ему нужно время что бы завестись
	ce_Low();
	for(uint8_t cnt = 100;;)
	{
		nrf24_SetReg(SET_CONFIG, (SET_CONFIG & (~(1<<PWR_UP)))); // Выключение питания
		if (nrf24_GetReg(SET_CONFIG) == (SET_CONFIG& (~(1<<PWR_UP))))
		break;
		if (!cnt--)		// Если прочитано не то что записано, то значит либо радио-чип ещё инициализируется, либо не работает.
		return 1;
	}

	#ifdef SET_EN_AA
	// включение автоподтверждения
	nrf24_SetReg(EN_AA, SET_EN_AA);
	#endif
	#ifdef 	SET_EN_RXADDR
	// включение каналов
	nrf24_SetReg(EN_RXADDR, SET_EN_RXADDR);
	#endif
	#ifdef	SET_SETUP_AW
	// выбор длины адреса
	nrf24_SetReg(SETUP_AW, SET_SETUP_AW);
	#endif
	#ifdef	SET_SETUP_RETR
	// установка времени ожидания подтверждения и количество автоматических повторов отправки
	nrf24_SetReg(SETUP_RETR, SET_SETUP_RETR);
	#endif
	#ifdef	SET_CHANAL
	// Выбор частотного канала
	nrf24_SetReg(RF_CH, SET_CHANAL);
	#endif
	#ifdef	SET_RF_SETUP
	// Выбор настроек радиоканала: скорости, мощности, пораметры для тестирования РК
	nrf24_SetReg(RF_SETUP,SET_RF_SETUP);
	#endif
	#ifdef	SET_RX_ADDR_P0
	// Выбор адреса канала 0 приёмника, подтверждения приходят на канал 0
	uint8_t rx_addr_p0[] = {SET_RX_ADDR_P0};
	nrf24_SetRegBuf(RX_ADDR_P0, rx_addr_p0, ADDR_LEN); // Подтверждения приходят на канал 0
	#endif
	#ifdef	SET_RX_ADDR_P1
	// Выбор адреса канала 1 приёмника
	uint8_t rx_addr_p1[] = {SET_RX_ADDR_P1};
	nrf24_SetRegBuf(RX_ADDR_P1, rx_addr_p1, ADDR_LEN);
	#endif
	#ifdef	SET_RX_ADDR_P2
	// Выбор адреса канала 2 приёмника
	uint8_t rx_addr_p2[] = {SET_RX_ADDR_P2};
	nrf24_SetRegBuf(RX_ADDR_P2, rx_addr_p2, ADDR_LEN);
	#endif
	#ifdef	SET_RX_ADDR_P3
	// Выбор адреса канала 3 приёмника
	uint8_t rx_addr_p3[] = {SET_RX_ADDR_P3};
	nrf24_SetRegBuf(RX_ADDR_P3, rx_addr_p3, ADDR_LEN);
	#endif
	#ifdef	SET_RX_ADDR_P4
	// Выбор адреса канала 4 приёмника
	uint8_t rx_addr_p4[] = {SET_RX_ADDR_P4};
	nrf24_SetRegBuf(RX_ADDR_P4, rx_addr_p4, ADDR_LEN);
	#endif
	#ifdef	SET_RX_ADDR_P5
	// Выбор адреса канала 5 приёмника
	uint8_t rx_addr_p5[] = {SET_RX_ADDR_P5};
	nrf24_SetRegBuf(RX_ADDR_P5, rx_addr_p5, ADDR_LEN);
	#endif
	#ifdef	SET_TX_ADDR
	// Установка адреса удалённого устройства
	uint8_t static tx_addr[] = {SET_TX_ADDR};
	nrf24_SetRegBuf(TX_ADDR, tx_addr, ADDR_LEN);
	#endif
	#ifdef	SET_RX_PW_P0
	// Установка размера данных, принимаемых по каналам, соответственно 0-5
	nrf24_SetReg(RX_PW_P0, SET_RX_PW_P0);
	#endif
	#ifdef	SET_RX_PW_P1
	nrf24_SetReg(RX_PW_P1, SET_RX_PW_P1);
	#endif
	#ifdef	SET_RX_PW_P2
	nrf24_SetReg(RX_PW_P2, SET_RX_PW_P2);
	#endif
	#ifdef	SET_RX_PW_P3
	nrf24_SetReg(RX_PW_P3, SET_RX_PW_P3);
	#endif
	#ifdef	SET_RX_PW_P4
	nrf24_SetReg(RX_PW_P4, SET_RX_PW_P4);
	#endif
	#ifdef	SET_RX_PW_P5
	nrf24_SetReg(RX_PW_P5, SET_RX_PW_P5);
	#endif
	#ifdef	SET_DYNPD
	// Включение произвольной длины для каналов
	nrf24_SetReg(DYNPD, SET_DYNPD);
	#endif
	#ifdef	SET_FEATURE
	// разрешение произвольной длины пакета данных
	nrf24_SetReg(FEATURE, SET_FEATURE);
	#endif

	nrf24_SetReg(CONFIG, SET_CONFIG); // Включение питания
	return (nrf24_GetReg(CONFIG) == (SET_CONFIG)) ? 0 : 2;
}
	

// Выполняет команду command
uint8_t nrf24_SetCmd(uint8_t cmd)
{
	return spi_transfer(cmd);
}

//Читает значение однобайтового регистра и возвращает его
uint8_t nrf24_GetReg(uint8_t reg)
{
	csn_Low(); //Прижимаем вывод CSN(SS) МК к земле, тем самым сообщаем о начале обмена данных.
	uint8_t answ = spi_transfer(reg);
	if (reg!=STATUS)
	{
		answ = spi_transfer(NOP);
	}
	csn_High(); //Вывод CSN(SS) МК к питанию, обмен данных завершен.
	return answ;
}

//Зписывает значение в однобайтовый регистр
uint8_t nrf24_SetReg(uint8_t reg, uint8_t data)
{
	csn_Low();
	uint8_t answ = spi_transfer(reg | W_REGISTER);//накладываем маску
	spi_transfer(data);
	csn_High();
	return answ;
}

// Выполняет команду command, и передаёт count байт параметров из буфера buf, возвращает регистр статуса
uint8_t nrf24_SetRegBuf(uint8_t reg, uint8_t *buf, uint8_t count)
{
	csn_Low();
	uint8_t status = spi_transfer(reg | W_REGISTER);
	while (count--)
	{
		spi_transfer(buf[count]);
	}
	csn_High();
	return status;
}

//Выполняет команду command, и читает count байт ответа, помещая их в буфер buf, возвращает регистр статуса
uint8_t nrf24_GetRegBuf(uint8_t reg, uint8_t *buf, uint8_t count)
{
	csn_Low();
	uint8_t status = spi_transfer(reg);
	while (count--)
	{
		buf[count] =  spi_transfer(NOP);
	}
	csn_High();
	return status;
}

void nrf24_clrStatus()
{
	spi_transfer(spi_transfer(NOP));
}

// Возвращает размер данных в начале FIFO очереди приёмника
uint8_t nrf24_rx_payload_width()
{
	csn_Low();
	spi_transfer(R_RX_PL_WID);
	uint8_t answ = spi_transfer(NOP);
	csn_High();
	return answ;
}




// Помещает пакет в очередь отправки.
// buf - буфер с данными, size - длина данных (от 1 до 32)
uint8_t nrf24_send_data(uint8_t * buf, uint8_t size)
{
	ce_Low(); // Если в режиме приёма, то выключаем его
	uint8_t conf = nrf24_GetReg(CONFIG);
	if (!(conf & (1 << PWR_UP))) // Если питание по какой-то причине отключено, возвращаемся с ошибкой
		return 0x31;
	// Сбрасываем бит PRIM_RX
	uint8_t status = nrf24_SetReg(CONFIG, conf & ~(1 << PRIM_RX));
	if (GET(status,TX_FULL));  // Если очередь передатчика заполнена, возвращаемся с ошибкой
		return 0x32;
	nrf24_SetRegBuf(W_TX_PAYLOAD, buf, size); // Запись данных на отправку
	ce_High(); // Импульс на линии CE приведёт к началу передачи
	_delay_us(15); // Нужно минимум 10мкс, возьмём с запасом
	ce_Low();
	return 0x30;
}


void check_radio()
{
	if (!nrf24_is_interrupt()) // Если прерывания нет, то не задерживаемся
	return;
	uint8_t status = nrf24_GetReg(STATUS);
	nrf24_SetReg(STATUS, status); // Просто запишем регистр обратно, тем самым сбросив биты прерываний
	uint8_t protect = 4; // В очереди FIFO не должно быть более 3 пакетов. Если больше, значит что-то не так
	send_Uart_str("get pac\r");
	while (((status & (7 << RX_P_NO)) != (7 << RX_P_NO)) && protect--)
	{ // Пока в очереди есть принятый пакет
		uint8_t leng = nrf24_rx_payload_width(); // Узнаём длину пакета
		send_Uart_str("pac leng\t");
		send_Uart_DEC(leng);
		send_Uart_str("\r");
		if(leng>32)
		{
			nrf24_SetCmd(FLUSH_RX);
		}
		else
		{
			uint8_t buf[32]; // буфер для принятого пакета
			nrf24_GetRegBuf(R_RX_PAYLOAD, buf, leng); // начитывается пакет
			while(leng--)
			{
				send_Uart_BIN(buf[leng]);
				send_Uart_str("\r");
			}
		}
		status = nrf24_GetReg(STATUS);
	}
}



void csn_Low()
{
	ClearBit(PORT_nrf_CSN,CSN);
}

void csn_High()
{
	SetBit(PORT_nrf_CSN,CSN);
}

void ce_Low()
{
	ClearBit(PORT_nrf_CE,CE);
}

void ce_High()
{
	SetBit(PORT_nrf_CE,CE);
}

//возрощает 0 ели прирываний нет
uint8_t nrf24_is_interrupt()
{
	return (~PIN_nrf_IEQ & (1 << IRQ));
}


uint8_t spi_transfer(uint8_t data)
{
	SPDR = data;
	while(!GET(SPSR,SPIF));
	return SPDR;
}


void nrf24_test()
{
	send_Uart_str("Hello_World\r");
	
	_delay_ms(100);
	
	
	
	send_Uart_str("nrf24_init\t");
	send_Uart(nrf24_init());
	send_Uart_str("\r");
	_delay_ms(2);
	
	send_Uart_str("CONFIG\t\t");
	uint8_t conf = nrf24_GetReg(CONFIG);
	send_Uart_BIN(conf);
	send_Uart_str("\r");
	//адреса
	send_Uart_str("RX_ADDR_P1\r");
	uint8_t leng = 5;
	uint8_t buf[leng]; // буфер для принятого пакета
	nrf24_GetRegBuf(RX_ADDR_P1, &buf[0], leng); // начитывается пакет
	while(leng--)
	{
		send_Uart_BIN(buf[leng]);
		send_Uart_str("\r");
	}
	send_Uart_str("TX_ADDR\r");
	leng = 5;
	nrf24_GetRegBuf(TX_ADDR, &buf[0], leng); // начитывается пакет
	while(leng--)
	{
		send_Uart_BIN(buf[leng]);
		send_Uart_str("\r");
	}
	
	send_Uart_str("PRIM_RX = 0");
	nrf24_SetReg(CONFIG, conf & ~(1 << PRIM_RX));
	send_Uart_str("\r");
	
	send_Uart_str("CONFIG\t\t");
	send_Uart_BIN(nrf24_GetReg(CONFIG));
	send_Uart_str("\r");
	
	send_Uart_str("FIFO_STATUS\t");
	send_Uart_BIN(nrf24_GetReg(FIFO_STATUS));
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
	
	
	
	send_Uart_str("IRQ\t");
	if (!(PIN_nrf_IEQ) & (1 << IRQ))
	send_Uart_str("1");
	else
	send_Uart_str("0");
	send_Uart_str("\r");
	
	send_Uart_str("PIN_nrf_IEQ\t");
	send_Uart_BIN(PIN_nrf_IEQ);
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


	send_Uart_str("TX_EMPTY\t");
	if (!(nrf24_GetReg(FIFO_STATUS) & (1 << TX_EMPTY)))
	send_Uart_str("1");
	else
	send_Uart_str("0");
	send_Uart_str("\r");
	send_Uart_str("\r");

	send_Uart_str("PIN_nrf_IEQ\t");
	send_Uart_BIN(PIN_nrf_IEQ);
	send_Uart_str("\r");
	
	send_Uart_str("IRQ\t\t");
	if (nrf24_is_interrupt()!=0)
	send_Uart_str("on");
	else
	send_Uart_str("off");
	send_Uart_str("\r");
	
	send_Uart_str("STATUS\t");
	send_Uart_BIN(nrf24_GetReg(STATUS));
	send_Uart_str("\r");
	

}