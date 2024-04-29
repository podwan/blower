/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Protect.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void ProtectInitialize(void);
void ProtectApp(void);

extern void PageErase(void);
extern void FLASH_write(unsigned int Addr,unsigned long long data);

Protect_TypeDef tProtect;

extern System_TypeDef tSystem;
extern tGlobal_TypeDef tGlobal;

#define 	VBUS200V		1970		//2K4 / 302K4 x Vbus / 3.3 x 4096 = 1970
#define 	VBUS280V		2758		//2K4 / 302K4 x Vbus / 3.3 x 4096 = 2758
#define 	VBUS380V		3743		//2K4 / 302K4 x Vbus / 3.3 x 4096 = 3743

#define 	HT80C			3599		//2.9 / 3.3 x 4096 = 3599 50uA
#define 	NTC80C			1442		//1.63 / (1.63 + 3) x 4096 = 1442

#define 	V12H16V			3310		//16 / 6 / 3.3 x 4096 = 3310
#define 	V12L10V			2068		//10 / 6 / 3.3 x 4096 = 2068

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
