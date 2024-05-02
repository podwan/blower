#ifndef __MOTOR_H
#define __MOTOR_H

#include "userMain.h"

#define I_KP 0.125f
#define I_KI 0.0039f
#define I_LIMIT 0.84f

void motorInit();
void motor1Drive();
extern tGlobal_TypeDef tGlobal;
#endif
