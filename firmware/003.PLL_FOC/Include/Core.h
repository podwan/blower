/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
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
static void ParkAngleSinCos(void);

extern void VoltageInitialize(void);
extern void CurrentInitialize(void);
extern void PllInitialize(void);

extern void InitAdcOffset(void);
extern void CalAdcOffset(void);
extern void GetCurrentOffset(void);

extern void CurrentSample(void);
extern void RotorAnglePLL(void);
extern void GetUs(void);
extern void UsOut(unsigned int Percent,signed int qEAngle);
extern unsigned int CalSinCos(signed short int qM,signed short int qA);

unsigned short int Percent;
signed short int qAngle;
signed short int qAngleDelta;
unsigned short MTick;
unsigned short ATick;

tCore_TypeDef tCore;

extern tGlobal_TypeDef tGlobal;
extern tUm_TypeDef tUm;
extern tIm_TypeDef tIm;
extern tPI_Type tPiId;
extern tPI_Type tPiIq;
extern tRm_TypeDef tRm;
extern tEm_TypeDef tEm;

#define     STATE_STOP    	0
#define     STATE_OFFSET	1
#define     STATE_BSTART  	2
#define     STATE_BWAIT   	3
#define     STATE_OSTART  	4
#define     STATE_OWAIT  	5
#define     STATE_FORCE		6
#define     STATE_RUN		7	
#define     STATE_TEST		8

#define     K_START_ACC_END     17000    //1000
#define     K_STARTACCELERATION 2		//10		
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
