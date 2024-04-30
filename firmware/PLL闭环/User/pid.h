#ifndef PID_H
#define PID_H

#include "userMain.h"

float pidOperator(PidController *pidController, float error);
void reset(PidController *pidController);

#endif // PID_H