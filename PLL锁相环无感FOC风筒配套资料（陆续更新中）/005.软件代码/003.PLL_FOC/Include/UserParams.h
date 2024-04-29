/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    UserParams.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#define    	CARRIER_FREQUENCY   25000 		
#define    	PWM_PERIOD_VALUE    (160000000 / CARRIER_FREQUENCY)			
#define    	DEAD_TIME    		(160000000 / CARRIER_FREQUENCY / 25)  	

#define		ORIENT_TIME			12500  //500ms
#define 	ORIENT_V_PERCENT	3276  //5%

#define     START_IQ            8192	//0.25	

#define		PLL_KR				2517		
#define		PLL_KL				5789		
#define		PLL_KP				256			
#define		PLL_KI				3
#define		PLL_LIMIT			8192		

#define	   	I_KP				4096		
#define	   	I_KI				128			
#define		I_LIMIT				27582		

#define		DELTAU_MAX			3276		
#define		US_MAX_PERCENT		62259		
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
