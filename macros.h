/*
 * macros.h
 *
 * Created: 08.03.2016 22:27:41
 *  Author: Light
 */ 


#ifndef MACROS_H_
#define MACROS_H_
/***********************************************************

//reg : имя переменной, регистра
//bit_no : позиция бита
//val : 0 или 1
************************************************************/
#define BIT(bit_no)        (1 << (bit_no))				//генерит маску с установленым bit_no битом

#define ClearBit(reg, bit_no)   (reg) &= ~BIT(bit_no)	//пример: ClearBit(PORTB, 1);	//сбросить 1-й бит PORTB

#define SetBit(reg, bit_no)		(reg) |= BIT(bit_no)	//пример: SetBit(PORTB, 3);		//установить 3-й бит PORTB

#define XOR(reg, bit_no)		(reg) ^= BIT(bit_no)	//пример: XOR(PORTB, 1);		//инвертировать 1-й бит PORTB

#define SetBitVal(reg, bit_no, val) do{if ((val&1)==0) reg &= (~(1<<(bit)));\	
									else reg |= (1<<(bit_no));}while(0)		//пример:	SetBitVal(PORTB, 3, 1); //установить 3-й бит PORTB
									//			SetBitVal(PORTB, 2, 0); //сбросить 2-й бит PORTB

/***********************************************************/

#define GET(reg, bit_no)		((reg) & BIT(bit_no))	//если бит установлен выдаст значение отличное от нуля

#define BitIsClear(reg, bit_no)	((reg & (1<<(bit_no))) == 0)	//пример: if (BitIsClear(PORTB,1)) {...} //если бит очищен

#define BitIsSet(reg, bit_no)	((reg & (1<<(bit_no))) != 0)	//пример: if(BitIsSet(PORTB,2)) {...} //если бит установлен

#define XOR(reg, bit_no)   (reg) ^= BIT(bit_no)			//меняет значение бита на противоположное 





#endif /* MACROS_H_ */