/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Math.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Math.h"
/*===============================================================================================*/
signed short int MulFrac(signed short int qX,signed short int qY)
{
	UNION_S32 sTemp32A;
	
	sTemp32A.S32 = (signed int)(qX * qY); //Q15*Q15 = Q30
	sTemp32A.S32 <<= 1; //Q31
	
	return (sTemp32A.Words.High); //Q15
}	
/*===============================================================================================*/
unsigned int CalSinCos(signed short int qM,signed short int qA)
{
	unsigned int temp;
	unsigned int res;
	unsigned short M,A;
	
	M = (unsigned short int)qM;
	A = (unsigned short int)qA;

	CORDIC -> CSR = 0x00600050;	//ARGSIZE = 1 (16-bit)	RESSIZE = 1(16-bit)		NARGS = 0	
							//NRES = 0	DMAWEN = 0	DMAREN = 0		IEN = 0
							//SCALE = 0	PRECISION = 0	FUNC=0  Cosine
	temp = (unsigned int)((M << 16) | A);
	CORDIC -> WDATA = temp;

	do
	{	
		temp = CORDIC -> CSR;
	}while ((temp & 0x80000000) == 0);
	
	res = CORDIC -> RDATA;
	return(res);
}	
/*============================================================================*/
unsigned int CalAtan(signed short int qY,signed short int qX)
{
	unsigned int temp;
	UNION_U32 Temp32;
	unsigned short Y,X;
	
	Y = (unsigned short int)qY;
	X = (unsigned short int)qX;
	
	CORDIC -> CSR = 0x00600032;	//ARGSIZE = 1 (16-bit)	RESSIZE = 1(16-bit)		NARGS = 0	
							//NRES = 0	DMAWEN = 0	DMAREN = 0		IEN = 0
							//SCALE = 0	PRECISION = 0	FUNC=2  Phase
	
	temp = (unsigned int)((Y << 16) | X);
	CORDIC -> WDATA = temp;	

	do
	{	
		temp = CORDIC -> CSR;
	}while ((temp & 0x80000000) == 0);
	
	Temp32.U32 = CORDIC -> RDATA;	
	
	return(Temp32.U32);
}
/*============================================================================*/
//input:	0.027 - 1
unsigned short int CalSqrt(unsigned short int m)
{
	unsigned int temp;
	UNION_U32 Temp32;	
	
	if (m < D0P027)
		m = D0P027;
	
	if (m < D0P75)
	{	
		CORDIC -> CSR = 0x00600039;	//ARGSIZE = 1 (16-bit)	RESSIZE = 1(16-bit)		NARGS = 0	
							//NRES = 0	DMAWEN = 0	DMAREN = 0		IEN = 0
							//SCALE = 0	PRECISION = 3	
							//FUNC=9  Square Root
		
		temp = (unsigned int)m;
		CORDIC -> WDATA = temp;	

		do
		{	
			temp = CORDIC -> CSR;
		}while ((temp & 0x80000000) == 0);
		
		Temp32.U32 = CORDIC -> RDATA;			
		return((signed short int)(Temp32.Words.Low));
	}
	else
	{
		CORDIC -> CSR = 0x00600139;	//ARGSIZE = 1 (16-bit)	RESSIZE = 1(16-bit)		NARGS = 0	
							//NRES = 0	DMAWEN = 0	DMAREN = 0		IEN = 0
							//SCALE = 1	PRECISION = 3	
							//FUNC=9  Square Root
		
		temp = (unsigned int)(m >> 1);
		CORDIC -> WDATA = temp;	
        
		do
		{	
			temp = CORDIC -> CSR;
		}while ((temp & 0x80000000) == 0);
		
		Temp32.U32 = CORDIC -> RDATA;			
		return((signed short int)(Temp32.Words.Low << 1));
	}	
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
