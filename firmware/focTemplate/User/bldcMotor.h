

#ifndef __FOC_H
#define __FOC_H

#include "userMain.h"

#define SHUNT_RESISTOR 0.1f // 100mR
#define GAIN 100.0f         // opAmp
#define VLOTS_AMPS_RATIO 1.0f / SHUNT_RESISTOR / GAIN

typedef struct
{
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
    float IdGoal;
    float IqGoal;
    // pid
    PidController pid_id;
    PidController pid_iq;
    // volatges
    float Ud;
    float Uq;
    void (*setPwm)(unsigned short int, unsigned short int, unsigned short int);
} BldcMotor;

#endif