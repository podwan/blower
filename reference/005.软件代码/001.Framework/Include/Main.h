/**************************************************************************************************
* �ŷ�ʵս����FOC�߽׿γ�
* @project Framework
* @file    Main.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/3/12
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

int Main(void);
void ADC1_2_IRQHandler(void);
static void SysTimeCount(void);

extern void Initialize(void);
extern void AdcSample(void);

System_TypeDef tSystem;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
