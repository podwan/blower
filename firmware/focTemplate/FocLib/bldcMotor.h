#ifndef __BLDCMOTOR_H
#define __BLDCMOTOR_H
#include "userMain.h"
#include "math_utils.h"
#include "pid.h"
#include "lowpass_filter.h"
#include "encoder.h"

#define CARRIER_FREQUENCY 10000                          // PWM载波频率
#define PWM_PERIOD_VALUE (160000000 / CARRIER_FREQUENCY) // 16000
#define DEAD_TIME (160000000 / CARRIER_FREQUENCY / 25)   // DT/1.6 = 6400 / 40	DT = 256
#define HALP_PWM_PERIOD (PWM_PERIOD_VALUE / 2.0f)        // PWM period * 2
#define U_DC 12.0f
#define UqMAX (U_DC * _1_SQRT3)
#define OPEN_LOOP_TORQUE UqMAX / 2.0f

#define MOTOR1_MAX_RPM 3000.0f
#define GET_MAX_VELOCITY(MAX_RPM) MAX_RPM / 60.0f * _2PI

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define PWM_GENERATE(p1, p2, p3) \
    {                            \
        TIM1->CCR1 = p1;         \
        TIM1->CCR2 = p2;         \
        TIM1->CCR3 = p3;         \
    }

typedef enum
{
    TORQUE,
    VELOCITY_OPEN_LOOP,
    VELOCITY,
    ANGLE,
} ControlType;

typedef enum
{
    VOLTAGE,
    CURRENT,
} TorqueType;

typedef enum
{
    MOTOR_CALIBRATE,
    MOTOR_READY,
    MOTOR_START,
} MotorState;

typedef struct
{
    MagEncoder magEncoder;
    MotorState state;
    ControlType controlType;
    TorqueType torqueType;
    float Ts;
    float target;
    //  angle
    float zeroElectricAngleOffSet;
    uint8_t pole_pairs;
    float angle_el;
    // currents
    float offset_ia;
    float offset_ib;
    float Ia;
    float Ib;
    float Ialpha;
    float Ibeta;
    float Id;
    float Iq;
    // pid
    PidController pidId;
    PidController pidIq;
    PidController velocityPID;
    PidController anglePID;
    // filter
    LowPassFilter IqFilter;
    LowPassFilter IdFilter;
    LowPassFilter velocityFilter;

    // volatges
    float Ud;
    float Uq;
    float Ualpha;
    float Ubeta;
    float Ta, Tb, Tc;
    void (*updatePwm)(unsigned short int, unsigned short int, unsigned short int);
    void (*startPwm)();
    void (*stopPwm)();
} BldcMotor;

void getElecAngle(BldcMotor *motor);
void foc(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b);
// void getZeroElecAngle(BldcMotor *motor);
void setPhaseVoltage1(BldcMotor *motor, float Uq, float Ud, float angle_el);
void goToZeroElecAngle(BldcMotor *motor);
#endif
