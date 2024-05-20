/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Heat.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Heat.h"
/**************************************************************************************************
* Heat Application				
1.PA8		TIM1_CH1
2.PA9		TIM1_CH2	Low Speed
3.PA10		TIM1_CH3	High Speed
**************************************************************************************************/
void HeatInitialize(void)
{
	tHeat.Gear = GEAR_OFF;
	tHeat.ZTick = 25;
}
/*===============================================================================================*/
//input:	tSystem.HeatGear
//0		off:		tHeat.Gear = 0		no trigger
//1		Half:		tHeat.Gear = 1		Half Heat
//2		Full:		tHeat.Gear = 2		Full Heat
/*===============================================================================================*/
void HeatApp(void)
{
	unsigned short TempH,TempL;
	unsigned int Temp;		
	
	TempH = 60 - tHeat.ZTick;
	TempL = 60 - tHeat.ZTick - 5;
	
	DisIE;
	Temp = tGlobal.RunTime;
	EnIE;
	
	if (tHeat.Tick == 0)
	{	
		tHeat.Gear = tSystem.HeatGear;
	}
	else if ((tHeat.Tick >= TempL) && (tHeat.Tick <= TempH))
	{
		if (Temp > 2)
			HEAT_ON;				//PA8 = 1
	}
	else
	{		
		HEAT_OFF;					//PA8 = 0		
	}	
}
/*===============================================================================================*/
//call by interrupt
void ScanfHeatTrigger(void)
{
	unsigned int Temp;	
	
	Temp = TIM1 -> SR;
    
    if((Temp & 0x00000004) != 0)
    {
        TIM1 -> SR &= 0xfffffffb;
		
		TIM1 -> CNT = 0;	
		
		Temp = TIM1 -> CCR2;	
		
		if (Temp < 20000)		//5ms
		{
			Temp >>= 2;
			Temp /= 40;
			Temp >>= 1;
			if ((Temp > 10) && (Temp < 40))
			{
				tHeat.ZTick = Temp;
			}
			else
			{
				tHeat.ZTick = 25;
			}	
		}
		else
		{	
			tSwitch.RisingNum ++;
			tHeat.ZCount ++;		
			
			if (tHeat.Gear == GEAR_HALF)
			{
                if(tHeat.ZCount >= 3) 
                {
                    tHeat.ZCount = 0;
                    tHeat.Tick = 60;
                }
			}

			if (tHeat.Gear == GEAR_FULL)
			{
                if ((tHeat.ZCount & 0x00000001) == 0)
				{			
					tHeat.Tick = 60;
				}
			}
		}				
    }	
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
