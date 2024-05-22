/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
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

void GetUs(void);

static signed short VoltRippleComp(signed short Vdq);

static void GetUsSector(unsigned short int UAngle);
static void GetUxyz(signed short int qUA);
static void VectorActionTimeCalculate(unsigned short int Percent,signed short int Sa,signed short int Sb);
static void SvpwmOut(unsigned short int Percent);
static void GetUalphabeta(void);

extern unsigned int CalAtan(signed short int qY,signed short int qX);
extern unsigned int CalSinCos(signed short int qM,signed short int qA);
extern signed short int MulFrac(signed short int qX,signed short int qY);
extern unsigned short int CalSqrt(unsigned short int m);
extern void IpiControl(tPI_Type *tPiStruct);

tUm_TypeDef tUm;

tPI_Type tPiId,tPiIq;

extern tCore_TypeDef tCore;

extern tIm_TypeDef tIm;
extern tGlobal_TypeDef tGlobal;

#define    SQRT3DIV2    56756
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
