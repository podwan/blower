/**************************************************************************************************
* 张飞实战电子
* @project Svpwm
* @file    CoreDef.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#define     TEST_LED_ON      	GPIOC->ODR |= 0x00008000		//PC13
#define     TEST_LED_OFF       	GPIOC->BSRR = 0x80000000
/*===========================================================================*/
#define     EANGLE0     0
#define     EANGLE2  	364
#define     EANGLE5  	910
#define     EANGLE10  	1820
#define     EANGLE22P5  4096
#define     EANGLE30    5461
#define     EANGLE45    8192
#define     EANGLE60    10922
#define     EANGLE90    16384
#define     EANGLE120   21845
#define		EANGLE135	24576
#define     EANGLE150   27306
#define     EANGLE180   32768
#define     EANGLE210   38229
#define     EANGLE240   43690
#define     EANGLE270   49151
#define     EANGLE300   54613
#define     EANGLE330   60074
#define     EANGLE360   0
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
typedef union
{
    signed long long int S64;
    struct
    {
        signed int Low;
        signed int High;
    }S32;
}UNION_S64;
/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;
	
	unsigned int Tick1s;
    unsigned short int FaultNum;
} tCore_TypeDef;

/*===========================================================================*/
typedef struct
{
	signed short int qUx;
	signed short int qUy;
	signed short int qUz;
	
	signed short int qCos;
	signed short int qSin;
	unsigned short int Sector;
	
	unsigned short int PercentMax;
	unsigned short int Percent;
	
	signed short int qEAngle;
    
	unsigned short int Taout;
	unsigned short int Tbout;
	unsigned short int Tcout;	
	unsigned short int CCR1;
	unsigned short int CCR2;
	unsigned short int CCR3;
	
} tUm_TypeDef;

/*===========================================================================*/
typedef struct
{
	unsigned short int CoreIndex;

} tGlobal_TypeDef;
/******************* (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi ****************/
