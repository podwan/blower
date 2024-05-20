/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Motor.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void MotorInitialize(void);
void MotorApp(void);

extern void CoreInitialize(void);
extern System_TypeDef tSystem;

Motor_TypeDef tMotor;
tGlobal_TypeDef tGlobal;

#define     HIGH_IQ            	18022		

#define     LOW_IQ            	10000
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
