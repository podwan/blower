/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Heat.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
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
