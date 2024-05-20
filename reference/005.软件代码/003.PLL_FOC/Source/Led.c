/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Led.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Led.h"
/**************************************************************************************************
* Led Application				PC13 --> LEDR			PC14 --> LEDO		PC15 --> LEDB
**************************************************************************************************/
void LedInitialize(void)
{
	tSystem.DebugMode = 0;
}
/*===============================================================================================*/
//LED应用程序
/*===============================================================================================*/
void LedApp(void)
{
	unsigned short int LedStatus;
    
	DisIE;
	tSystem.ErrCode = tGlobal.ErrorCode;
	LedStatus = tGlobal.LedStatus;
	EnIE;	
	
	if (tSystem.DebugMode == 0)
	{
        if (tSystem.KeyValue == 0)
        {
            GPIOC -> ODR &= 0x9fff;
            GPIOC -> ODR |= 0x8000;			//PC15 --> LEDB		
        }
        else if (tSystem.KeyValue == 1)
        {
            GPIOC -> ODR &= 0x5fff;
            GPIOC -> ODR |= 0x4000;			//PC14 --> LEDO
        }
        else if (tSystem.KeyValue == 2)
        {
            GPIOC -> ODR &= 0x3fff;
            GPIOC -> ODR |= 0x2000;			//PC13 --> LEDR
        }	
	}
	else if (tSystem.DebugMode == 1)			//Motor
	{
		if (LedStatus == 0)
		{
			GPIOC -> ODR &= 0x1fff;
		}	
		else if (LedStatus == 1)
		{
			GPIOC -> ODR &= 0x3fff;
			GPIOC -> ODR |= 0x2000;				//PC13 --> LEDR
		}	
		else if (LedStatus == 2)
		{
			GPIOC -> ODR &= 0x7fff;
			GPIOC -> ODR |= 0x6000;				//PC13 PC14 --> LEDR	LEDG
		}	
		else if (LedStatus == 3)
		{
			GPIOC -> ODR |= 0xe000;				//PC13 PC14 PC15--> LEDR  LEDG LEDB
		}
		else if (LedStatus == 4)
		{
			GPIOC -> ODR &= 0x9fff;
			GPIOC -> ODR |= 0x8000;				//PC15 --> LEDB
		}
	}
	else if (tSystem.DebugMode == 2)			//FanSpeed
	{
		if (tSystem.FanSpeed == 0)
		{
			GPIOC -> ODR &= 0x9fff;
			GPIOC -> ODR |= 0x8000;				//PC15 --> LEDB
		}
		else if (tSystem.FanSpeed == 1)
		{
			GPIOC -> ODR &= 0x5fff;
			GPIOC -> ODR |= 0x4000;				//PC14 --> LEDG
		}
		else if (tSystem.FanSpeed == 2)
		{
			GPIOC -> ODR &= 0x3fff;
			GPIOC -> ODR |= 0x2000;				//PC13 --> LEDR
		}	
	}
	else if (tSystem.DebugMode == 3)			//Error
	{
		if (tSystem.ErrCode == 0)
		{	
			if (tSystem.KeyValue == 0)
			{
				GPIOC -> ODR &= 0x9fff;
				GPIOC -> ODR |= 0x8000;			//PC15 --> LEDB		
			}
			else if (tSystem.KeyValue == 1)
			{
				GPIOC -> ODR &= 0x5fff;
				GPIOC -> ODR |= 0x4000;			//PC14 --> LEDO
			}
			else if (tSystem.KeyValue == 2)
			{
				GPIOC -> ODR &= 0x3fff;
				GPIOC -> ODR |= 0x2000;			//PC13 --> LEDR
			}	
		}
		else if (tSystem.ErrCode == 1)			
		{			
			if (tLed.Tick > 250)
			{
				GPIOC -> ODR &= 0x3fff;
				GPIOC -> ODR |= 0x2000;			//PC13 --> LEDR ON
			}	
			else
			{
				GPIOC -> ODR &= 0x1fff;			//PC13 --> LEDR OFF
				if (tLed.Tick == 0)
					tLed.Tick = 500;
			}
		}
		else if (tSystem.ErrCode == 2)
		{
			if (tLed.Tick > 250)
			{
				GPIOC -> ODR &= 0x5fff;
				GPIOC -> ODR |= 0x4000;			//PC14 --> LEDO ON
			}	
			else
			{
				GPIOC -> ODR &= 0x1fff;			//PC14 --> LEDO OFF
				if (tLed.Tick == 0)
					tLed.Tick = 500;
			}
		}
		else if (tSystem.ErrCode == 3)
		{
			if (tLed.Tick > 250)
			{
				GPIOC -> ODR &= 0x9fff;
				GPIOC -> ODR |= 0x8000;			//PC15 --> LEDB ON
			}	
			else
			{
				GPIOC -> ODR &= 0x1fff;			//PC15 --> LEDB OFF
				if (tLed.Tick == 0)
					tLed.Tick = 500;
			}
		}	
		else if (tSystem.ErrCode == 4)
		{
			if (tLed.Tick > 250)
			{
				GPIOC -> ODR &= 0x1fff;
				GPIOC -> ODR |= 0xe000;			//ALL ON
			}	
			else
			{
				GPIOC -> ODR &= 0x1fff;			//ALL OFF
				if (tLed.Tick == 0)
					tLed.Tick = 500;
			}
		}	
	}	
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
