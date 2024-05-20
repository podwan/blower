#include "voltage.h"
#include "math_utils.h"
#include "comm.h"
#include "bldcMotor.h"
#include "pid.h"
#include "app.h"
const char sectorRemap[] = {0, 2, 6, 1, 4, 3, 5};
void getDQVoltages(BldcMotor *motor)
{

    //     Id = lpfOperator(& lpf,  Id);
    //     Iq = lpfOperator(& lpf,  Iq);

    //     Ud = pidOperator(& pid_id,  IdGoal -  Id);
    //     Uq = pidOperator(& pid_iq,  IqGoal -  Iq);
}
/*============================================================================*/
// Park逆变换
// Ualpha = Ud * Cosθr - Uq * Sinθr
// Ubeta = Uq * Cosθr + Ud * Sinθr
/*============================================================================*/
void getABVoltages(BldcMotor *motor)
{
    float ct;
    float st;
    _sincos(motor->angle_el, &st, &ct);
    motor->Ualpha = motor->Ud * ct - motor->Uq * st;
    motor->Ubeta = motor->Uq * ct + motor->Ud * st;
}
#if 0
// Park逆变换+SVPWM
void setTorque(BldcMotor *motor, float Uq, float Ud, float angle_el)
{
    static float Ts = 1.0f;

    float t1, t2, t3, t4, t5, t6, t7;
    float sum, k_svpwm;
    float ct;
    float st;
    _sincos(angle_el, &st, &ct);
    // Park逆变换
    float Ualpha = -Uq * st + Ud * ct;
    float Ubeta = Uq * ct + Ud * st;

    // 扇区判断
    float K = _SQRT3 * Ts / U_DC; // SVPWM调制比
    float u1 = Ubeta * K;
    float u2 = (_SQRT3_2 * Ualpha - 0.5f * Ubeta) * K; // sqrt(3)/2 = 0.8660254
    float u3 = (-_SQRT3_2 * Ualpha - 0.5f * Ubeta) * K;

    uint8_t sector = (u1 > 0.0f) + ((u2 > 0.0f) << 1) + ((u3 > 0.0f) << 2); // sector = A + 2B + 4C

    // 非零矢量和零矢量作用时间的计算
    switch (sector)
    {
    case 3: // 扇区1
        t4 = u2;
        t6 = u1;
        sum = t4 + t6;
        if (sum > Ts) // 过调制处理
        {
            k_svpwm = Ts / sum;
            t4 *= k_svpwm;
            t6 *= k_svpwm;
        }
        t7 = (Ts - t4 - t6) / 2.0f;
        motor->Ta = t4 + t6 + t7;
        motor->Tb = t6 + t7;
        motor->Tc = t7;
        break;
    case 1: // 扇区2
        t2 = -u2;
        t6 = -u3;
        sum = t2 + t6;
        if (sum > Ts)
        {
            k_svpwm = Ts / sum;
            t2 *= k_svpwm;
            t6 *= k_svpwm;
        }
        t7 = (Ts - t2 - t6) / 2.0f;
        motor->Ta = t6 + t7;
        motor->Tb = t2 + t6 + t7;
        motor->Tc = t7;
        break;
    case 5: // 扇区3
        t2 = u1;
        t3 = u3;
        sum = t2 + t3;
        if (sum > Ts)
        {
            k_svpwm = Ts / sum;
            t2 *= k_svpwm;
            t3 *= k_svpwm;
        }
        t7 = (Ts - t2 - t3) / 2.0f;
        motor->Ta = t7;
        motor->Tb = t2 + t3 + t7;
        motor->Tc = t3 + t7;
        break;
    case 4: // 扇区4
        t1 = -u1;
        t3 = -u2;
        sum = t1 + t3;
        if (sum > Ts)
        {
            k_svpwm = Ts / sum;
            t1 *= k_svpwm;
            t3 *= k_svpwm;
        }
        t7 = (Ts - t1 - t3) / 2.0f;
        motor->Ta = t7;
        motor->Tb = t3 + t7;
        motor->Tc = t1 + t3 + t7;
        break;
    case 6: // 扇区5
        t1 = u3;
        t5 = u2;
        sum = t1 + t5;
        if (sum > Ts)
        {
            k_svpwm = Ts / sum;
            t1 *= k_svpwm;
            t5 *= k_svpwm;
        }
        t7 = (Ts - t1 - t5) / 2.0f;
        motor->Ta = t5 + t7;
        motor->Tb = t7;
        motor->Tc = t1 + t5 + t7;
        break;
    case 2: // 扇区6
        t4 = -u3;
        t5 = -u1;
        sum = t4 + t5;
        if (sum > Ts)
        {
            k_svpwm = Ts / sum;
            t4 *= k_svpwm;
            t5 *= k_svpwm;
        }
        t7 = (Ts - t4 - t5) / 2.0f;
        motor->Ta = t4 + t5 + t7;
        motor->Tb = t7;
        motor->Tc = t5 + t7;
        break;
    default:
        motor->Ta = 0;
        motor->Tb = 0;
        motor->Tc = 0;
        break;
    }
    // step4：6路PWM输出
    motor->updatePwm(HALP_PWM_PERIOD * motor->Ta, HALP_PWM_PERIOD * motor->Tb, HALP_PWM_PERIOD * motor->Tc);
}
#elif 0
void setTorque(BldcMotor *motor, float Uq, float Ud, float angle_el)
{
    static float Ts = 1.0f;
    // Uq = _constrain(Uq, -UqMAX, UqMAX);

    float ct;
    float st;
    _sincos(angle_el, &st, &ct);
    // Park逆变换
    float Ualpha = Ud * ct - Uq * st;
    float Ubeta = Uq * ct + Ud * st;

    float tFirst, tSecond;
    float K = _SQRT3 * Ts / U_DC;
    float X = K * Ubeta;
    float Y = K * (_SQRT3_2 * Ualpha - Ubeta * 0.5f);
    float Z = K * (-_SQRT3_2 * Ualpha - Ubeta * 0.5f);

    uint8_t sector = sectorRemap[(X > 0.0f) + ((Y > 0.0f) << 1) + ((Z > 0.0f) << 2)]; // sector = A + 2B + 4C

    switch (sector)
    {
    case 1:
        tFirst = Y;
        tSecond = X;

        motor->Ta = (Ts - tFirst - tSecond) / 2.0f;
        motor->Tb = motor->Ta + tFirst;
        motor->Tc = motor->Tb + tSecond;

        break;
    case 2:
        tFirst = -Y;
        tSecond = -Z;

        motor->Tb = (Ts - tFirst - tSecond) / 2.0f;
        motor->Ta = motor->Tb + tFirst;
        motor->Tc = motor->Ta + tSecond;

        break;
    case 3:
        tFirst = X;
        tSecond = Z;

        motor->Tb = (Ts - tFirst - tSecond) / 2.0f;
        motor->Tc = motor->Tb + tFirst;
        motor->Ta = motor->Tc + tSecond;

        break;
    case 4:
        tFirst = -X;
        tSecond = -Y;

        motor->Tc = (Ts - tFirst - tSecond) / 2.0f;
        motor->Tb = motor->Tc + tFirst;
        motor->Ta = motor->Tb + tSecond;

        break;

    case 5:
        tFirst = Z;
        tSecond = Y;

        motor->Tc = (Ts - tFirst - tSecond) / 2.0f;
        motor->Ta = motor->Tc + tFirst;
        motor->Tb = motor->Ta + tSecond;

        break;

    case 6:
        tFirst = -Z;
        tSecond = -X;

        motor->Ta = (Ts - tFirst - tSecond) / 2.0f;
        motor->Tc = motor->Ta + tFirst;
        motor->Tb = motor->Tc + tSecond;

        break;
    }

    motor->updatePwm(HALP_PWM_PERIOD * motor->Ta, HALP_PWM_PERIOD * motor->Tb, HALP_PWM_PERIOD * motor->Tc);
}
#elif 1

