/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Initialize.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Initialize.h"
/**********************************************
* 外设及应用程序初始化
**********************************************/
void Initialize(void)
{
    SysClockInit();
    GpioInit();
	DacInit();	
	OpAmpInit();	
	CompInit();
    PwmInit();		
    AdcInit();    
	CORDICInit();
    Timer1Init();	
    NvicInit();	
	
	LedInitialize();
	KeyInitialize();
	SwitchInitialize();
	MotorInitialize();
	HeatInitialize();
	ProtectInitialize();
}
/**********************************************
* 系统时钟配置
**********************************************/
static void SysClockInit(void)
{          
    //Enable Prefetch Buffer
    FLASH -> ACR |= 0x00000100;
    //Flash 8 wait state 7 cpu cycle
    FLASH -> ACR |= 0x00000008;
    
    //PLL config	PLLSRC = HSI16, PLLM = 2,PLLN = 40
    //f(VCO_clock<170MHz) = 16MHz x (40/2) = 320MHz
    //f(PLL_R) = 320MHz /2 = 160MHz		for system clock
    //f(PLL_Q) = 320MHz /2 = 160MHz		disable
    //f(PLL_P) = 320MHz /6 = 53.333MHz		for ADC
    RCC -> PLLCFGR &= 0x008c800c;
    RCC -> PLLCFGR |= 0x31012812; //M = 2 N = 40 R = 2 PLLRCLK = 160MHZ		HSI16
    
    RCC -> CR |= 0x01000000;	//PLLON
    //等待PLL锁定完成			PLLRDY
    while((RCC->CR & 0x02000000) == 0)
    {
    }
    
    //PLL selected as system clock
    RCC -> CFGR &= 0xfffffffc;	
    RCC -> CFGR |= 0x00000003;	
    
    //wait PLL used as system clock
    while ((RCC -> CFGR & 0x0000000c) != 0x0c)	
    {
    }
}
/**********************************************
* 数字IO口配置
* PA8 -- TIM1_CH1 trigger SCR		output
* PA9 -- TIM1_CH2 rece zero and speed set		input
* PA10 -- TIM1_CH3 rece zero and speed set	input
*
* PC13 --> LED
* PC14 --> RL1
* PC15 --> RL2
*
* PF0 input
**********************************************/
static void GpioInit(void)
{
	RCC->AHB2ENR |= 0x00000001; //GPIOAEN = 1    
    GPIOA->MODER &= 0xffc0ffff;	//PA9(AF6) PA10 input
    GPIOA->MODER |= 0x00090000; //PA8 output   
	GPIOA->AFR[1] |= 0x00000060;//PA9 = AF6 = TIM1_CH2
	
    RCC->AHB2ENR |= 0x00000004; //GPIOCEN = 1    
    GPIOC->MODER &= 0x03ffffff;	//output
    GPIOC->MODER |= 0x54000000;    
	
	RCC->AHB2ENR |= 0x00000020; //GPIOFEN = 1    
    GPIOF->MODER &= 0xfffffffc;	//input
}
/**********************************************
* PWM配置
* PA15 --> TIM8CH1
* PB3  --> TIM8CH1N
* PB4  --> TIM8CH2N
* PB5  --> TIM8CH3N
* PB6  --> TIM8BKIN2H
* PB7  --> TIM8BKINH
* PB8  --> TIM8CH2
* PB9  --> TIM8CH3
**********************************************/
static void PwmInit(void)
{
    RCC->AHB2ENR |= 0x00000001; 	//GPIOAEN = 1
    RCC->AHB2ENR |= 0x00000002; 	//GPIOBEN = 1
    RCC->APB2ENR |= 0x00002000; 	//TIM8EN = 1
    
    GPIOA->MODER &= 0x3fffffff;		//Alternate function mode
    GPIOA->MODER |= 0x80000000;
    GPIOA->OTYPER &= 0xffff7fff;	//Output push-pull
    GPIOA->OSPEEDR &= 0x3fffffff;	//Very high speed
    GPIOA->OSPEEDR |= 0xc0000000;
    GPIOA->PUPDR &= 0x3fffffff;		//No pull-up, pull-down
    GPIOA->AFR[1] |= 0x20000000;	//PA15 = AF2 = TIM8_CH1
    
	//PB0-PB2	 PB10-PB15 Analog mode		
    GPIOB->MODER &= 0xfff0003f;		//PB3-PB9
    GPIOB->MODER |= 0x000aaa80;		//Alternate function mode
    GPIOB->OTYPER &= 0xfffffc07;	//Output push-pull
    GPIOB->OSPEEDR &= 0xfff0003f;	//Very high speed
    GPIOB->OSPEEDR |= 0x000fffc0;
    GPIOB->PUPDR &= 0xfffc003f;		//No pull-up, pull-down   
    GPIOB->AFR[0] |= 0x5a344000; 	//PB7=AF5=TIM8BKINH PB6=AF10=TIM8BKIN2H  PB5=AF3=TIM8CH3N  PB4=AF4=TIM8CH2N 	PB3=AF4=TIM8CH1N
    GPIOB->AFR[1] |= 0x000000aa; 	//PB8=AF10=TIM8_CH2		PB9=AF10=TIM8_CH3
    
    TIM8->CNT = 0;
    TIM8->PSC = 0;					//无预分频
    TIM8->ARR = (PWM_PERIOD_VALUE >> 1) - 1; 				//PWM频率为25KHz  160MHz/25KHz = 6400 中心对齐 重载值设定为3200
    
    TIM8->CR1 |= 0x00a0; 			//使能中心对齐模式
    TIM8->CR1 |= 0x0100; 			//tdts = 2*Ttim_ker_ck
    TIM8->CR2 |= 0x00700000; 		//TIM_TRGO2 OC4REF
	
    TIM8->CCMR1 = 0x00004848;		//CC1S=0(CC1 channel output),	OC1FE=0(output compare 1 fast disable),	OC1PE=1(output compare 1 preload enable)
									//OC1M = Force inactive level
    TIM8->CCMR2 |= 0x00006848; 		//CCR4 PWM2模式	
    TIM8->CCER |= 0x00001DDD; 		//所有通道输出低电平	CC1E=1(OC1 Enable),		CC1P=0(OC1 active high),		
									//						CC1NE=1(CC1N Enable),	CC1NP=0(tim_oc1n active high),	
//    TIM8->CCMR1 = 0x00006868;
//    TIM8->CCMR2 |= 0x00006868;
//    TIM8->CCER |= 0x00001555;  //用于测试PWM配置是否正常
    
    TIM8->CCR1 = 1000;
    TIM8->CCR2 = 1000;
	TIM8->CCR3 = 1000;
    TIM8->CCR4 = (PWM_PERIOD_VALUE >> 1) - 2;
    
	TIM8->BDTR = 0;
    TIM8->BDTR |= 0x000e0880; 		//filter 2.4us	OSSR=1	死区 (64 + 0) x 2 x 1/80 = 1.6us
	
    TIM8->AF1 = 0x00000010; 		//BKCMP4E
    TIM8->AF2 = 0x00000000; 		//BKIN2 disable
	TIM8->BDTR |= 0x10008000;		//MOE=1
	
	delay(5000); 
	
	TIM8->SR &= 0xffffff7f; 		
	TIM8->BDTR |= 0x00001000;		//BKE=1
    TIM8->CR1 |= 0x0001;			//使能定时器1	
}
/**********************************************
* COMP配置
* COMP4
* PB0 - COMP4_INP
*
**********************************************/
static void CompInit(void)
{
	RCC ->APB2ENR |= 0x00000001;//SYSCFGEN = 1	
	COMP4 -> CSR = 0x00178041; 	//EN=1,INMSEL=4(DAC3_CH2),INPSEL=0(PB0),	POL=0(not-inverted)
								//HYST=7(70mV),BLANKSEL=2(TIM8_OC5),BRGEN=0,SCALEN=0,VALUE=0,LOCK=0
}	
/**********************************************
* OPAMP配置
* OPAMP1
* PA1 OP1_VINP	(VINP0)
* PA2 OP1_VOUT	(ADC1_IN3)
* PA3 OP1_VINM	(VINM0)
*
* OPAMP2
* PA5 OP2_VINM	(VINM0)
* PA6 OP2_VOUT	(ADC1_IN12)
* PA7 OP2_VINP	(VINP0)
*
* OPAMP3
* PB13 OP3_VINP	(VINP1)
*
**********************************************/
static void OpAmpInit(void)
{
	RCC ->APB2ENR |= 0x00000001;//SYSCFGEN = 1
	
	//Analog mode
	GPIOA -> MODER |= 0x0000fcfc;	//PA1 PA2 PA3	PA5 PA6 PA7
	GPIOB -> MODER |= 0x3fc0003f;	//PB0 PB1 PB2 	PB11 PB12 PB13 PB14
	
	//OPAEN = 1	OP enable	OPAHSM = 1 high-speed mode	
	//VP_SEL = 0, VM_SEL = 0
	OPAMP1->CSR = 0x00000081;	
	OPAMP2->CSR = 0x00000081;
	
	//OPAINTOEN = 1  internal output enable
	OPAMP3->CSR = 0x000000c5;	//VP_SEL=1,VM=2,PGA-GAIN = 2
}
/**********************************************
* ADC配置
* PA0 --> Vbus  	ADC12_IN1
* PA2 --> Ia		ADC1_IN3
* PA6 --> Ib		ADC2_IN3
* PB2 --> V15	    ADC2_IN12
* PB11 --> bak  	ADC12_IN14
* PB12 --> NTC	  	ADC1_IN11
* PB14 --> HT     	ADC1_IN5
* 分布 ADC1  Ia ADC1_IN3  	Vbus ADC12_IN1	HT ADC1_IN5  		NTC    ADC1_IN11    
* 分布 ADC2  Ib ADC2_IN3	V12 ADC2_IN12   bak ADC12_IN14 	    OPAMP3 ADC2_IN18 
* ADC clock 40MHz
**********************************************/
static void AdcInit(void)
{
    unsigned int Temp;
	
    RCC->AHB2ENR |= 0x00002000; //ADC12EN
    RCC->CCIPR &= 0xcfffffff;
    RCC->CCIPR |= 0x10000000; //ADC CLOCK PLLP 
    
    //校准ADC
    ADC1 -> CR &= 0xdfffffff; //DEEPPWD = 0，解除掉电模式
    ADC1 -> CR |= 0x10000000; //ADC voltage regulator enable
    //等待稳压器正常，时间需要20us
    delay(5000);
    ADC2 -> CR &= 0xdfffffff; //DEEPPWD = 0，解除掉电模式
    ADC2 -> CR |= 0x10000000; //ADC voltage regulator enable
    //等待稳压器正常，时间需要20us
    delay(5000); 
    ADC1 -> CR |= 0x80000000; //enable calibration
    //等待校准完成
    do
    {
        Temp = ADC1 -> CR;
        Temp &= 0x80000000;
    }while(Temp != 0);
    
    ADC2 -> CR |= 0x80000000; //enable calibration
    //等待校准完成
    do
    {
        Temp = ADC2 -> CR;
        Temp &= 0x80000000;
    }while(Temp != 0);
    
    //ADC模块公共寄存器配置
    ADC12_COMMON -> CCR |= 0x00000005;//Injected simultaneous mode only
    		
    //ADC1配置	
    ADC1->CFGR = 0x00000000; 	//Injected Queue enable
	//采样时间
    ADC1->SMPR1 = 0x12492492;  //12.5 + 12.5 = 25 ADC Clock cycles * （1/53.333MHz） =  468.75ns
    ADC1->SMPR2 = 0x02492492;
	
	//Injected sequence	
	//4 conversions		JEXTSEL[4:0]=9 tim8_trgo
	//JSQ1=IN3(Ia) 	JSQ2=IN1(Vbus) 	JSQ3=IN5(HT) 	JSQ4=IN11(NTC) 
	ADC1->JSQR = 0x58a086ab; //TIM8_TRGO2 TRIGGER rising
		
	//interrupt
    ADC1->ISR |= 0x00000001; //清除ADRDY位
    ADC1->CR |= 0x00000001;//使能ADC1
    //等待ADC准备好
    do
    {
        Temp = ADC1 -> ISR;
        Temp &= 0x00000001;
    }while(Temp == 0);
    ADC1 -> ISR |= 0x00000001;//清除ADRDY位
    
    //ADC2配置
    ADC2->CFGR = 0x00000000; 	//Injected Queue enable
    ADC2->SMPR1 = 0x12492492;  //12.5 + 12.5 = 25 ADC Clock cycles * （1/53.333MHz） =  468.75ns
    ADC2->SMPR2 = 0x02492492;
	
	//4 conversions		JEXTSEL[4:0]=9 tim8_trgo 
	//JSQ1=IN3(Ib) 	JSQ2=IN12(V15) 	JSQ3=IN14(VTS-B) 	JSQ4=IN18(OPAMP3)
    ADC2->JSQR = 0x91c606ab; //TIM8_TRGO2 TRIGGER rising
    ADC2->CR |= 0x00000001;//使能ADC2
    
    do
    {
        Temp = ADC2 -> ISR;
        Temp &= 0x00000001;
    }while(Temp == 0);
    ADC2 -> ISR |= 0x00000001;//清除ADRDY位
    
	//interrupt enable
    ADC1->IER |= 0x00000040; //End of injected sequence of conversions interrupt enable
    
	//ADC start of injected conversion
    ADC1->CR |= 0x00000008;
    ADC2->CR |= 0x00000008;// ADC start of injected conversion
}
/**********************************************
* DAC配置
* PA4 --> DACOUT1H
**********************************************/
static void DacInit(void)
{
    RCC->AHB2ENR |= 0x00050000; //DAC1EN DAC3EN = 1
    
	//High frequency interface mode selection
    DAC1->MCR = 0x00008000; //HFSEL[1:0] = 0b10	
    DAC1->CR |= 0x00000001; //EN1 = 1    
	
	//High frequency interface mode selection
    DAC3->MCR = 0x00008000; //HFSEL[1:0] = 0b10	
    DAC3->CR |= 0x00010000; //EN2 = 1    
    DAC3->DHR12R2 = 1490; //Value	1.2 x 4096 /3.3 = 1490
	//1.2 / 2 / 0.2 = 3A	
}
/**********************************************
* CORDIC配置
**********************************************/
static void CORDICInit(void)
{
	RCC -> AHB1ENR |= 0x00000008;
}	
///**********************************************
//* 定时器1配置
//**********************************************/
static void Timer1Init(void)
{
    RCC->APB2ENR |= 0x00000800; //TIM1EN = 1
    
    TIM1->CNT = 0;
    TIM1->PSC = 39;		//40/160M = 250ns	x 65536 = 16.384ms
    TIM1->ARR = 0xffff; 
    TIM1->RCR = 0;
    TIM1->CR1 |= 0x0180;//上升计数
    
	TIM1 -> CCMR1 = 0xf100;
	TIM1 -> CCER = 0x00b0;	//CC2NP = CC2P = CC2E = 1

    TIM1->CR1 |= 0x0001; //使能定时器1计数
}
/**********************************************
* NVIC中断配置
* ADC1_2_IRQHandler	IRQ = 18
**********************************************/
static void NvicInit(void)
{
    NVIC-> ISER[0] |= 0x00040000; 	//IRQ = 18 ADC中断   
    NVIC -> IP[18] = 0x00; 			//优先级最高
}
/**********************************************
* 简单延时函数
**********************************************/
static void delay(unsigned int time)
{
    while(time--);
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
