/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Key.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Key.h"
/**************************************************************************************************
* Key Application			PF0			
**************************************************************************************************/
void KeyInitialize(void)
{
    unsigned int *p = 0;
    
	tKey.Tick = 0;
	tKey.Index = PRESS_WAIT;
    
    //Read KeyValue
    p = (unsigned int*)0x0801F800;
    tSystem.KeyValue = *p;
    tKey.Value = tSystem.KeyValue;
}
/*===============================================================================================*/
//Output:	tSystem.HeatGear
void KeyApp(void)
{
	if (tSystem.FanSpeed)
	{	
		KeyScanf();	
		tSystem.HeatGear = tKey.Value;
	}
	else
	{
		tSystem.HeatGear = 0;
	}	
}
/*===============================================================================================*/
//output:	tKey.Value 0 1 2 
static void KeyScanf(void)
{
	unsigned int Temp;

	if (tKey.Tick == 0)
	{
		tKey.Tick = 10;					//10ms
		
		Temp = GPIOF -> IDR;			//PF0
		if (Temp & 0x00000001)
			tKey.Input = STATUS_RELEASE;
		else
			tKey.Input = STATUS_PRESS;
		
		switch(tKey.Index)
		{
			case PRESS_WAIT:
				if (tKey.Input == STATUS_PRESS)
				{		
					tKey.Index = PRESS_DELAY;
					tKey.Delay = 10;
				}
				break;
			case PRESS_DELAY:
				tKey.Delay --;
				if (tKey.Input == STATUS_RELEASE)
				{	
					tKey.Index = PRESS_WAIT;
				}	
				else
				{
					if (tKey.Delay == 0)
						tKey.Index = PRESS_CONFIRM;
				}	
				break;
			case PRESS_CONFIRM:
				tKey.Index = RELEASE_WAIT;								
				break;
			case RELEASE_WAIT:
				if (tKey.Input == STATUS_RELEASE)
				{		
					tKey.Index = RELEASE_DELAY;
					tKey.Delay = 10;
				}
				break;
			case RELEASE_DELAY:
				tKey.Delay --;
				if (tKey.Input == STATUS_PRESS)
				{	
					tKey.Index = RELEASE_WAIT;
				}	
				else
				{
					if (tKey.Delay == 0)
						tKey.Index = RELEASE_CONFIRM;
				}	
				break;
			case RELEASE_CONFIRM:
				tKey.Value ++;
				if (tKey.Value >= 3)
					tKey.Value = 0;
                tSystem.KeyValue = tKey.Value;
				tKey.Index = PRESS_WAIT;
				break;						
			default:
				tKey.Index = PRESS_WAIT;
				break;
		}					
	}	
}	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
