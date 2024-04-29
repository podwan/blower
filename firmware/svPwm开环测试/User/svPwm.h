#ifndef __SVPWM_H
#define __SVPWM_H

#include "userMain.h"

#define CARRIER_FREQUENCY 25000                          // PWM载波频率
#define PWM_PERIOD_VALUE (160000000 / CARRIER_FREQUENCY) // 6400
#define DEAD_TIME (160000000 / CARRIER_FREQUENCY / 25)   // DT/1.6 = 6400 / 40	DT = 256

#define MAX_PERCENT 0.95f

/*===========================================================================*/

void setSvPwm(SvPwm *svPwm, float percent, float theta);
#endif