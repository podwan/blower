
#include "pwm.h"
#include "voltage.h"

void setPwm1(unsigned short int a, unsigned short int b, unsigned short int c)
{
    TIM8->CCR1 = a;
    TIM8->CCR2 = b;
    TIM8->CCR3 = c;
}
/*===============================================================================================*/
void Close6Pwm1(void)
{
    TIM8->CCMR1 = 0x00004848;
    TIM8->CCMR2 = 0x00006848;
    TIM8->CCER = 0x00001ddd;
}
/*===============================================================================================*/
void Open3LowPwm1(void)
{
    TIM8->CCR1 = 2000;
    TIM8->CCR2 = 2000;
    TIM8->CCR3 = 2000;

    TIM8->CCMR1 = 0x00006868;
    TIM8->CCMR2 = 0x00006868;
    TIM8->CCER = 0x00001444;
}
/*===============================================================================================*/
void Open6WorkPwm1(void)
{
    TIM8->CCMR1 = 0x00006868;
    TIM8->CCMR2 = 0x00006868;
    TIM8->CCER = 0x00001555;
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
