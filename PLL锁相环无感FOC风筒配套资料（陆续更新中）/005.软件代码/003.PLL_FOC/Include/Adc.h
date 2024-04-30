/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Adc.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
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
