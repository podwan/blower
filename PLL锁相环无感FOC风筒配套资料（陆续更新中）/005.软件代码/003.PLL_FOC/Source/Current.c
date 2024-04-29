/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Current.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Current.h"
/**************************************************************************************************
* Current
**************************************************************************************************/
/*===============================================================================================*/
void CurrentInitialize(void)
{
	tIm.qIa = 0;
	tIm.qIb = 0;
	tIm.qIc = 0;
	
	tIm.qIalpha = 0;
	tIm.qIbeta = 0;	
	
	tIm.qId = 0;
	tIm.qIq = 0;	
}
/*===============================================================================================*/

/*===============================================================================================*/
void CurrentSample(void)
{
	GetIabc();
	GetIalphabeta();
	GetIdq(); 
}
/*============================================================================*/
//检流电阻负压代表Ia的正向电流，即注入电机的电流为正向电流。
/*============================================================================*/
static void GetIabc(void)
{
    signed short int sIa,sIb,sIc;
    
    sIa = (signed short int)((tIm.qIoffsetA - tGlobal.IaValue) << 3); //Q15
    sIb = (signed short int)((tIm.qIoffsetB - tGlobal.IbValue) << 3); //Q15    
    sIc = 0 - sIa - sIb;
    
    tIm.qIa = sIa;
    tIm.qIb = sIb;
    tIm.qIc = sIc;
}
/*============================================================================*/
//Clarke变换，计算公式
//Ialpha = Ia
//Ibeta = (Ia + 2Ib)/sqrt(3)
//Ibeta = 1/sqrt(3) * Ia + 1/sqrt(3) * 2Ib
/*============================================================================*/
static void GetIalphabeta(void)
{
    UNION_S32 sTemp32A,sTemp32B;
	unsigned short int Temp;
    
    tIm.qIalpha = tIm.qIa; //Q15
	
	Temp = ONE_DIV_SQRT3;							
	sTemp32A.S32 = (signed int)(Temp * tIm.qIa);	
	sTemp32B.S32 = (signed int)(Temp * tIm.qIb);		
	
    sTemp32B.S32 += sTemp32B.S32;					
    sTemp32A.S32 += sTemp32B.S32;
    tIm.qIbeta = sTemp32A.Words.High;//Q15			
}
/*===============================================================================================*/
void GetCurrentOffset(void)
{
	tIm.qIoffsetA = tGlobal.IaOffset;
	tIm.qIoffsetB = tGlobal.IbOffset; 
}	
/*============================================================================*/
//Park变换
//Id = Ialpha * Cosθr + Ibeta * Sinθr
//Iq = -Ialpha * Sinθr + Ibeta * Cosθr
/*============================================================================*/
static void GetIdq(void)
{
    tIm.qId = MulFrac(tIm.qIalpha,tIm.qParkCos) + MulFrac(tIm.qIbeta,tIm.qParkSin);
    tIm.qIq = MulFrac(-tIm.qIalpha,tIm.qParkSin) + MulFrac(tIm.qIbeta,tIm.qParkCos);
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
