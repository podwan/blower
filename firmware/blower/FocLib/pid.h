#ifndef PID_H
#define PID_H

#include "userMain.h"

typedef struct
{
    float P;             //!< Proportional gain
    float I;             //!< Integral gain
    float D;             //!< Derivative gain
    float output_ramp;   //!< Maximum speed of change of the output value
    float limit;         //!< Maximum output value
    float error_prev;    //!< last tracking error value
    float output_prev;   //!< last pid output value
    float integral_prev; //!< last integral component value
    float Ts;            // PID调节周期
} PidController;

void pidInit(PidController *pidController, float _P, float _I, float _D, float _ramp, float _limit, float _Ts);
float pidOperator(PidController *pidController, float error);
void reset(PidController *pidController);

#endif // PID_H