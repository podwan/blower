/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Motor.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Motor.h"
/**************************************************************************************************
* Motor Application
**************************************************************************************************/
void MotorInitialize(void)
{
	CoreInitialize();
}
/*===============================================================================================*/
//input:	tSystem.FanSpeed
/*===============================================================================================*/
void MotorApp(void)
{
	if (tGlobal.ErrorCode == 0)
		tMotor.Speed = tSystem.FanSpeed;
	else
		tMotor.Speed = 0;
	
	if (tMotor.Speed) 
	{
		if (tGlobal.MotorStatus == 0)
		{
			tGlobal.MotorStatus = 1;			
			tGlobal.CoreIndex = 1;
		}	
		else
		{						
			if (tMotor.Speed == 1)
			{		
				DisIE;
				tGlobal.qSetIq = LOW_IQ;
				EnIE;		

			}
			else if (tMotor.Speed == 2)
			{
				DisIE;
				tGlobal.qSetIq = HIGH_IQ;
				EnIE;	
			}	
		}	
	}	
	else
	{					
		tGlobal.CoreIndex = 0;
	}
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
