/**************************************************************************************************
 * 张飞实战电子
 * @project Svpwm
 * @file    Adc.h
 * @author  张飞实战电子团队
 * @date    2024/03/28
 * @version V100
 * @Copyright  软件著作权张飞实战电子所有
 **************************************************************************************************/

#include "userMain.h"

typedef struct
{
    unsigned short int ValueInstant;
    unsigned short int ValueAverage;
    unsigned int ValueSum32;

    unsigned short int ValueNum;
    unsigned short int ValueFilter;
} tAnx_Type;

typedef struct
{
    tAnx_Type An11, An12, An13, An14, An21, An22, An23, An24;
    unsigned short int Index;
} tAdc_Type;

/*===========================================================================*/

void AdcSample(void);
void InitAdcOffset(void);
void CalAdcOffset(void);

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
