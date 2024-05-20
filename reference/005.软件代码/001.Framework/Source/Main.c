/**************************************************************************************************
* 张飞实战电子FOC高阶课程
* @project Framework
* @file    Main.c
* @author  张飞实战电子团队
* @date    2024/3/12
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
