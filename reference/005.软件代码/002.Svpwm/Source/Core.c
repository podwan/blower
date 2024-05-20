/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Core.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Core.h"
/**************************************************************************************************
* State
**************************************************************************************************/
void CoreInitialize(void)
{
	VoltageInitialize();
	
	tGlobal.CoreIndex = 0;
    tCore.FaultNum = 0;
}
/*===============================================================================================*/
//状态机
/*===============================================================================================*/
void CoreMachine(void)
{		
	if (tCore.Tick)
		tCore.Tick --;
	
	if ((TIM8->SR & 0x00000080) != 0)		//BIF = 1, MOE=0
	{
        tCore.FaultNum ++;
        if(tCore.FaultNum >= 3)
        {
            tCore.FaultNum = 0;
            tGlobal.CoreIndex = STATE_STOP;
            
            Close6Pwm();		
            
            VoltageInitialize();		
            
            if (tGlobal.CoreIndex == STATE_STOP)
            {			
                TIM8->SR &= 0xffffff7f;
            }
        }
        else
        {
            TIM8->SR &= 0xffffff7f;
            TIM8->BDTR |= 0x00008000;
        }
	}	
	else
	{
        tCore.FaultNum = 0;
		switch (tGlobal.CoreIndex)
		{
			case STATE_STOP:
				
				Close6Pwm();									
				
				break;
			case STATE_BSTART:				
				
				Open3LowPwm();		
				
				tCore.Tick = 10000;			
				tGlobal.CoreIndex = STATE_BWAIT;
				break;
			
			case STATE_BWAIT:
				if (tCore.Tick == 0)
				{					
					Close6Pwm();
                    VoltageInitialize();
					tGlobal.CoreIndex = STATE_RUN;			
				}
				
				break;	
			case STATE_RUN:	
 				Open6WorkPwm();
				tUm.Percent = 9500;		
				tUm.qEAngle += 100;
				UsOut(tUm.Percent,tUm.qEAngle);				
                
				break;
			
			default:
				tGlobal.CoreIndex = STATE_STOP;
				break;
		}			
	}
	
//DAC看波形
    DAC->DHR12R1 = ((0x8000 + tUm.qUx) >> 4);	
//    DAC->DHR12R1 = ((0x8000 + tUm.qEAngle) >> 4);	
//	DAC->DHR12R1 = tUm.CCR1;	
}	
/*===============================================================================================*/
static void Close6Pwm(void)
{
	TIM8->CCMR1 = 0x00004848;		
	TIM8->CCMR2 = 0x00006848;		
	TIM8->CCER = 0x00001ddd;		
}	
/*===============================================================================================*/
static void Open3LowPwm(void)
{
	TIM8->CCR1 = 2000;
	TIM8->CCR2 = 2000;
	TIM8->CCR3 = 2000;

	TIM8->CCMR1 = 0x00006868;		
	TIM8->CCMR2 = 0x00006868;		
	TIM8->CCER = 0x00001444;		
}
/*===============================================================================================*/
static void Open6WorkPwm(void)
{
	TIM8->CCMR1 = 0x00006868;		
	TIM8->CCMR2 = 0x00006868;		
	TIM8->CCER = 0x00001555;		
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
