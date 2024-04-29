/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Pll.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\CoreDef.h"
#include "..\Include\UserParams.h"

void PllInitialize(void);
void RotorAnglePLL(void);

extern unsigned int CalSinCos(signed short int qM,signed short int qA);
extern signed short int QLowPassFilter(signed short int qY,signed short int qX,signed short int qK);
extern unsigned int CalAtan(signed short int qY,signed short int qX);
extern signed short int MulFrac(signed short int qX,signed short int qY);

extern void IpiControl(tPI_Type *tPiStruct);

tRm_TypeDef tRm;
tEm_TypeDef tEm;

tPI_Type tPiPll;

extern tUm_TypeDef tUm;
extern tIm_TypeDef tIm;

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
