/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    UserParams.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#define    	CARRIER_FREQUENCY   25000 		//PWM载波频率
#define    	PWM_PERIOD_VALUE    (160000000 / CARRIER_FREQUENCY)			//6400
#define    	DEAD_TIME    		(160000000 / CARRIER_FREQUENCY / 25)  	//DT/1.6 = 6400 / 40	DT = 256

#define		US_MAX_PERCENT		62259
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
