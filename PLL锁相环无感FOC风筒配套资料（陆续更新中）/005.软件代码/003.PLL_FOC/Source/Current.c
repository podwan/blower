/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Current.c
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
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
//�������踺ѹ����Ia�������������ע�����ĵ���Ϊ���������
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
//Clarke�任�����㹫ʽ
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
//Park�任
//Id = Ialpha * Cos��r + Ibeta * Sin��r
//Iq = -Ialpha * Sin��r + Ibeta * Cos��r
/*============================================================================*/
static void GetIdq(void)
{
    tIm.qId = MulFrac(tIm.qIalpha,tIm.qParkCos) + MulFrac(tIm.qIbeta,tIm.qParkSin);
    tIm.qIq = MulFrac(-tIm.qIalpha,tIm.qParkSin) + MulFrac(tIm.qIbeta,tIm.qParkCos);
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
