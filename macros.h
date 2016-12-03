/*
 * macros.h
 *
 * Created: 08.03.2016 22:27:41
 *  Author: Light
 */ 


#ifndef MACROS_H_
#define MACROS_H_
/***********************************************************

//reg : ��� ����������, ��������
//bit_no : ������� ����
//val : 0 ��� 1
************************************************************/
#define BIT(bit_no)        (1 << (bit_no))				//������� ����� � ������������ bit_no �����

#define ClearBit(reg, bit_no)   (reg) &= ~BIT(bit_no)	//������: ClearBit(PORTB, 1);	//�������� 1-� ��� PORTB

#define SetBit(reg, bit_no)		(reg) |= BIT(bit_no)	//������: SetBit(PORTB, 3);		//���������� 3-� ��� PORTB

#define XOR(reg, bit_no)		(reg) ^= BIT(bit_no)	//������: XOR(PORTB, 1);		//������������� 1-� ��� PORTB

#define SetBitVal(reg, bit_no, val) do{if ((val&1)==0) reg &= (~(1<<(bit)));\	
									else reg |= (1<<(bit_no));}while(0)		//������:	SetBitVal(PORTB, 3, 1); //���������� 3-� ��� PORTB
									//			SetBitVal(PORTB, 2, 0); //�������� 2-� ��� PORTB

/***********************************************************/

#define GET(reg, bit_no)		((reg) & BIT(bit_no))	//���� ��� ���������� ������ �������� �������� �� ����

#define BitIsClear(reg, bit_no)	((reg & (1<<(bit_no))) == 0)	//������: if (BitIsClear(PORTB,1)) {...} //���� ��� ������

#define BitIsSet(reg, bit_no)	((reg & (1<<(bit_no))) != 0)	//������: if(BitIsSet(PORTB,2)) {...} //���� ��� ����������

#define XOR(reg, bit_no)   (reg) ^= BIT(bit_no)			//������ �������� ���� �� ��������������� 





#endif /* MACROS_H_ */