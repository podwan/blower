#ifndef __MOTOR_H
#define __MOTOR_H

#include "userMain.h"

typedef enum
{
    MOTOR_STOP,
    MOTOR_START,
    MOTOR_WAIT,
    MOTOR_RUN,
} MotorState;

typedef struct
{
    unsigned short int Tick;
    unsigned int Tick1s;
    unsigned short int FaultNum;
    MotorState state;
    SvPwm svPwm
} Motor;

#endif