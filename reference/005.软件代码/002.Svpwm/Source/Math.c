/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Math.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Math.h"	
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
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
