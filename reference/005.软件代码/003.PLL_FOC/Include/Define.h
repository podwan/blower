/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
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
	unsigned short int FanSpeed;
	unsigned short int HeatGear;
	unsigned short int DebugMode;
	
	unsigned short int Delay;
	unsigned short int ErrCode;
    unsigned short int KeyValue;
    unsigned short int FlashWriteOk;
} System_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;
	unsigned short int CountVbus;
    unsigned short int CountHt;
    unsigned short int CountNtc;
    unsigned short int Count12V;
} Protect_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;	
	unsigned short int Count;	
} Led_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Speed;
	unsigned short int Tick;	
	unsigned short int Count;	
	unsigned short int RisingNum;	

	unsigned int HCount;
} Switch_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;
	unsigned short int Delay;
	unsigned short int Input;
	unsigned short int Index;
	
	unsigned short int Value;
} Key_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Speed;
	signed short int qSetIq;
} Motor_TypeDef;
/*===========================================================================*/
typedef struct
{
	unsigned short int Tick;
	unsigned short int Gear;
	unsigned short int ZCount;
	unsigned short int ZTick;	
} Heat_TypeDef;
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
}tAdc_Type;
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
