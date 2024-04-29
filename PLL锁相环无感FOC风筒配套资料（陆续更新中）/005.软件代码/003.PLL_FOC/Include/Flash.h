/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Flash.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

static void Flash_unlock(void);
static void Flash_lock(void);

void PageErase(void);
void FLASH_write(unsigned int Addr,unsigned long long data);
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
