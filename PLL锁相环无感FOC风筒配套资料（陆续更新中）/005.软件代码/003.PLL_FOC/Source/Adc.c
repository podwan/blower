/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Adc.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Adc.h"
/*===============================================================================================*/
void AdcSample(void)
{  
	tAdc.An11.ValueInstant = (unsigned short int)ADC1->JDR1; //Ia
    tAdc.An12.ValueInstant = (unsigned short int)ADC1->JDR2; //Vbus
    tAdc.An13.ValueInstant = (unsigned short int)ADC1->JDR3; //HT
    tAdc.An14.ValueInstant = (unsigned short int)ADC1->JDR4; //NTC
    
    tAdc.An21.ValueInstant = (unsigned short int)ADC2->JDR1; //Ib
    tAdc.An22.ValueInstant = (unsigned short int)ADC2->JDR2; //V12
    tAdc.An23.ValueInstant = (unsigned short int)ADC2->JDR3; //VTS-B
    tAdc.An24.ValueInstant = (unsigned short int)ADC2->JDR4; //OPAMP3
	
    tGlobal.IaValue = tAdc.An11.ValueInstant;
    tGlobal.IbValue = tAdc.An21.ValueInstant;
    
	tGlobal.VbusInstant = tAdc.An12.ValueInstant;
	tGlobal.OPAMP3Instant = tAdc.An24.ValueInstant;
}
/*===============================================================================================*/
void InitAdcOffset(void)
{
	tAdc.An11.ValueSum32 = 0;
	tAdc.An11.ValueNum = 0;
	tAdc.An21.ValueSum32 = 0;
	tAdc.An21.ValueNum = 0;
    tAdc.An12.ValueSum32 = 0;
    tAdc.An12.ValueNum = 0;
}
/*===============================================================================================*/
void CalAdcOffset(void)
{
	if (tGlobal.OffsetReq)
	{
		tAdc.An11.ValueSum32 += tAdc.An11.ValueInstant;
		tAdc.An11.ValueNum ++;
		if(tAdc.An11.ValueNum >= 64)
		{
			tAdc.An11.ValueAverage = (unsigned short int)(tAdc.An11.ValueSum32 >> 6);
			tAdc.An11.ValueSum32 = 0;
			tAdc.An11.ValueNum = 0;
		} 
		
		tAdc.An21.ValueSum32 += tAdc.An21.ValueInstant;
		tAdc.An21.ValueNum ++;
		if(tAdc.An21.ValueNum >= 64)
		{
			tAdc.An21.ValueAverage = (unsigned short int)(tAdc.An21.ValueSum32 >> 6);
			tAdc.An21.ValueSum32 = 0;
			tAdc.An21.ValueNum = 0;
            tGlobal.IaOffset = tAdc.An11.ValueAverage;
            tGlobal.IbOffset = tAdc.An21.ValueAverage;
		} 
        
        tAdc.An12.ValueSum32 += tAdc.An12.ValueInstant;
        tAdc.An12.ValueNum ++;
        if(tAdc.An12.ValueNum >= 64)
        {
            tAdc.An12.ValueAverage = (unsigned short int)(tAdc.An12.ValueSum32 >> 6);
            tAdc.An12.ValueSum32 = 0;
            tAdc.An12.ValueNum = 0;
            tGlobal.TargetVbus = tAdc.An12.ValueAverage;
            tGlobal.OffsetReq = 0;
        } 
	}
}	
/*===============================================================================================*/
//1024 x 40us = 40.96ms		4096 x 50us = 204.8ms
void AdcFilter(void)
{
    if (tGlobal.OffsetReq == 0)
	{
        //Vbus
        tAdc.An12.ValueSum32 += tAdc.An12.ValueInstant;
        tAdc.An12.ValueNum ++;
        if(tAdc.An12.ValueNum >= 256)
        {
            tAdc.An12.ValueAverage = (unsigned short int)(tAdc.An12.ValueSum32 >> 8);
            tAdc.An12.ValueSum32 = 0;
            tAdc.An12.ValueNum = 0;
            tGlobal.VbusAverage = tAdc.An12.ValueAverage;
        } 	
    }
	
	//HT
	tAdc.An13.ValueSum32 += tAdc.An13.ValueInstant;
	tAdc.An13.ValueNum ++;
	if(tAdc.An13.ValueNum >= 4096)
	{
		tAdc.An13.ValueAverage = (unsigned short int)(tAdc.An13.ValueSum32 >> 12);
		tAdc.An13.ValueSum32 = 0;
		tAdc.An13.ValueNum = 0;
		tGlobal.HTAverage = tAdc.An13.ValueAverage;
	} 	
	
	//NTC
	tAdc.An14.ValueSum32 += tAdc.An14.ValueInstant;
	tAdc.An14.ValueNum ++;
	if(tAdc.An14.ValueNum >= 4096)
	{
		tAdc.An14.ValueAverage = (unsigned short int)(tAdc.An14.ValueSum32 >> 12);
		tAdc.An14.ValueSum32 = 0;
		tAdc.An14.ValueNum = 0;
		tGlobal.NTCAverage = tAdc.An14.ValueAverage;
	} 	
	
	//V12	64 x 40us = 2.56ms	
	tAdc.An22.ValueSum32 += tAdc.An22.ValueInstant;
	tAdc.An22.ValueNum ++;
	if(tAdc.An22.ValueNum >= 64)
	{
		tAdc.An22.ValueAverage = (unsigned short int)(tAdc.An22.ValueSum32 >> 6);
		tAdc.An22.ValueSum32 = 0;
		tAdc.An22.ValueNum = 0;
		tGlobal.V12Average = tAdc.An22.ValueAverage;
	} 		
}	
/*===============================================================================================*/

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
