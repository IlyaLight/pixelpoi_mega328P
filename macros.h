/*
 * macros.h
 *
 * Created: 08.03.2016 22:27:41
 *  Author: Light
 */ 


#ifndef MACROS_H_
#define MACROS_H_

//-------------------------------
// Работа с битами
//-------------------------------
#define BIT(bit_no)        (1 << (bit_no))			//генерит маску с установленым bit_no битом
#define CLR(reg, bit_no)   (reg) &= ~BIT(bit_no)	//сбросить бит
#define SET(reg, bit_no)   (reg) |= BIT(bit_no)		//установить бит
#define GET(reg, bit_no)   ( (reg) & BIT(bit_no) )	//если бит установлен выдаст значение отличное от нуля
#define XOR(reg, bit_no)   (reg) ^= BIT(bit_no)		//меняет значение бита на противоположное 





#endif /* MACROS_H_ */