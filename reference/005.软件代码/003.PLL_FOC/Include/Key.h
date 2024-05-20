/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Key.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

void KeyInitialize(void);
void KeyApp(void);
static void KeyScanf(void);
Key_TypeDef tKey;

extern void PageErase(void);
extern void FLASH_write(unsigned int Addr,unsigned long long data);

extern System_TypeDef tSystem;

#define     STATUS_RELEASE      0
#define     STATUS_PRESS    	1

#define			PRESS_WAIT				0
#define			PRESS_DELAY				1
#define			PRESS_CONFIRM			2
#define			RELEASE_WAIT			3
#define			RELEASE_DELAY			4
#define			RELEASE_CONFIRM		    5
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
