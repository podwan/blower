#include "svPwm.h"
#include "foc_utils.h"
#include "pwm.h"

/*============================================================================*/
// theta is electric angle in radius
static void getSector(SvPwm *svPwm, float theta)
{
    svPwm->sector = (int)(floor(theta / _PI_3)) + 1;
}
/*============================================================================*/
// 三相相位相差60度的正弦波Ux Uy Uz产生
//  Ux = Sin（θ）
//  Uy = Sin（θ + 60）
//     = 1/2 Sinθ + sqrt(3)/2 Cosθ
//  Uz = Sin（θ - 60）
//     = 1/2 Sinθ - sqrt(3)/2 Cosθ
// theta is electric angle in radius
/*============================================================================*/
static void getXYZ(SvPwm *svPwm, float theta)
{
    svPwm->X = _sin(theta);
    svPwm->Y = _sin(theta + _PI_3);
    svPwm->Z = _sin(theta - _PI_3);
}

/*============================================================================*/
// TcOUt = (T - Ta - Tb)/4
// TbOut = Tb /2 + TcOut
// TaOut = Ta/2 + TbOut
static void vectorActionTimeCalculate(SvPwm *svPwm, float percent, float a, float b)
{

    float Ta, Tb;

    if (a < 0)
        a = 0;
    if (b < 0)
        b = 0;

    if (percent > svPwm->percentMax)
        percent = svPwm->percentMax;

    Ta = percent * PWM_PERIOD_VALUE * a;
    Tb = percent * PWM_PERIOD_VALUE * b;

    svPwm->TcOut = (PWM_PERIOD_VALUE - Ta - Tb) / 4.0f;
    svPwm->TbOut = Tb / 2.0f + svPwm->TcOut;
    svPwm->TaOut = Ta / 2.0f + svPwm->TbOut;
}

/*============================================================================*/
static void setPhaseVoltage(SvPwm *svPwm, float percent)
{
    float ccr1, ccr2, ccr3, ccrMax;

    switch (svPwm->sector)
    {
    case 1: // Ta == T1  Tb == T2   T1 == M * T * (-Z)     T2 == M * T * X
        vectorActionTimeCalculate(svPwm, percent, -(svPwm->Z), svPwm->X);
        ccr1 = svPwm->TaOut;
        ccr2 = svPwm->TbOut;
        ccr3 = svPwm->TcOut;
        break;

    case 2: // Ta == T3  Tb == T2    T3 == M * T * Z     T2 == M * T * Y
        vectorActionTimeCalculate(svPwm, percent, svPwm->Z, svPwm->Y);
        ccr1 = svPwm->TbOut;
        ccr2 = svPwm->TaOut;
        ccr3 = svPwm->TcOut;
        break;

    case 3: // Ta == T3  Tb == T4  T3 == M * T * X  T4 == M * T * (-Y)
        vectorActionTimeCalculate(svPwm, percent, svPwm->X, -(svPwm->Y));
        ccr1 = svPwm->TcOut;
        ccr2 = svPwm->TaOut;
        ccr3 = svPwm->TbOut;
        break;

    case 4: // Ta == T5  Tb == T4   T5 == M * T * (-X)  T4 == M * T * Z
        vectorActionTimeCalculate(svPwm, percent, -(svPwm->X), svPwm->Z);
        ccr1 = svPwm->TcOut;
        ccr2 = svPwm->TbOut;
        ccr3 = svPwm->TaOut;
        break;

    case 5: // Ta == T5  Tb == T6    T5 == M * T * (-Y)  T6 == M * T * (-Z)
        vectorActionTimeCalculate(svPwm, percent, -(svPwm->Y), -(svPwm->Z));
        ccr1 = svPwm->TbOut;
        ccr2 = svPwm->TcOut;
        ccr3 = svPwm->TaOut;
        break;

    case 6: // Ta == T1  Tb == T6  T1 == M * T * Y   T6 == M * T * (-X)
        vectorActionTimeCalculate(svPwm, percent, svPwm->Y, -(svPwm->X));
        ccr1 = svPwm->TaOut;
        ccr2 = svPwm->TcOut;
        ccr3 = svPwm->TbOut;
        break;

    default:
        break;
    }

    // 限制最小占空比
    if (ccr1 < DEAD_TIME)
        ccr1 = DEAD_TIME;
    if (ccr2 < DEAD_TIME)
        ccr2 = DEAD_TIME;
    if (ccr3 < DEAD_TIME)
        ccr3 = DEAD_TIME;
    // 限制最大占空比
    ccrMax = (PWM_PERIOD_VALUE >> 1) - DEAD_TIME;

    if (ccr1 > ccrMax)
        ccr1 = ccrMax;
    if (ccr2 > ccrMax)
        ccr2 = ccrMax;
    if (ccr3 > ccrMax)
        ccr3 = ccrMax;

    svPwm->CCR1 = ccr1;
    svPwm->CCR2 = ccr2;
    svPwm->CCR3 = ccr3;

    svPwm->setPwm(svPwm->CCR1, svPwm->CCR2, svPwm->CCR3);
}

void setSvPwm(SvPwm *svPwm, float percent, float theta)
{
    getSector(svPwm, theta);
    getXYZ(svPwm, theta);
    setPhaseVoltage(svPwm, percent);
}