/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Adc.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void ADCSample(void);
void InitAdcOffset(void);
void CalAdcOffset(void);
void AdcFilter(void);

tAdc_Type tAdc;
extern tGlobal_TypeDef tGlobal;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
