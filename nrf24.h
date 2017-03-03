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


uint8_t	nrf24_init();
void nrf24_test();
void check_radio();

#endif
