/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Main.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Main.h"

/**************************************************************************************************
* 初始化及主循环
**************************************************************************************************/
int Main(void)
{   
	Initialize();
    
	tSystem.Delay = 100;	
	while(tSystem.Delay);
    
	while(1)
    {
        SwitchApp();
		KeyApp();
		HeatApp();
		LedApp();
		MotorApp();		
		ProtectApp();
    }
}
/*===============================================================================================*/
//TIM8_TRGO2 trigger
void ADC1_2_IRQHandler(void)
{
    unsigned int Temp;
    
    Temp = ADC1->ISR;
    
    if((Temp & 0x00000040) != 0)
    {
        ADC1->ISR |= 0x00000040;
//        GPIOC -> ODR |= 0x2000;//验证ADC触发点
        
        AdcSample();
		CoreMachine();	
		AdcFilter();		   
		ScanfHeatTrigger();	
		SysTimeCount();
        
//        GPIOC -> ODR &= 0xdfff;//验证ADC触发点
    }
}
/*===============================================================================================*/
//call SysTimeCount every 40us 
static void SysTimeCount(void)
{
	tSystem.Tick ++;
	if (tSystem.Tick >= 25)
	{
		tSystem.Tick = 0;
		
		if (tSwitch.Tick)
			tSwitch.Tick --;
		
		if (tKey.Tick)
			tKey.Tick --;
				
		if (tSystem.Delay)
			tSystem.Delay --;
		
		if (tLed.Tick)
			tLed.Tick --;
		
		if (tProtect.Tick)
			tProtect.Tick --;
	}	
	
	if (tHeat.Tick)
		tHeat.Tick --;
}	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
