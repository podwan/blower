/**************************************************************************************************
* �ŷ�ʵս����
* @project PLL_FOC
* @file    Main.c
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\Main.h"

/**************************************************************************************************
* ��ʼ������ѭ��
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
//        GPIOC -> ODR |= 0x2000;//��֤ADC������
        
        AdcSample();
		CoreMachine();	
		AdcFilter();		   
		ScanfHeatTrigger();	
		SysTimeCount();
        
//        GPIOC -> ODR &= 0xdfff;//��֤ADC������
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
