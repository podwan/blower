#include "voltage.h"
#include "foc_utils.h"
#include "pwm.h"
#include "current.h"
#include "pid.h"

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
