#ifndef __APP_H
#define __APP_H
#include "userMain.h"

#define KEY_ENABLE 0
#define DISPLAY_ENABLE 0
#define NEED_COMMUNICATION 0
#define WITH_NTC 0

#define DEBUG_COM 1
#define DEBUG_SEG 0

#define POWER_ON_INIT        \
    {                        \
        devState = POWER_ON; \
    }

#define STANDBY_INIT        \
    {                       \
        devState = STANDBY; \
    }

#define SET_INIT        \
    {                   \
        devState = SET; \
    }

#define WORK_INIT        \
    {                    \
        devState = WORK; \
    }

#define FAULT_INIT        \
    {                     \
        devState = FAULT; \
    }

#define TEST_INIT        \
    {                    \
        devState = TEST; \
    }

void appInit();
void appRunning();
extern uint showStuff;
#endif