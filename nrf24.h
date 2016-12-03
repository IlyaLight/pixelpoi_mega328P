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
#ifndef NRF24
#define NRF24

#include <avr/io.h>

#define CONFIGSET	((1 << MASK_RX_DR)|(1 << MASK_TX_DS)|(1 << MASK_MAX_RT)|(1 << EN_CRC)|(1 << CRCO)|(0 << PWR_UP )|(1 << PRIM_RX))
#define ADDR_LEN 5				//длинна адреса 
#define SELF_ADDR {0xE7, 0xE7, 0xE7, 0xE7, 0xE7}	// Собственный адрес
#define REMOTE_ADDR {0xC2, 0xC2, 0xC2, 0xC2, 0xC2}	// Адрес удалённой стороны
#define CHANAL 3				//частотa несущей (в диапазоне 0 - 125) с шагом 1Мгц. Радиочастота несущей вычисляется по формуле 2400 + RF_CH МГц. 




uint8_t	nrf24_init();
void nrf24_test()

//uint8_t nrf24_is_interrupt();


#endif
