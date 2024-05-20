/**************************************************************************************************
* 张飞实战电子FOC高阶课程
* @project Framework
* @file    Define.h
* @author  张飞实战电子团队
* @date    2024/3/12
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#define  	DisIE				__asm("CPSID I")
#define  	EnIE				__asm("CPSIE I")

/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;
	unsigned short int Delay;

} System_TypeDef;
/*===========================================================================*/
typedef struct
{
    unsigned short int ValueInstant;
    unsigned short int ValueAverage;
    unsigned int ValueSum32;
	
    unsigned short int ValueNum;		
    unsigned short int ValueFilter;	
}tAnx_Type;

typedef struct
{
    tAnx_Type An11,An12,An13,An14,An21,An22,An23,An24;
}tAdc_Type;

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
