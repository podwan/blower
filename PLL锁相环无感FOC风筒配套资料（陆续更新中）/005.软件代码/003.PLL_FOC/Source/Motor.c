/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Motor.c
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
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
