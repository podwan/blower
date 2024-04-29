/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Core.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\CoreDef.h"
#include "..\Include\UserParams.h"

void CoreInitialize(void);
void CoreMachine(void);

static void Close6Pwm(void);
static void Open3LowPwm(void);
static void Open6WorkPwm(void);

extern void VoltageInitialize(void);

extern void UsOut(unsigned int Percent,signed int qEAngle);
extern unsigned int CalSinCos(signed short int qM,signed short int qA);

tCore_TypeDef tCore;

tGlobal_TypeDef tGlobal;
extern tUm_TypeDef tUm;

#define     STATE_STOP    	0
#define     STATE_BSTART  	1
#define     STATE_BWAIT   	2
#define     STATE_RUN		3	
	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
