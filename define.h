
#ifndef DEFINE_H
#define DEFINE_H

//#define F_CPU 16000000UL /*������� ������ ����������������*/
#define F_CPU	8000000UL
#define _U_		__attribute__((__unused__))

//#define F_CPU 7372800UL

#endif

/*=======================================================================
���               ������ � ������		�������� �������� 
char						1 (8)	�� -128 �� 127    
short						2 (16)	�� -32768 �� 32767 
long						4 (32)	�� -2 147 483 648 �� 2 147 483 647 
unsigned char     			1 (8)	o� 0 �� 255    
unsigned short				2 (16)	�� 0 �� 65535 
unsigned long				4 (32)	�� 0 �� 4 294 967 295 

���	              ������ � ������	�������� ��������
char	                  1 (8)	    �� -128 �� 127
unsigned char	          1 (8)	    �� 0 �� 255
char	                  1 (8)	    �� -128 �� 127
int	                      2 (16)	�� -32768 �� 32767
unsigned int	          2 (16)	�� 0 �� 65535
signed int	              2 (16)	�� -32768 �� 32767
short int	              2 (16)	�� -32768 �� 32767
unsigned short int	      2 (16)	�� 0 �� 65535
signed short int	      2 (16)	�� -32768 �� 32767
long int	              4 (32)	�� -2147483648 �� 2147483647
unsigned long int	      4 (32)	�� 0 �� 4294967295
signed long int	          4 (32)	�� -2147483648 �� 2147483647
float	                  4 (32)	�� 3.4�-38 �� 3.4�+38
double	                  8 (64)	�� 1.7�-308 �� 1.7�+308
long double	              10 (80)	�� 3.4�-4932 �� 3.4�+4932


volatile - ���������� � ���� ���������� ����������� �� ����� ����� �������.
=========================================================================
<< - �������� ����� �����
1<<6 ��� 0b01000000 �������� 1 ����� �� 6 �������
5<<5 ��� 0b10100000 �������� 5 ����� �� 5 �������
=========================================================================
>> - �������� ����� ������
255;  //0b11111111
255 >> 1; ��������� 127 ��� 0b01111111
========================================================================= 
~    - �������� ��������
94 ��� 0b01011110
~ 94 ������ 161 ��� 0b10100001
=========================================================================
| - ����������� ���
tmp = 155
tmp = tmp | 4; //������������� � ������� ������ ��� ���������� tmp
    155     0b10011011    
|
      4     0b00000100    
   =159     0b10011111
������������ ���������� ����� ��� ��������� ����� �������� ��������. 
������� ������� ��� ������ � ������� �������� ������ ����� <<.
tmp = tmp | (1<<4); //������������� � ������� ��������� ��� ���������� tmp
������ ������ ������ � �������� ������� �� ������ ������� �����, 
��������� �������� ��� ����� ���������� ������ � ��������� ���������� tmp, 
��������� ��������� ���������� tmp.
���������� ��������� ����� � ������� ����� ���
tmp = tmp | (1<<7)|(1<<5)|(1<<0);
tmp |= (1<<7)|(1<<5)|(1<<0);
������������� � ������� �������, ����� � ������� ���� ���������� tmp
=========================================================================
& -��������� �
	A B X
	0 0 0
	0 1 0
	1 0 0
	1 1 0
tmp = tmp & (~((1<<3)|(1<<5)|(1<<6))); //�������� ������, ����� � ������ ���� 
��� ��� 
tmp &= (~((1<<3)|(1<<5)|(1<<6)))
=========================================================================
^ -��������� ����������� ���
	tmp = 155;0b10011011
    tmp = tmp ^ 8; // ����������� ��������� ��� ��������� tmp
    155         0b10011011    
^
    8           0b00001000    
 =  147         0b10010011
tmp = tmp ^ (1<<3); // ����������� ������ ��� ��������� tmp ��� ���
tmp ^= (1<<4);  //����������� �������� ���
����� ������������� ��������� ����� ������������
tmp ^= ((1<<4)|(1<<2)|(1<<1)); //����������� 4,2 � 1 ����
=========================================================================
��� ��������� ���������� �� ��� � ����������? ����� �������� ��� ����, 
����� ������������, � ����� �������� ���������� �������� � ����� 
if ((tmp & (1<<2)) != 0 ){
      // ���� ����� �����������, ������ ���� ����������
      // ������ ��� ���������� tmp
   }
� ����� �������� ���� ��� �������
    if ((tmp & (1<<2)) == 0 ){
      // ���� ����� �����������, ������ ���� �� ����������
      // ������ ��� ���������� tmp
    }
=========================================================================	
��������  ��������
	==		�����
	!=		�� �����
	>		������
	>=		������ ��� �����
	<		������
	<=		������ ��� �����
=========================================================================		
*/	     
/*
���� ��������	���������� ��������
( )				����� �������
[ ]				��������� �������� �������
.				��������� �������� ������
->				��������� �������� ������
!				���������� ���������
~				����������� ���������
-				��������� �����
++				���������� �� �������
--				���������� �� �������
&				������ ������
*				��������� �� ������
(���)			�������������� ���� (�.�. (float) a)
sizeof( )		����������� ������� � ������
*				���������
/				�������
%				����������� ������� �� �������
+				��������
-				���������
<<				����� �����
>>				����� ������
<				������, ���
<=				������ ��� �����
>				������, ���
>=				������ ��� �����
==				�����
!=				�� �����
&				����������� ���������� "�"
^				����������� ����������� "���"
|				����������� ���������� "���"
&&				���������� "�"
||				���������� "���"
?:				�������� (���������) ��������
=				������������
,				�������� �������_
_________________________________________________
+=, - =, *=,  
%=, <<=,/=,		��������� �������� ������������ (��������, � *= b(�.�. a = a * b) � �.�.)
>>=,&=,|=,^= 
_________________________________________________					
 */

/* DEFINE_H_ */