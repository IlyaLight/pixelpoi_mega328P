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
#include <util/delay.h>


void csn_High();
void csn_Low();
void ce_High();
void ce_Low();
//uint8_t  nrf24_is_interrupt();


uint8_t nrf24_SetReg(uint8_t, uint8_t);
uint8_t spi_transfer(uint8_t);
uint8_t nrf24_GetReg(uint8_t);
uint8_t nrf24_SetRegBuf(uint8_t, uint8_t*, uint8_t);
uint8_t nrf24_SetRegBuf(uint8_t, uint8_t*, uint8_t);

uint8_t nrf24_is_interrupt();

uint8_t static self_addr[] = SELF_ADDR;
uint8_t static remote_addr[] = REMOTE_ADDR;


/* configure the module */
uint8_t  nrf24_init()
{	
	ce_Low();
	
	for(uint8_t cnt = 100;;) 
	{
		nrf24_SetReg(CONFIG, (CONFIGSET & (~(1<<PWR_UP)))); // Выключение питания
		if (nrf24_GetReg(CONFIG) == (CONFIGSET& (~(1<<PWR_UP))))
		break;
		// Если прочитано не то что записано, то значит либо радио-чип ещё инициализируется, либо не работает.
		if (!cnt--)
			return 0x31; // Если после 100 попыток не удалось записать что нужно, то выходим с ошибкой
		_delay_ms(1);
	}
	// включение автоподтверждения
	nrf24_SetReg(EN_AA, (0 << ENAA_P5)|(0 << ENAA_P4)|(0 << ENAA_P3)|(0 << ENAA_P2)|(1 << ENAA_P1)|(0 << ENAA_P0));
		 
	// включение каналов
	nrf24_SetReg(EN_RXADDR, (0 << ERX_P5)|(0 << ERX_P4)|(0 << ERX_P3)|(0 << ERX_P2)|(1 << ERX_P1)|(1 << ERX_P0));
	 		  
	// выбор длины адреса
	nrf24_SetReg(SETUP_AW, 3 << AW);
	 
	// установка времени ожидания подтверждения и количество автоматических повторов отправки
	 nrf24_SetReg(SETUP_RETR, (0 << ADR)|(2 << ARC));
	 
	// Выбор частотного канала
	nrf24_SetReg(RF_CH, CHANAL);	

	// Выбор настроек радиоканала: скорости, мощности, пораметры для тестирования РК
	nrf24_SetReg(RF_SETUP,(0<<CONT_WAVE)|(0<<RF_DR_LOW)|(0<<PLL_LOCK)|(0<<RF_DR)|(3<<RF_PWR)); 
	


	  
	// Выбор адреса канала 0 приёмника, подтверждения приходят на канал 0
	nrf24_SetRegBuf(RX_ADDR_P0, &remote_addr[0], ADDR_LEN); // Подтверждения приходят на канал 0
	
	// Выбор адреса канала 1 приёмника
	nrf24_SetRegBuf(RX_ADDR_P1, &self_addr[0], ADDR_LEN);
	
	// Выбор адреса канала 2 приёмника
	//nrf24_SetRegBuf(RX_ADDR_P1, &self_addr[0], ADDR_LEN);
	
	// Выбор адреса канала 3 приёмника
	//nrf24_SetRegBuf(RX_ADDR_P1, &self_addr[0], ADDR_LEN);
	
	// Выбор адреса канала 4 приёмника
	//nrf24_SetRegBuf(RX_ADDR_P1, &self_addr[0], ADDR_LEN);
	
	// Выбор адреса канала 5 приёмника
	//nrf24_SetRegBuf(RX_ADDR_P1, &self_addr[0], ADDR_LEN);
	
	// Установка адреса удалённого устройства
	nrf24_SetRegBuf(TX_ADDR, &self_addr[0], ADDR_LEN);
	
	// Установка размера данных, принимаемых по каналам, соответственно 0-5  
	nrf24_SetReg(RX_PW_P0, 0);
	nrf24_SetReg(RX_PW_P1, 32);
	nrf24_SetReg(RX_PW_P2, 0);	
	nrf24_SetReg(RX_PW_P3, 0);	
	nrf24_SetReg(RX_PW_P4, 0);	
	nrf24_SetReg(RX_PW_P5, 0);
	
	// Включение произвольной длины для каналов
	nrf24_SetReg(DYNPD, (0 << DPL_P5)|(0 << DPL_P4)|(0 << DPL_P3)|(0 << DPL_P2) | (1 << DPL_P1) | (1 << DPL_P0));
	
	// разрешение произвольной длины пакета данных
	nrf24_SetReg(FEATURE, (1 << EN_DPL)|(0 << EN_ACK_PAY)|(0 << EN_DYN_ACK)); 
	
	nrf24_SetReg(CONFIG, CONFIGSET|(1 << PWR_UP )); // Включение питания
	return (nrf24_GetReg(CONFIG) == (CONFIGSET|(1 << PWR_UP ))) ? 0x30 : 0x32;
}
	

// Выполняет команду command
void nrf24_command(uint8_t command)
{
	csn_Low();
	spi_transfer(command);
	csn_High();
}

