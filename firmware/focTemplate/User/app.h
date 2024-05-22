#ifndef __APP_H
#define __APP_H

#include "userMain.h"

#define CALI_PID 1

#define CURRENT_MAX 0.8f
#define MAX_VELOCITY 300

#define WORK_INIT                   \
    {                               \
        devState = WORK;            \
        flashCnt = 0;               \
        motor1.state = MOTOR_START; \
        motor1.startPwm();          \
    }

#define STANDBY_INIT                \
    {                               \
        devState = STANDBY;         \
        flashCnt = 0;               \
        motor1.state = MOTOR_READY; \
    }

#ifdef __cplusplus // 使用C语言的方式编译方法名。
extern "C"
{
#endif

    void appInit();
#ifdef __cplusplus
}
#endif

void appRunning();
// void txDataProcess();
extern float txA, txB, txC;
extern float load_data[];
#endif
