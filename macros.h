/*
 * macros.h
 *
 * Created: 08.03.2016 22:27:41
 *  Author: Light
 */ 


#ifndef MACROS_H_
#define MACROS_H_

//-------------------------------
// ������ � ������
//-------------------------------
#define BIT(bit_no)        (1 << (bit_no))			//������� ����� � ������������ bit_no �����
#define CLR(reg, bit_no)   (reg) &= ~BIT(bit_no)	//�������� ���
#define SET(reg, bit_no)   (reg) |= BIT(bit_no)		//���������� ���
#define GET(reg, bit_no)   ( (reg) & BIT(bit_no) )	//���� ��� ���������� ������ �������� �������� �� ����
#define XOR(reg, bit_no)   (reg) ^= BIT(bit_no)		//������ �������� ���� �� ��������������� 





#endif /* MACROS_H_ */