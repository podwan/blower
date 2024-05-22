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
static void vectorActionTimeCalculate(BldcMotor *motor, float vector, float a, float b)
{

    float Ta, Tb;

    if (a < 0)
        a = 0;
    if (b < 0)
        b = 0;

    if (vector > VECTOR_MAX)
        vector = VECTOR_MAX;

    Ta = vector * PWM_PERIOD_VALUE * a;
    Tb = vector * PWM_PERIOD_VALUE * b;

    motor->Ta = (PWM_PERIOD_VALUE - Ta - Tb) / 4.0f;
    svPwm->Tb = Tb / 2.0f + svPwm->TcOut;
    svPwm->Tc = Ta / 2.0f + svPwm->TbOut;
}
#if 0
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
#else
void setTorque(BldcMotor *motor, float Uq, float Ud, float angle_el)
{
    float vector;
    vector = _sqrtApprox(Uq * Uq + Ud * Ud);
    int sector = (int)(floor(angle_el / _PI_3)) + 1;
    float X = _sin(theta);
    float Y = _sin(theta + _PI_3);
    float Z = _sin(theta - _PI_3);
    switch (sector)
    {
    case 1:
    }
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
