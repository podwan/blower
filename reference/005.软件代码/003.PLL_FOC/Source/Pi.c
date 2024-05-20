/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Pi.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Pi.h"
/**************************************************************************************************
* Pi
**************************************************************************************************/
/*===============================================================================================*/
void IpiControl(tPI_Type *tPiStruct)
{
	UNION_S32 sTemp32A,sTemp32B;
	tPI_Type tIVar;
    
    tIVar = *tPiStruct;	
	
	sTemp32A.S32 = tIVar.Kp * tIVar.sErr; //Q16 * Q15
	
	if (sTemp32A.Words.High > tIVar.sLimit)
	{
		sTemp32A.Words.High = tIVar.sLimit;
		sTemp32A.Words.Low = 0;
		tIVar.sLimit = 0;
	}	
	else if (sTemp32A.Words.High < -tIVar.sLimit)
	{
		sTemp32A.Words.High = -tIVar.sLimit;
		sTemp32A.Words.Low = 0;
		tIVar.sLimit = 0;
	}
	else
	{
		if (sTemp32A.Words.High >= 0)
		{	
			tIVar.sLimit -= sTemp32A.Words.High;
		}
		else
		{
			tIVar.sLimit += sTemp32A.Words.High;
		}	
	}	
	
	sTemp32B.S32 = tIVar.Ki * tIVar.sErr;
	tIVar.qSumErr32.S32 += sTemp32B.S32;
	
	if (tIVar.qSumErr32.Words.High > tIVar.sLimit)
	{
		tIVar.qSumErr32.Words.High = tIVar.sLimit;
		tIVar.qSumErr32.Words.Low = 0;
	}	
	else if (tIVar.qSumErr32.Words.High < -tIVar.sLimit)
	{
		tIVar.qSumErr32.Words.High = -tIVar.sLimit;
		tIVar.qSumErr32.Words.Low = 0;
	}	
	
	sTemp32A.S32 += tIVar.qSumErr32.S32;
	tIVar.sOut = sTemp32A.Words.High; //Q15
	
	*tPiStruct = tIVar;
}	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
