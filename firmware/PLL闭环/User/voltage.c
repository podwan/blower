#include "voltage.h"
#include "foc_utils.h"
#include "pwm.h"
#include "current.h"
#include "pid.h"

#if 1

void getUdUq(Motor *motor)
{
}

const char sectorRemap[] = {0, 2, 6, 1, 4, 3, 5};

// 输入Uq、Ud和电角度，输出三路PWM
void setPhaseVoltage(Voltages *voltages)
{
    float tFirst, tSecond;
    int d1, d2, d3;

    // Park逆变换
    float Ualpha = -voltages->Uq * _sin(voltages->eAngle) + voltages->Ud * _cos(voltages->eAngle);
    float Ubeta = voltages->Uq * _cos(voltages->eAngle) + voltages->Ud * _sin(voltages->eAngle);

    float K = _SQRT3 * PWM_PERIOD_VALUE / U_DC;
    float X = Ubeta * K;
    float Y = (_SQRT3 * Ualpha / 2.0f + Ubeta / 2.0f) * K;
    float Z = (-_SQRT3 * Ualpha / 2.0f + Ubeta / 2.0f) * K;

    uint8_t sector = sectorRemap[(X > 0.0f) + ((Y > 0.0f) << 1) + ((Z > 0.0f) << 2)]; // sector = A + 2B + 4C

    switch (sector)
    {
    case 1:
        tFirst = -Z;
        tSecond = X;

        d1 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d2 = d1 + tFirst;
        d3 = d2 + tSecond;
        break;
    case 2:
        tFirst = Z;
        tSecond = Y;

        d2 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d1 = d2 + tFirst;
        d3 = d1 + tSecond;
        break;
    case 3:
        tFirst = X;
        tSecond = -Y;

        d2 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d3 = d2 + tFirst;
        d1 = d3 + tSecond;

        break;
    case 4:
        tFirst = -X;
        tSecond = Z;

        d3 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d2 = d3 + tFirst;
        d1 = d2 + tSecond;
        break;

    case 5:
        tFirst = -Y;
        tSecond = -Z;

        d3 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d1 = d3 + tFirst;
        d2 = d1 + tSecond;
        break;

    case 6:
        tFirst = Y;
        tSecond = -X;

        d1 = (PWM_PERIOD_VALUE - tFirst - tSecond) / 2.0f;
        d3 = d1 + tFirst;
        d2 = d3 + tSecond;
        break;
    }

    voltages->setPwm(d1, d2, d3); // 输出三路PWM，驱动无刷电机转动
}
#else
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
    float err;
    float UqMax;

    err = motor->currents.IdGiven - motor->currents.Id;
    motor->voltages.Ud = pidOperator(&motor->PiId, err);

    err = motor->currents.IqGiven - motor->currents.Iq;
    motor->voltages.Uq = pidOperator(&motor->PiIq, err);

    motor->voltages.UsMax = motor->voltages.percentMax * K;

    UqMax = _sqrt(motor->voltages.UsMax * motor->voltages.UsMax - motor->voltages.Ud * motor->voltages.Ud);
    _constrain(motor->voltages.Uq, -UqMax, UqMax);

    motor->voltages.Us = _sqrt(motor->voltages.Uq * motor->voltages.Uq + motor->voltages.Ud * motor->voltages.Ud);
    motor->voltages.percent = motor->voltages.Us / K;
}
#endif