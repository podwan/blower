/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Voltage.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Voltage.h"
/**************************************************************************************************
* Svpwm
**************************************************************************************************/
void VoltageInitialize(void)
{
	tUm.PercentMax = US_MAX_PERCENT;			//60293
	
	tPiId.qSumErr32.S32 = 0;
	tPiIq.qSumErr32.S32 = 0;	
}
/*===============================================================================================*/
/*============================================================================*/
void UsOut(unsigned short int Percent,signed short int qUA)
{			
    GetUsSector(qUA);	
    GetUxyz(qUA);
    SvpwmOut(Percent);   
    GetUalphabeta();
}
/*============================================================================*/
static void GetUsSector(unsigned short int UAngle)
{
    if((UAngle > EANGLE0) && (UAngle < EANGLE60))
        tUm.Sector = 1;
    else if((UAngle >= EANGLE60) && (UAngle < EANGLE120))
        tUm.Sector = 2;
    else if((UAngle >= EANGLE120) && (UAngle < EANGLE180))
        tUm.Sector = 3;
    else if((UAngle >= EANGLE180) && (UAngle < EANGLE240))
        tUm.Sector = 4;
    else if((UAngle >= EANGLE240) && (UAngle < EANGLE300))
        tUm.Sector = 5;
    else   
        tUm.Sector = 6; 
}
/*============================================================================*/
//三相相位相差60度的正弦波Ux Uy Uz产生
// Ux = Sin（θ）
// Uy = Sin（θ + 60）
//    = 1/2 Sinθ + sqrt(3)/2 Cosθ
// Uz = Sin（θ - 60）
//    = 1/2 Sinθ - sqrt(3)/2 Cosθ
/*============================================================================*/
static void GetUxyz(signed short int qUA)
{	
	UNION_U32 Temp32;
	signed short int sTempA,sTempB;
	
	Temp32.U32 = CalSinCos(0x7fff,qUA);
	tUm.qCos = (signed short int)Temp32.Words.Low;
	tUm.qSin = (signed short int)Temp32.Words.High;	

	tUm.qUx = tUm.qSin;		

	sTempA = qUA + EANGLE60;
	Temp32.U32 = CalSinCos(0x7fff,sTempA);
	tUm.qUy = (signed short int)Temp32.Words.High;		
	
	sTempB = qUA - EANGLE60;
	Temp32.U32 = CalSinCos(0x7fff,sTempB);
	tUm.qUz = (signed short int)Temp32.Words.High; 
    
}
/*==============================================================================
 产生马鞍波调制波
==============================================================================*/
static void SvpwmOut(unsigned short int Percent)
{
    unsigned short int PDC1Temp;
    unsigned short int PDC2Temp;
    unsigned short int PDC3Temp;
    unsigned short int PDCMax;
    
    switch(tUm.Sector)
    {
        case 1:
            VectorActionTimeCalculate(Percent,-tUm.qUz,tUm.qUx);
            PDC1Temp = tUm.Taout;
            PDC2Temp = tUm.Tbout;
            PDC3Temp = tUm.Tcout;
            break;
        case 2:
            VectorActionTimeCalculate(Percent,tUm.qUz,tUm.qUy);
            PDC1Temp = tUm.Tbout;
            PDC2Temp = tUm.Taout;
            PDC3Temp = tUm.Tcout;
            break;
        case 3:
            VectorActionTimeCalculate(Percent,tUm.qUx,-tUm.qUy);
            PDC1Temp = tUm.Tcout;
            PDC2Temp = tUm.Taout;
            PDC3Temp = tUm.Tbout;
            break;
        case 4:
            VectorActionTimeCalculate(Percent,-tUm.qUx,tUm.qUz);
            PDC1Temp = tUm.Tcout;
            PDC2Temp = tUm.Tbout;
            PDC3Temp = tUm.Taout;
            break;
        case 5:
            VectorActionTimeCalculate(Percent,-tUm.qUy,-tUm.qUz);
            PDC1Temp = tUm.Tbout;
            PDC2Temp = tUm.Tcout;
            PDC3Temp = tUm.Taout;
            break;
        case 6:
            VectorActionTimeCalculate(Percent,tUm.qUy,-tUm.qUx);
            PDC1Temp = tUm.Taout;
            PDC2Temp = tUm.Tcout;
            PDC3Temp = tUm.Tbout;
            break;
        default:break;
    }
    
    //限制最小占空比
    if(PDC1Temp < DEAD_TIME)
        PDC1Temp = DEAD_TIME;
    if(PDC2Temp < DEAD_TIME)
        PDC2Temp = DEAD_TIME;
    if(PDC3Temp < DEAD_TIME)
        PDC3Temp = DEAD_TIME;
    //限制最大占空比
    PDCMax = (PWM_PERIOD_VALUE >> 1) - DEAD_TIME; 
    if(PDC1Temp > PDCMax)
        PDC1Temp = PDCMax;
    if(PDC2Temp > PDCMax)
        PDC2Temp = PDCMax;
    if(PDC3Temp > PDCMax)
        PDC3Temp = PDCMax;
    
    tUm.CCR1 = PDC1Temp;
    tUm.CCR2 = PDC2Temp;
    tUm.CCR3 = PDC3Temp;
	
    //最终占空比给定
    TIM8 -> CCR1 = PDC1Temp;
    TIM8 -> CCR2 = PDC2Temp;
    TIM8 -> CCR3 = PDC3Temp;
}
/*============================================================================*/
static void VectorActionTimeCalculate(unsigned short int Percent,signed short int Sa,signed short int Sb)
{
    UNION_U32 Temp32;
    UNION_U32 Temp32A,Temp32B;
    
    unsigned short int a,b;
    
    if(Sa<0)
        Sa = 0;
    if(Sb<0)
        Sb = 0;
    
    a = (unsigned short int)Sa;
    b = (unsigned short int)Sb;
    
    if(Percent > tUm.PercentMax)
        Percent = tUm.PercentMax;
    
	Temp32.U32 = (unsigned int)(Percent * PWM_PERIOD_VALUE); 
    Temp32A.U32 = (unsigned int)(Temp32.Words.High * a);			
    Temp32B.U32 = (unsigned int)(Temp32.Words.High * b);			
    
    tUm.Tcout = ((PWM_PERIOD_VALUE >> 1) - Temp32A.Words.High - Temp32B.Words.High) >> 1;
    tUm.Tbout = tUm.Tcout + Temp32B.Words.High;
    tUm.Taout = tUm.Tbout + Temp32A.Words.High;
}
/*==============================================================================
Ualpha Ubeta
==============================================================================*/
static void GetUalphabeta(void)
{
	tUm.qUs = (signed short int)(tUm.Percent >> 1);	
    
	tUm.qUalpha = MulFrac(tUm.qUs,tUm.qCos);
	tUm.qUbeta = MulFrac(tUm.qUs,tUm.qSin);	
}	
/*==============================================================================
GetUs
==============================================================================*/
void GetUs(void)
{
	unsigned short int Temp;
	signed short int qVq_Max;
    UNION_U32 Temp32;
    
	tPiId.sErr = tIm.qIdGiven - tIm.qId;
    tPiId.Kp = I_KP;				
    tPiId.Ki = I_KI;	
    tPiId.sLimit = I_LIMIT;
    IpiControl(&tPiId);
    if(tCore.RippleCompEnable == 1)
    {
        tUm.qUd = VoltRippleComp(tPiId.sOut);
    }
    else
    {
        tUm.qUd = tPiId.sOut;   
    }   
  
	tPiIq.sErr = tIm.qIqGiven - tIm.qIq;	
    tPiIq.Kp = I_KP;				
	tPiIq.Ki = I_KI;			
    tPiIq.sLimit = I_LIMIT;
    IpiControl(&tPiIq);
    if(tCore.RippleCompEnable == 1)
    {
        tUm.qUq = VoltRippleComp(tPiIq.sOut);
    }
    else
    {
        tUm.qUq = tPiIq.sOut;   
    }
	
    tUm.qUsMax = (signed short int)(tUm.PercentMax >> 1);
	Temp = (unsigned short int)(MulFrac(tUm.qUsMax,tUm.qUsMax) - MulFrac(tUm.qUd,tUm.qUd));
	qVq_Max = CalSqrt(Temp);
	
	if (tUm.qUq > qVq_Max)
		tUm.qUq = qVq_Max;
	if (tUm.qUq < -qVq_Max)
		tUm.qUq = -qVq_Max;
	
	Temp32.U32 = CalAtan(tUm.qUq,tUm.qUd);	
	tUm.PercentOut = Temp32.Words.High << 1;		
	tUm.qUsdAngle = (signed short int)Temp32.Words.Low;
}
/*==============================================================================
纹波电压补偿
//                  TargetDCbus - DCbus
// CompVdq = Vdq + --------------------- * Vdq
//                         DCbus
//
//
//            TargetDCbus 
// CompVdq = ------------- * Vdq
//               DCbus
//
==============================================================================*/
static signed short VoltRippleComp(signed short Vdq)
{
	signed short CompVdq;
    UNION_S32 sTemp32;
    signed short sTemp;
    signed int sTempErr;
    
	if (tGlobal.TargetVbus > tGlobal.VbusInstant)
    {
        sTempErr = (tGlobal.TargetVbus - tGlobal.VbusInstant) << 15; 
        sTemp = (signed short)(sTempErr / tGlobal.VbusInstant);
        sTemp32.S32 = Vdq * sTemp;
        sTemp = (signed short)(sTemp32.S32 >> 15);
        
        if(sTemp > 3276)
            sTemp = 3276;
        if(sTemp < -3276)
            sTemp = -3276;
        
		sTemp32.S32 = Vdq + sTemp;
        if(sTemp32.S32 > 32767)
            sTemp32.S32 = 32767;
        if(sTemp32.S32 < -32768)
            sTemp32.S32 = -32768;
        CompVdq = sTemp32.Words.Low;
    }
	else if (tGlobal.VbusInstant > tGlobal.TargetVbus)
    {
        sTempErr = tGlobal.TargetVbus  << 15;
        sTemp = (signed short)(sTempErr / tGlobal.VbusInstant);
        sTemp32.S32 = Vdq * sTemp;
        
		CompVdq = (signed short)(sTemp32.S32 >> 15);
    }
	else
    {
		CompVdq = Vdq;
    }
    
	return CompVdq;
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
