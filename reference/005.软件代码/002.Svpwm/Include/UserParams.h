/**************************************************************************************************
* �ŷ�ʵս����
* @project Svpwm
* @file    UserParams.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#define    	CARRIER_FREQUENCY   25000 		//PWM�ز�Ƶ��
#define    	PWM_PERIOD_VALUE    (160000000 / CARRIER_FREQUENCY)			//6400
#define    	DEAD_TIME    		(160000000 / CARRIER_FREQUENCY / 25)  	//DT/1.6 = 6400 / 40	DT = 256

#define		US_MAX_PERCENT		62259
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
