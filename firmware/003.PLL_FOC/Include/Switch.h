/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Switch.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void SwitchInitialize(void);
void SwitchApp(void);

static void GetSwitchSpeed(void);

extern System_TypeDef tSystem;

Switch_TypeDef tSwitch;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
