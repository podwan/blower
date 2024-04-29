/**************************************************************************************************
* �ŷ�ʵս����FOC�߽׿γ�
* @project Framework
* @file    Main.c
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/3/12
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
	
	tSystem.Delay = 500;	
	while(tSystem.Delay);
    
	while(1)
    {
        
    }
}
/*===============================================================================================*/
//TIM8_TRGO trigger
void ADC1_2_IRQHandler(void)
{
    unsigned int Temp;
    
    Temp = ADC1->ISR;
    
    if((Temp & 0x00000040) != 0)
    {
        ADC1->ISR |= 0x00000040;
        
        GPIOC->ODR |= 0x2000;
        
        AdcSample();  
            
		SysTimeCount();
        
        GPIOC->ODR &= 0xdfff;
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
		
		if (tSystem.Delay)
			tSystem.Delay --;
	}	
}	
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
