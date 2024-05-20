/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Motor.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
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
