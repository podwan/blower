/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Switch.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Switch.h"
/**************************************************************************************************
* Switch Application									
PA8		output
PA9		low speed      high pulse input	
PA10	input		   high pulse input
**************************************************************************************************/
/*===============================================================================================*/
void SwitchInitialize(void)
{
	tSwitch.Speed = 0;
	tSwitch.RisingNum = 0;
	tSwitch.Count = 0;
	
	tSystem.FanSpeed = 0;
	tSwitch.Tick = 0;
}
/*===============================================================================================*/
//Output:	tSystem.FanSpeed
void SwitchApp(void)
{
	if(tSwitch.Tick == 0)
	{
		tSwitch.Tick = 1;				//1ms
		
		GetSwitchSpeed();
		
		tSystem.FanSpeed = tSwitch.Speed;
	}
}
/*===============================================================================================*/
//0 stop no speed:	PA9 high level and PA10 high level 		more than 20ms
//1 low speed:	PA9 high pulse input and PA10 high level 	more than 20ms
//2 high speed:	PA9 high pulse input and PA10 high pulse 	more than 20ms
//output:		tSwitch.Speed
static void GetSwitchSpeed(void)
{
	unsigned int Temp;	
	
	switch(tSwitch.Speed)
	{
		case 0:
			if (tSwitch.RisingNum)
			{
				if (tSwitch.Count == 0)
				{
					tSwitch.Count = 500;					
					tSwitch.Speed = 1;
					tSwitch.RisingNum = 0;
				}
				else
				{
					tSwitch.Count --;
				}				
			}
			break;
		case 1:

				Temp = GPIOA -> IDR;
				Temp &= 0x0200;			//PA9
		
				if (Temp == 0)
				{
					tSwitch.Count = 500;
				}	
				else
				{	
					if (tSwitch.Count == 0)
					{
						tSwitch.Count = 500;						
						tSwitch.Speed = 0;
						tSwitch.RisingNum = 0;
					}						
					else
					{
						tSwitch.Count --;
					}
				}
				
				
				Temp = GPIOA -> IDR;
				Temp &= 0x0400;			//PA10
				
				if (Temp == 0)
				{
					tSwitch.Speed = 2;
					tSwitch.RisingNum = 0;
					tSwitch.HCount = 500;
				}				
		
			break;
		case 2:			
				
			Temp = GPIOA -> IDR;
			Temp &= 0x0400;			//PA10
			
			if (Temp)
			{
				if (tSwitch.HCount)
				{	
					tSwitch.HCount --;
				}	
				else
				{
					tSwitch.Speed = 1;
					tSwitch.RisingNum = 0;
					tSwitch.Count = 500;
				}						
			}				
			else
			{
				tSwitch.HCount = 500;
			}	
			break;
		default:
			break;
	}
}	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
