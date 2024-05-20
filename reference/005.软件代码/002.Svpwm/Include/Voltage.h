/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Voltage.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\CoreDef.h"
#include "..\Include\UserParams.h"

void VoltageInitialize(void);
void UsOut(unsigned short int Percent,signed short int qUA);

static void GetUsSector(unsigned short int UAngle);
static void GetUxyz(signed short int qUA);
static void VectorActionTimeCalculate(unsigned short int Percent,signed short int Sa,signed short int Sb);
static void SvpwmOut(unsigned short int Percent);

extern unsigned int CalSinCos(signed short int qM,signed short int qA);

tUm_TypeDef tUm;

extern tCore_TypeDef tCore;

extern tGlobal_TypeDef tGlobal;

#define    SQRT3DIV2    56756
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
