#include "voltage.h"
#include "foc_utils.h"
#include "pwm.h"
#include "current.h"
#include "pid.h"

/*============================================================================*/
// voltages->eAngle is electric angle in radius
static void getSector(Voltages *voltages)
{
    voltages->sector = (int)(floor(voltages->eAngle / _PI_3)) + 1;
}
/*============================================================================*/
// 三相相位相差60度的正弦波Ux Uy Uz产生
//  Ux = Sin（θ）
//  Uy = Sin（θ + 60）
//     = 1/2 Sinθ + sqrt(3)/2 Cosθ
//  Uz = Sin（θ - 60）
//     = 1/2 Sinθ - sqrt(3)/2 Cosθ
// voltages->eAngle is electric angle in radius
/*============================================================================*/
static void getXYZ(Voltages *voltages)
{
    voltages->X = _sin(voltages->eAngle);
    voltages->Y = _sin(voltages->eAngle + _PI_3);
    voltages->Z = _sin(voltages->eAngle - _PI_3);
}

/*============================================================================*/
// TcOUt = (T - Ta - Tb)/4
// TbOut = Tb /2 + TcOut
// TaOut = Ta/2 + TbOut
static void vectorActionTimeCalculate(Voltages *voltages, float a, float b)
{

    float Ta, Tb;

    if (a < 0)
        a = 0;
    if (b < 0)
        b = 0;

    if (voltages->percent > voltages->percentMax)
        voltages->percent = voltages->percentMax;

    Ta = voltages->percent * PWM_PERIOD_VALUE * a;
    Tb = voltages->percent * PWM_PERIOD_VALUE * b;

    voltages->TcOut = (PWM_PERIOD_VALUE - Ta - Tb) / 4.0f;
    voltages->TbOut = Tb / 2.0f + voltages->TcOut;
    voltages->TaOut = Ta / 2.0f + voltages->TbOut;
}

/*============================================================================*/
static void setSvPwm(Voltages *voltages)
{
    float ccr1, ccr2, ccr3, ccrMax;

    switch (voltages->sector)
    {
    case 1: // Ta == T1  Tb == T2   T1 == M * T * (-Z)     T2 == M * T * X
        vectorActionTimeCalculate(voltages, -(voltages->Z), voltages->X);
        ccr1 = voltages->TaOut;
        ccr2 = voltages->TbOut;
        ccr3 = voltages->TcOut;
        break;

    case 2: // Ta == T3  Tb == T2    T3 == M * T * Z     T2 == M * T * Y
        vectorActionTimeCalculate(voltages, voltages->Z, voltages->Y);
        ccr1 = voltages->TbOut;
        ccr2 = voltages->TaOut;
        ccr3 = voltages->TcOut;
        break;

    case 3: // Ta == T3  Tb == T4  T3 == M * T * X  T4 == M * T * (-Y)
        vectorActionTimeCalculate(voltages, voltages->X, -(voltages->Y));
        ccr1 = voltages->TcOut;
        ccr2 = voltages->TaOut;
        ccr3 = voltages->TbOut;
        break;

    case 4: // Ta == T5  Tb == T4   T5 == M * T * (-X)  T4 == M * T * Z
        vectorActionTimeCalculate(voltages, -(voltages->X), voltages->Z);
        ccr1 = voltages->TcOut;
        ccr2 = voltages->TbOut;
        ccr3 = voltages->TaOut;
        break;

    case 5: // Ta == T5  Tb == T6    T5 == M * T * (-Y)  T6 == M * T * (-Z)
        vectorActionTimeCalculate(voltages, -(voltages->Y), -(voltages->Z));
        ccr1 = voltages->TbOut;
        ccr2 = voltages->TcOut;
        ccr3 = voltages->TaOut;
        break;

    case 6: // Ta == T1  Tb == T6  T1 == M * T * Y   T6 == M * T * (-X)
        vectorActionTimeCalculate(voltages, voltages->Y, -(voltages->X));
        ccr1 = voltages->TaOut;
        ccr2 = voltages->TcOut;
        ccr3 = voltages->TbOut;
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

    voltages->CCR1 = ccr1;
    voltages->CCR2 = ccr2;
    voltages->CCR3 = ccr3;

    voltages->setPwm(voltages->CCR1, voltages->CCR2, voltages->CCR3);
}

void setPhaseVoltage(Voltages *voltages)
{
    getSector(voltages);
    getXYZ(voltages);
    setSvPwm(voltages);
}

void getPercentTheta(Motor *motor)
{
}