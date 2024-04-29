/**************************************************************************************************
 * �ŷ�ʵս����
 * @project Svpwm
 * @file    Voltage.c
 * @author  �ŷ�ʵս�����Ŷ�
 * @date    2024/03/28
 * @version V100
 * @Copyright  �������Ȩ�ŷ�ʵս��������
 **************************************************************************************************/
#include "..\Include\Voltage.h"
/**************************************************************************************************
 * Svpwm
 **************************************************************************************************/
void VoltageInitialize(void)
{
    tUm.PercentMax = US_MAX_PERCENT;
}
/*============================================================================*/
void UsOut(unsigned short int Percent, signed short int qUA)
{
    GetUsSector(qUA);
    GetUxyz(qUA);
    SvpwmOut(Percent);
}
/*============================================================================*/
static void GetUsSector(unsigned short int UAngle)
{
    if ((UAngle > EANGLE0) && (UAngle < EANGLE60))
        tUm.Sector = 1;
    else if ((UAngle >= EANGLE60) && (UAngle < EANGLE120))
        tUm.Sector = 2;
    else if ((UAngle >= EANGLE120) && (UAngle < EANGLE180))
        tUm.Sector = 3;
    else if ((UAngle >= EANGLE180) && (UAngle < EANGLE240))
        tUm.Sector = 4;
    else if ((UAngle >= EANGLE240) && (UAngle < EANGLE300))
        tUm.Sector = 5;
    else
        tUm.Sector = 6;
}
/*============================================================================*/
// ������λ���60�ȵ����Ҳ�Ux Uy Uz����
//  Ux = Sin���ȣ�
//  Uy = Sin���� + 60��
//     = 1/2 Sin�� + sqrt(3)/2 Cos��
//  Uz = Sin���� - 60��
//     = 1/2 Sin�� - sqrt(3)/2 Cos��
/*============================================================================*/
static void GetUxyz(signed short int qUA)
{
    UNION_U32 Temp32;
    signed short int sTempA, sTempB;

    Temp32.U32 = CalSinCos(0x7fff, qUA);
    tUm.qCos = (signed short int)Temp32.Words.Low;
    tUm.qSin = (signed short int)Temp32.Words.High;

    tUm.qUx = tUm.qSin;

    sTempA = qUA + EANGLE60;
    Temp32.U32 = CalSinCos(0x7fff, sTempA);
    tUm.qUy = (signed short int)Temp32.Words.High;

    sTempB = qUA - EANGLE60;
    Temp32.U32 = CalSinCos(0x7fff, sTempB);
    tUm.qUz = (signed short int)Temp32.Words.High;
}
/*==============================================================================
 �����������Ʋ�
==============================================================================*/
static void SvpwmOut(unsigned short int Percent)
{
    unsigned short int PDC1Temp;
    unsigned short int PDC2Temp;
    unsigned short int PDC3Temp;
    unsigned short int PDCMax;

    switch (tUm.Sector)
    {
    case 1:
        VectorActionTimeCalculate(Percent, -tUm.qUz, tUm.qUx);
        PDC1Temp = tUm.Taout;
        PDC2Temp = tUm.Tbout;
        PDC3Temp = tUm.Tcout;
        break;
    case 2:
        VectorActionTimeCalculate(Percent, tUm.qUz, tUm.qUy);
        PDC1Temp = tUm.Tbout;
        PDC2Temp = tUm.Taout;
        PDC3Temp = tUm.Tcout;
        break;
    case 3:
        VectorActionTimeCalculate(Percent, tUm.qUx, -tUm.qUy);
        PDC1Temp = tUm.Tcout;
        PDC2Temp = tUm.Taout;
        PDC3Temp = tUm.Tbout;
        break;
    case 4:
        VectorActionTimeCalculate(Percent, -tUm.qUx, tUm.qUz);
        PDC1Temp = tUm.Tcout;
        PDC2Temp = tUm.Tbout;
        PDC3Temp = tUm.Taout;
        break;
    case 5:
        VectorActionTimeCalculate(Percent, -tUm.qUy, -tUm.qUz);
        PDC1Temp = tUm.Tbout;
        PDC2Temp = tUm.Tcout;
        PDC3Temp = tUm.Taout;
        break;
    case 6:
        VectorActionTimeCalculate(Percent, tUm.qUy, -tUm.qUx);
        PDC1Temp = tUm.Taout;
        PDC2Temp = tUm.Tcout;
        PDC3Temp = tUm.Tbout;
        break;
    default:
        break;
    }

    // ������Сռ�ձ�
    if (PDC1Temp < DEAD_TIME)
        PDC1Temp = DEAD_TIME;
    if (PDC2Temp < DEAD_TIME)
        PDC2Temp = DEAD_TIME;
    if (PDC3Temp < DEAD_TIME)
        PDC3Temp = DEAD_TIME;
    // �������ռ�ձ�
    PDCMax = (PWM_PERIOD_VALUE >> 1) - DEAD_TIME;
    if (PDC1Temp > PDCMax)
        PDC1Temp = PDCMax;
    if (PDC2Temp > PDCMax)
        PDC2Temp = PDCMax;
    if (PDC3Temp > PDCMax)
        PDC3Temp = PDCMax;

    tUm.CCR1 = PDC1Temp;
    tUm.CCR2 = PDC2Temp;
    tUm.CCR3 = PDC3Temp;

    // ����ռ�ձȸ���
    TIM8->CCR1 = PDC1Temp;
    TIM8->CCR2 = PDC2Temp;
    TIM8->CCR3 = PDC3Temp;
}
/*============================================================================*/
static void VectorActionTimeCalculate(unsigned short int Percent, signed short int Sa, signed short int Sb)
{
    UNION_U32 Temp32;
    UNION_U32 Temp32A, Temp32B;

    unsigned short int a, b;

    if (Sa < 0)
        Sa = 0;
    if (Sb < 0)
        Sb = 0;

    a = (unsigned short int)Sa;
    b = (unsigned short int)Sb;

    if (Percent > tUm.PercentMax)
        Percent = tUm.PercentMax;

    Temp32.U32 = (unsigned int)(Percent * PWM_PERIOD_VALUE);
    Temp32A.U32 = (unsigned int)(Temp32.Words.High * a);
    Temp32B.U32 = (unsigned int)(Temp32.Words.High * b);

    tUm.Tcout = ((PWM_PERIOD_VALUE >> 1) - Temp32A.Words.High - Temp32B.Words.High) >> 1;
    tUm.Tbout = tUm.Tcout + Temp32B.Words.High;
    tUm.Taout = tUm.Tbout + Temp32A.Words.High;
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
