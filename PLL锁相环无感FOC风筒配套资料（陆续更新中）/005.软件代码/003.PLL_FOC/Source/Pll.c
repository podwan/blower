/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Pll.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Pll.h"
/**************************************************************************************************
* Voltage
**************************************************************************************************/
/*===============================================================================================*/
//Pll -Ed --> tRm.qAngle
//Ualpha = R x Ialpha + L x dIalpha / dt + Ealpha
//tUm.qUalpha x Uo = R x tIm.qIalpha x Io + L x d(tIm.qIalpha) / dt x Io + tEm.qEalpha x Uo
//tUm.qUalpha = R x tIm.qIalpha x Io / Uo + L x d(tIm.qIalpha) / dt x Io / Uo + tEm.qEalpha
//tUm.qUalpha = Kr x tIm.qIalpha + Kl x d(tIm.qIalpha) + tEm.qEalpha
//tUm.qUbeta = Kr x tIm.qIbeta + Kl x d(tIm.qIbeta) + tEm.qEbeta
//Ubeta = R x Ibeta + L x dIbeta / dt + Ebeta
/*===============================================================================================*/
void PllInitialize(void)
{
	tIm.qIalphaLast = 0;
	tIm.qIbetaLast = 0;	
	
	tEm.qKr = PLL_KR;			
	tEm.qKl = PLL_KL;			
	tEm.qEd = 0;
	
	tRm.qAngle = 0;
	tRm.qAngleDalta = 0;
    
	tPiPll.qSumErr32.S32 = 0;
}
/*===============================================================================================*/
//tUm.qUalpha = Kr x tIm.qIalpha + Kl x d(tIm.qIalpha) + tEm.qEalpha
//tUm.qUbeta = Kr x tIm.qIbeta + Kl x d(tIm.qIbeta) + tEm.qEbeta
void RotorAnglePLL(void)
{
	UNION_S32 sTemp32A,sTemp32B;
	signed short int sTemp16;
	
	UNION_U32 Temp32;
	signed short int sTempSin;
	signed short int sTempCos;
	
	sTemp32A.S32 = (signed int)(tEm.qKr * tIm.qIalpha);
	sTemp32A.S32 <<= 1;
	sTemp16 = tIm.qIalpha - tIm.qIalphaLast;
	tIm.qIalphaLast = tIm.qIalpha;
	sTemp32B.S32 = (signed int)(tEm.qKl * sTemp16);
	sTemp32B.S32 <<= 1;
	sTemp32B.S32 += sTemp32A.S32;
	tEm.qEalpha = tUm.qUalpha - sTemp32B.Words.High;
	
	sTemp32A.S32 = (signed int)(tEm.qKr * tIm.qIbeta);
	sTemp32A.S32 <<= 1;
	sTemp16 = tIm.qIbeta - tIm.qIbetaLast;
	tIm.qIbetaLast = tIm.qIbeta;
	sTemp32B.S32 = (signed int)(tEm.qKl * sTemp16);
	sTemp32B.S32 <<= 1;
	sTemp32B.S32 += sTemp32A.S32;
	tEm.qEbeta = tUm.qUbeta - sTemp32B.Words.High;
	
	Temp32.U32 = CalSinCos(0x7fff,tRm.qAngle);
	sTempCos = (signed short int)Temp32.Words.Low;
	sTempSin = (signed short int)Temp32.Words.High;	
	
	sTemp32A.S32 = (signed int)(sTempCos * tEm.qEalpha);
	sTemp32A.S32 <<= 1;
	sTemp32B.S32 = (signed int)(sTempSin * tEm.qEbeta);
	sTemp32B.S32 <<= 1;	
	sTemp32B.S32 += sTemp32A.S32;		
	sTemp32B.S32 <<= 4;
	tEm.qEd = sTemp32B.Words.High;
	
    tPiPll.sErr = -tEm.qEd;
    tPiPll.Kp = PLL_KP;				
    tPiPll.Ki = PLL_KI;		
	tPiPll.sLimit = PLL_LIMIT;	
    IpiControl(&tPiPll);	
	tRm.qAngleDalta = tPiPll.sOut;
	
	tRm.qAngle += tRm.qAngleDalta;  
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
