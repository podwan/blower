/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Protect.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Protect.h"
/**************************************************************************************************
**************************************************************************************************/
void ProtectInitialize(void)
{
	tProtect.CountVbus = 100;
    tProtect.CountHt = 100;
    tProtect.CountNtc = 100;
    tProtect.Count12V = 100;
    tSystem.FlashWriteOk = 0;
}
/*===============================================================================================*/
//input: 	tGlobal.VbusAverage		tGlobal.HTAverage	tGlobal.NTCAverage		tGlobal.V12Average
//output:	tGlobal.ErrorCode
/*===============================================================================================*/
void ProtectApp(void)
{
    unsigned short int ErrorCode;
    
    DisIE;
    ErrorCode = tGlobal.ErrorCode;
    EnIE;
    
	if (tProtect.Tick == 0)
	{
		tProtect.Tick = 1;
        
        if(tProtect.CountVbus)
            tProtect.CountVbus --;
        
        if(tProtect.CountHt)
            tProtect.CountHt --;
        
        if(tProtect.CountNtc)
            tProtect.CountNtc --;
        
        if(tProtect.Count12V)
            tProtect.Count12V --;
		
		if ((tGlobal.VbusAverage > VBUS380V) || (tGlobal.VbusAverage < VBUS200V))
		{
			if (tProtect.CountVbus == 0)
			{
				if ((ErrorCode == 0) || (ErrorCode >= 1))
                {
					ErrorCode = 2;
                    if(tSystem.FlashWriteOk == 0)
                    {
                        tSystem.FlashWriteOk = 1;
                        DisIE;
                        PageErase();
                        FLASH_write(0x0801F800,(unsigned long long)tSystem.KeyValue);
                        EnIE;
                    }
                }
			}
		}
		else
		{
            if(ErrorCode == 2)
            {
                if(tGlobal.VbusAverage > VBUS280V)
                {
                    SCB->AIRCR = 0x05fa0004;
                }
            }
			tProtect.CountVbus = 100;
		}
		
		if (tGlobal.HTAverage > HT80C) 
		{
			if (tProtect.CountHt == 0)
			{
				if ((ErrorCode == 0) || (ErrorCode > 2))
					ErrorCode = 3;
			}	
		}
		else
		{
			tProtect.CountHt = 100;
		}
		
		if (tGlobal.NTCAverage < NTC80C) 
		{
			if (tProtect.CountNtc == 0)
			{
				if ((ErrorCode == 0) || (ErrorCode > 3))
					ErrorCode = 4;
			}	
		}
		else
		{
			tProtect.CountNtc = 100;
		}	
		
		if ((tGlobal.V12Average < V12L10V) || (tGlobal.V12Average > V12H16V))
		{
			if (tProtect.Count12V == 0)
			{
				if ((ErrorCode == 0) || (ErrorCode > 4))
					ErrorCode = 5;
			}	
		}
		else
		{
			tProtect.Count12V = 100;
		}	
	}
    DisIE;
    tGlobal.ErrorCode = ErrorCode;
    EnIE;
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
