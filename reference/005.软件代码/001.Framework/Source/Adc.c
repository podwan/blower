/**************************************************************************************************
* �ŷ�ʵս����FOC�߽׿γ�
* @project Framework
* @file    Adc.c
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/3/12
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\Adc.h"
/*===============================================================================================*/
void AdcSample(void)
{  
	tAdc.An11.ValueInstant = (unsigned short int)ADC1->JDR1; //Ia
    tAdc.An12.ValueInstant = (unsigned short int)ADC1->JDR2; //Vbus
    tAdc.An13.ValueInstant = (unsigned short int)ADC1->JDR3; //HT
    tAdc.An14.ValueInstant = (unsigned short int)ADC1->JDR4; //NTC
    
    tAdc.An21.ValueInstant = (unsigned short int)ADC2->JDR1; //Ib
    tAdc.An22.ValueInstant = (unsigned short int)ADC2->JDR2; //V12
    tAdc.An23.ValueInstant = (unsigned short int)ADC2->JDR3; //VTS-B
    tAdc.An24.ValueInstant = (unsigned short int)ADC2->JDR4; //OPAMP3
	
}

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
