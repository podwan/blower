/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Curretn.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\CoreDef.h"

void CurrentInitialize(void);
void CurrentSample(void);
void CalCurrentOffset(void);

static void GetIabc(void);
static void GetIalphabeta(void);
static void GetIdq(void);

extern signed short int MulFrac(signed short int qX,signed short int qY);

tIm_TypeDef tIm;

extern tGlobal_TypeDef tGlobal;
extern tUm_TypeDef tUm;

#define     ONE_DIV_SQRT3   37837  //Q16
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
