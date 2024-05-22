#ifndef __USERTIMER_H
#define __USERTIMER_H
#include "userMain.h"
#define ZERO_IO
#define ZERO_POLL 0
#define USE_ZERO_TIMER 0
#define DOUBLE_EDGE 0
#define CROSS_ZERO_POWER_OFF_DECTECTION 0
#define FREQUENCE_JUDGE 0
#define ZERO_ERR_TIME 1000

void dealPer100us();
unsigned char getFrequence();
bool getOneSecFlag();
bool getPowerLost();
bool getOneMsFlag();
void initializeClock();
bool getZeroErr();
void setCrossZero4timer();
bool getCrossZero();
bool get5MsFlag();
bool get10MsFlag();
bool get20MsFlag();
bool get30MsFlag();
bool get100MsFlag();
bool get500MsFlag();
#endif