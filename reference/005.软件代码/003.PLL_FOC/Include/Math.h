/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Math.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

signed short int MulFrac(signed short int qX,signed short int qY);
unsigned int CalSinCos(signed short int qM,signed short int qA);
unsigned int CalAtan(signed short int qY,signed short int qX);
unsigned short int CalSqrt(unsigned short int m);

#define D0P027	885
#define D0P75	24576
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
