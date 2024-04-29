/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
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
typedef struct
{
	unsigned short int Tick;
	unsigned short int Index;
	unsigned short int StartSwitchNum;
	unsigned short int RippleCompEnable;
	
	UNION_U32 StartAcceleration32;
	UNION_U32 StartOmega32;
	
	signed short int qStartThetaDelta;
	signed short int qSetIq;
	
	unsigned int Tick1s;
    unsigned short int FaultNum;
} tCore_TypeDef;
/*===========================================================================*/
typedef struct
{		
	unsigned short int IaValue;
	unsigned short int IbValue;	
    
	signed short int qIa;
	signed short int qIb;
	signed short int qIc;
    
	signed short int qIalpha;
	signed short int qIalphaLast;
	signed short int qIbeta;
	signed short int qIbetaLast;
    
	signed short int qId;
	signed short int qIq;
    
	signed short int qIoffsetA;
	signed short int qIoffsetB;	
    
	signed short int qIdGiven;
    signed short int qIqGiven;
    
	signed short int qParkAngle;
	signed short int qParkCos;
	signed short int qParkSin;
} tIm_TypeDef;
/*===========================================================================*/
typedef struct
{
	signed short int qUalpha;
	signed short int qUbeta;
    
	signed short int qUd;
	signed short int qUq;
    
	signed short int qUx;
	signed short int qUy;
	signed short int qUz;
	
	signed short int qUs;
    signed short int qUsMax;
    
	signed short int qCos;
	signed short int qSin;
	unsigned short int Sector;
	
	unsigned short int PercentMax;
	unsigned short int Percent;
	unsigned short int PercentOut;
	
	unsigned short int Taout;
	unsigned short int Tbout;
	unsigned short int Tcout;	
    
	unsigned short int CCR1;
	unsigned short int CCR2;
	unsigned short int CCR3;
	
    signed short int qEAngle;	
	signed short int qUsdAngle;
} tUm_TypeDef;
/*===========================================================================*/
typedef struct
{
	signed short int qAngle;
	signed short int qAngleLast;
	signed short int qAngleDalta;
	
} tRm_TypeDef;
/*===========================================================================*/
typedef struct
{
	signed short int qEalpha;
	signed short int qEbeta;
	signed short int qKr;
	signed short int qKl;
	
	signed short int qEd;	
} tEm_TypeDef;
/*===========================================================================*/
typedef struct
{
    signed short int sErr;
    signed short int sLimit;
    UNION_S32 qSumErr32;	
	
    unsigned short int Kp;
    unsigned short int Ki;	
    signed short int sOut;		
}tPI_Type;
/*===========================================================================*/
typedef struct
{
	unsigned short int LedStatus;
	unsigned short int CoreIndex;
	unsigned short int IaValue;
	unsigned short int IbValue;
	unsigned short int IaOffset;
	unsigned short int IbOffset;
    
	unsigned short int VbusAverage;
	unsigned short int VbusInstant;	
    unsigned short int TargetVbus;
    
	unsigned short int OffsetReq;
	signed short int qSetIq;	
	
	unsigned short int MotorStatus;
	unsigned short int ErrorCode;
	
	unsigned short int HTAverage;
	unsigned short int NTCAverage;
	
	unsigned short int V12Average;
	unsigned short int OPAMP3Instant;
	
	unsigned int RunTime;
} tGlobal_TypeDef;
/******************* (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi ****************/
