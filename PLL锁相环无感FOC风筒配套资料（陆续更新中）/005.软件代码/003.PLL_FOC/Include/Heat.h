/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Heat.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void HeatInitialize(void);
void HeatApp(void);
void ScanfHeatTrigger(void);

extern System_TypeDef tSystem;

Heat_TypeDef tHeat;
extern Switch_TypeDef tSwitch;
extern tGlobal_TypeDef tGlobal;

#define 	HEAT_OFF	(GPIOA -> ODR &= 0xfeff)			//PA8 = 0
#define		HEAT_ON		(GPIOA -> ODR |= 0x0100)			//PA8 = 1

#define		GEAR_OFF	0
#define		GEAR_HALF	1
#define		GEAR_FULL	2
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
