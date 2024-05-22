/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
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
	CurrentInitialize();
	PllInitialize();
	
	tGlobal.CoreIndex = 0;
	tGlobal.LedStatus = 0;
    tCore.FaultNum = 0;
}
/*===============================================================================================*/
//StateMachine tState.Index
/*===============================================================================================*/
void CoreMachine(void)
{	
	CurrentSample();	
	
	if (tCore.Tick)
		tCore.Tick --;
	
	if ((TIM8->SR & 0x00000080) != 0)		//BIF=1, MOE=0
	{
        tCore.FaultNum ++;
        if(tCore.FaultNum >= 3)
        {
            tCore.FaultNum = 0;
            tGlobal.LedStatus = 4;
            tGlobal.CoreIndex = STATE_STOP;
            
            Close6Pwm();		
            
            VoltageInitialize();
            CurrentInitialize();			
            PllInitialize();		
            
            tGlobal.ErrorCode = 1;
            
            tGlobal.RunTime = 0;
            
            if (tGlobal.CoreIndex == STATE_STOP)
            {			
                tGlobal.MotorStatus = 0;
                TIM8->SR &= 0xffffff7f;
            }
        }
        else
        {
            TIM8->SR &= 0xffffff7f;
            TIM8->BDTR |= 0x00008000;		//MOE=1
        }
	}	
	else
	{
        tCore.FaultNum = 0;
		switch (tGlobal.CoreIndex)
		{
			case STATE_STOP:
				
				Close6Pwm();						//close 6 pwm			
				InitAdcOffset();
				
				tGlobal.LedStatus = 0;			
			
				tGlobal.RunTime = 0;
				
				if (tGlobal.ErrorCode == 0)
                {
                    tGlobal.OffsetReq = 1;
                }
				
				break;
			case STATE_OFFSET:
				
				if (tGlobal.OffsetReq)
				{	
					CalAdcOffset();
				}	
				else
				{
					GetCurrentOffset();
					tGlobal.CoreIndex = STATE_BSTART;
					
					tGlobal.RunTime = 0;
					tCore.Tick1s = 25000;
				}	
				
				break;
			case STATE_BSTART:		//Boost			
				
				Open3LowPwm();		//open 3 low pwm 
				
				tCore.Tick = 10000;			//10000 x 40 = 400 ms
				tGlobal.CoreIndex = STATE_BWAIT;
				break;
			
			case STATE_BWAIT:
				if (tCore.Tick == 0)
				{					
					Close6Pwm();				//close 6 pwm
					tGlobal.CoreIndex = STATE_OSTART;			
				}
				
				break;
				
			case STATE_OSTART:		//Orient
                
				Open6WorkPwm();	
                
//                Percent = 9500;
//                qAngle = 0;
//                qAngleDelta = 0;
//				tGlobal.CoreIndex = STATE_TEST;
                
				tUm.Percent = ORIENT_V_PERCENT;	
				tUm.qEAngle = 0;					
				UsOut(tUm.Percent,tUm.qEAngle);			
                
				tCore.Tick = ORIENT_TIME;			
				tGlobal.CoreIndex = STATE_OWAIT;
				break;
			
			case STATE_OWAIT:
				if (tCore.Tick == 0)
				{						
					tIm.qIqGiven = START_IQ;			
					tIm.qIdGiven = 0;
                    
					tCore.StartSwitchNum = 0;
					tCore.StartAcceleration32.U32 = 0;
					tCore.StartOmega32.U32 = 0x00010000;		//0x00100000			
					
					VoltageInitialize();
					CurrentInitialize();			
					PllInitialize();
					tIm.qParkAngle = -EANGLE90;		
					tGlobal.CoreIndex = STATE_FORCE;
                    tCore.RippleCompEnable = 0;
				}	

				break;
			
			case STATE_FORCE:		//Force
				
				RotorAnglePLL();
                
				if (tCore.StartAcceleration32.Words.High < K_START_ACC_END)	
					tCore.StartAcceleration32.U32 += K_STARTACCELERATION;
				else
					tCore.StartAcceleration32.Words.High = K_START_ACC_END;  
				
				tCore.StartOmega32.U32 += tCore.StartAcceleration32.U32 >> 4;	//16
				
				if(tCore.StartOmega32.Words.High >= 874)		//20000 * 0.00004 * 65536 / 60 = 874
				{	
					tCore.StartOmega32.Words.High = 874;
				}
				
				tIm.qParkAngle += tCore.StartOmega32.Words.High;				
                
				tCore.qStartThetaDelta = tRm.qAngle - tIm.qParkAngle;			
				
				GetUs();
				tUm.Percent = tUm.PercentOut;
				tUm.qEAngle = tIm.qParkAngle + tUm.qUsdAngle;				
				UsOut(tUm.Percent,tUm.qEAngle);
				
				if ((tIm.qParkAngle > EANGLE60) && (tCore.StartSwitchNum == 0))
				{					
					tCore.StartSwitchNum = 1;
				}
                
				if ((tCore.StartSwitchNum != 0) && (tCore.StartOmega32.Words.High >= 874))		//20000RPM
				{								
					if (tCore.qStartThetaDelta > 0)
					{
						tCore.StartSwitchNum ++;
						if (tCore.StartSwitchNum > 3)  		
						{									
							tGlobal.CoreIndex = STATE_RUN;
							tGlobal.LedStatus = 1;		
						}	
					}
					else
					{
						tCore.StartSwitchNum = 1;						
					}		
				}	
				
				ParkAngleSinCos();
				
				break;		

			case STATE_RUN:
				RotorAnglePLL();
				
				GetUs();  				
				tUm.Percent = tUm.PercentOut;		
				tUm.qEAngle = tIm.qParkAngle + tUm.qUsdAngle;
				UsOut(tUm.Percent,tUm.qEAngle);			
                
				tIm.qParkAngle = tRm.qAngle - tCore.qStartThetaDelta;					
                
				if (tCore.qStartThetaDelta < 0)						
				{
					tCore.qStartThetaDelta ++;						
				}
				else if (tCore.qStartThetaDelta > 0)	
				{
					tCore.qStartThetaDelta --;
				}
				else
				{
					tCore.RippleCompEnable = 1;	
                    	
                    if (tCore.Tick1s == 0)
                    {
                        tCore.Tick1s = 25000;
                        
                        if (tGlobal.RunTime < 0xffffffff)
                            tGlobal.RunTime ++;
                        
                    } 
                    else
                    {
                        tCore.Tick1s --;
                    }
                    
                    if (tIm.qIqGiven < tGlobal.qSetIq)			
                    {													
                        tIm.qIqGiven ++;
                    }							
                    else if (tIm.qIqGiven > tGlobal.qSetIq)	
                    {
                        tIm.qIqGiven --; 
                    }	
                    
					tGlobal.LedStatus = 2;
				}						
				
				ParkAngleSinCos();
				
				break;
			case STATE_TEST:
                if(MTick++ > 4)
                {
                    MTick = 0;
                    if(Percent < 16000)
                        Percent ++;
                }
                
                if(ATick++ > 40)
                {
                    ATick = 0;
                    if(qAngleDelta <= 1179)
                        qAngleDelta ++;
                }
                qAngle += qAngleDelta;
                UsOut(Percent,qAngle);
                break;
			default:
				tGlobal.CoreIndex = STATE_STOP;
				break;
		}			
	}
	
	
//DAC看波形
	
//	DAC->DHR12R1 = (0x8000 + tIm.qParkAngle) / 16;	
	
//	DAC->DHR12R1 = (0x8000 + tUm.qEAngle) / 16;		
	
//	DAC->DHR12R1 = (0x8000 + tUm.qUq) / 16;	
	
//	DAC->DHR12R1 = (0x8000 + tIm.qIa) / 16;		
	
//	DAC->DHR12R1 = tUm.CCR1;
	
//	DAC->DHR12R1 = (0x8000 + tCore.qStartThetaDelta) / 16;	
	
//	DAC->DHR12R1 = (0x8000 + tRm.qAngle) / 16;		
	
//	DAC->DHR12R1 = (0x8000 + tEm.qEd) / 16;		
	
	DAC->DHR12R1 = (0x8000 + tIm.qId) / 16;	
}
/*===============================================================================================*/
static void ParkAngleSinCos(void)
{
	UNION_U32 Temp32;
	
	Temp32.U32 = CalSinCos(0x7fff,tIm.qParkAngle);
	tIm.qParkCos = (signed short int)Temp32.Words.Low;
	tIm.qParkSin = (signed short int)Temp32.Words.High;
}	
/*===============================================================================================*/
static void Close6Pwm(void)
{
	TIM8->CCMR1 = 0x00004848;		
	TIM8->CCMR2 = 0x00006848;		
	TIM8->CCER = 0x00001ddd;		
	//CC1E=1(OC1 Enable),		CC1P=0(OC1 active high),	CC1NE=1(CC1N Enable),	CC1NP=1(tim_oc1n active low)
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
	//CC1E=0(OC1 Disable),		CC1P=0(OC1 active high),	CC1NE=1(CC1N Enable),	CC1NP=0(tim_oc1n active high)
}
/*===============================================================================================*/
static void Open6WorkPwm(void)
{
	TIM8->CCR1 = 200;
	TIM8->CCR2 = 200;
	TIM8->CCR3 = 200;

	TIM8->CCMR1 = 0x00006868;		
	TIM8->CCMR2 = 0x00006868;		
	TIM8->CCER = 0x00001555;		
	//CC1E=1(OC1 Disable),		CC1P=0(OC1 active high),	CC1NE=1(CC1N Enable),	CC1NP=0(tim_oc1n active high)
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
