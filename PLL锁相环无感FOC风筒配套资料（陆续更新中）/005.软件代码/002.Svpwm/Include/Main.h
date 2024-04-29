/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Main.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

int Main(void);
void ADC1_2_IRQHandler(void);

static void SysTimeCount(void);

extern void Initialize(void);

extern void CoreMachine(void);

extern void AdcSample(void);

System_TypeDef tSystem;
extern tGlobal_TypeDef tGlobal;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
