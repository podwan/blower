/**************************************************************************************************
* 张飞实战电子FOC高阶课程
* @project Framework
* @file    Main.h
* @author  张飞实战电子团队
* @date    2024/3/12
* @version V100
* @Copyright  软件著作权张飞实战电子所有
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
