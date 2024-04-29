/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Switch.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void SwitchInitialize(void);
void SwitchApp(void);

static void GetSwitchSpeed(void);

extern System_TypeDef tSystem;

Switch_TypeDef tSwitch;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