void setTorque(BldcMotor *motor, float Uq, float Ud, float angle_el)
{

    float center;
    float _ca, _sa;
    float Ualpha, Ubeta;
    float Ua, Ub, Uc;

    // Sinusoidal PWM modulation
    // Inverse Park + Clarke transformation
    _sincos(angle_el, &_sa, &_ca);

    // Inverse park transform
    Ualpha = _ca * Ud - _sa * Uq; // -sin(angle) * Uq;
    Ubeta = _sa * Ud + _ca * Uq;  //  cos(angle) * Uq;

    // Clarke transform
    Ua = Ualpha;
    Ub = -0.5f * Ualpha + _SQRT3_2 * Ubeta;
    Uc = -0.5f * Ualpha - _SQRT3_2 * Ubeta;

    center = UqMAX / 2;

    // discussed here: https://community.simplefoc.com/t/embedded-world-2023-stm32-cordic-co-processor/3107/165?u=candas1
    // a bit more info here: https://microchipdeveloper.com/mct5001:which-zsm-is-best
    // Midpoint Clamp
    float Umin = min(Ua, min(Ub, Uc));
    float Umax = max(Ua, max(Ub, Uc));
    center -= (Umax + Umin) / 2;

    Ua += center;
    Ub += center;
    Uc += center;

    motor->Ta = _constrain(Ua / U_DC, 0.0f, 1.0f);
    motor->Tb = _constrain(Ub / U_DC, 0.0f, 1.0f);
    motor->Tc = _constrain(Uc / U_DC, 0.0f, 1.0f);

    motor->updatePwm(HALP_PWM_PERIOD * motor->Ta, HALP_PWM_PERIOD * motor->Tb, HALP_PWM_PERIOD * motor->Tc);
    // set the voltages in driver
    // driver->setPwm(Ua, Ub, Uc);
}
#endif
void svpwm_test(BldcMotor *motor, float Uq, float acc)
{
    motor->angle_el += acc;
    if (motor->angle_el > _2PI)
        motor->angle_el = 0;

    setTorque(motor, Uq, 0.0f, motor->angle_el);
}
// Park逆变换*SVPWM