//Читает значение однобайтового регистра и возвращает его
uint8_t nrf24_GetReg(uint8_t reg)
{
    csn_Low();//Прижимаем вывод CSN(SS) МК к земле, тем самым сообщаем о начале обмена данных.
    SPDR=reg;
    while(!GET(SPSR,SPIF));//ожидаем когда освободится SPI для последующей записи байта
    
	if (reg!=STATUS)
	{
		SPDR=NOP;
		while(!GET(SPSR,SPIF));
	}
	csn_High();//Вывод CSN(SS) МК к питанию, обмен данных завершен.
	return SPDR;
}

//Зписывает значение в однобайтовый регистр
uint8_t nrf24_SetReg(uint8_t reg, uint8_t data)
{
	csn_Low();
	spi_transfer(reg | W_REGISTER);//накладываем маску
	uint8_t status = spi_transfer(data);
	csn_High();
	return status;
}

// Выполняет команду command, и передаёт count байт параметров из буфера buf, возвращает регистр статуса
uint8_t nrf24_SetRegBuf(uint8_t command, uint8_t * buf, uint8_t count) 
{
	csn_Low();
	uint8_t status = spi_transfer(command);
	while (count--) {
		spi_transfer(*(buf++));
	}
	csn_High();
	return status;
}

//Выполняет команду command, и читает count байт ответа, помещая их в буфер buf, возвращает регистр статуса
uint8_t nrf24_GetRegBuf(uint8_t command, uint8_t * buf, uint8_t count) 
{
	csn_Low();
	uint8_t status = spi_transfer(command);
	while (count--) 
	{
		*(buf++) =  spi_transfer(NOP);
	}
	csn_High();
	return status;
}

void nrf24_clrStatus()
{
	uint8_t status= nrf24_GetReg(STATUS);//прочитали статус регистр
	nrf24_SetReg(STATUS, status);//сброс флагов прерываний
}


// Возвращает размер данных в начале FIFO очереди приёмника
uint8_t nrf24_read_rx_payload_width() 
{
	csn_High();
	spi_transfer(R_RX_PL_WID);
	uint8_t answ = spi_transfer(0xFF);
	csn_Low();
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
	if (GET(status,TX_FULL_STATUS));  // Если очередь передатчика заполнена, возвращаемся с ошибкой
		return 0x32;
	nrf24_SetRegBuf(W_TX_PAYLOAD, buf, size); // Запись данных на отправку
	ce_High(); // Импульс на линии CE приведёт к началу передачи
	_delay_us(15); // Нужно минимум 10мкс, возьмём с запасом
	ce_Low();
	return 0x30;
}


uint8_t nrf24_check_radio() 
{
	if (!nrf24_is_interrupt()) // Если прерывания нет, то не задерживаемся
	return 0;
	uint8_t status = nrf24_GetReg(STATUS);
	nrf24_SetReg(STATUS, status); // Просто запишем регистр обратно, тем самым сбросив биты прерываний
	
	if (status & ((1 << TX_DS) | (1 << MAX_RT))) // Завершена передача успехом, или нет,
	{ 
		if (status & (1 << MAX_RT)) // Если достигнуто максимальное число попыток
		{ 
			nrf24_command(FLUSH_TX); // Удалим последний пакет из очереди
			return 1;
		}
		if (!(nrf24_GetReg(FIFO_STATUS) & (1 << TX_EMPTY))) // Если в очереди передатчика есть что передавать
		{ 
			ce_High(); // Импульс на линии CE приведёт к началу передачи
			_delay_us(15); // Нужно минимум 10мкс, возьмём с запасом
			ce_Low();
		} 
		else 
		{
			uint8_t conf = nrf24_GetReg(CONFIG);
			nrf24_SetReg(CONFIG, conf | (1 << PRIM_RX)); // Устанавливаем бит PRIM_RX: приём
			ce_High(); // Высокий уровень на линии CE переводит радио-чип в режим приёма
		}
	}
	uint8_t protect = 4; // В очереди FIFO не должно быть более 3 пакетов. Если больше, значит что-то не так
	while (((status & (7 << RX_P_NO)) != (7 << RX_P_NO)) && protect--) // Пока в очереди есть принятый пакет
	{ 
		uint8_t l = nrf24_read_rx_payload_width(); // Узнаём длину пакета
		if (l > 32)  // Ошибка. Такой пакет нужно сбросить
		{
			nrf24_command(FLUSH_RX);
			return 2;
		} 
		else 
		{
			uint8_t buf[32]; // буфер для принятого пакета
			nrf24_GetRegBuf(R_RX_PAYLOAD, &buf[0], l); // начитывается пакет
			if ((status & (7 << RX_P_NO)) == (1 << RX_P_NO)) // если datapipe 1
			{ 
				return 0; // вызываем обработчик полученного пакета
			}
		}
		status = nrf24_GetReg(STATUS);
	}
	return 3;
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
	//return !((PIN_nrf_IEQ) & (1 << IRQ));
}


uint8_t spi_transfer(uint8_t data)
{
	SPDR = data;
	while(!GET(SPSR,SPIF));
	return SPDR;
}

