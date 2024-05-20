/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    Define.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#define  	DisIE				__asm("CPSID I")
#define  	EnIE				__asm("CPSIE I")

#define     TEST_LED_ON      	GPIOC->ODR |= 0x00008000		//PC15
#define     TEST_LED_OFF       	GPIOC->BSRR = 0x80000000
/*===========================================================================*/
typedef union
{
    signed int S32;
    struct
    {
        signed short int Low;
        signed short int High;
    }Words;
}UNION_S32;
/*===========================================================================*/
typedef union
{
    unsigned int U32;
    struct
    {
        unsigned short int Low;
        unsigned short int High;
    }Words;
}UNION_U32;
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
    unsigned short int Index;
    unsigned short int IoffsetA;
    unsigned short int IoffsetB;
    unsigned short int IoffsetC;
}tAdc_Type;
/*===========================================================================*/
typedef struct
{
	unsigned short int CoreIndex;

} tGlobal_TypeDef;
/******************* (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi ****************/
