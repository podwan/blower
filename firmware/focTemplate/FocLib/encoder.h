
#ifndef __ENCODER_H
#define __ENCODER_H
#include "userMain.h"
/**
 *  Direction structure
 */
typedef enum
{
    CW = 1,     // clockwise
    CCW = -1,   // counter clockwise
    UNKNOWN = 0 // not yet known or invalid state
} Direction;

typedef struct
{
    float angle_prev;           // 最后一次调用 getSensorAngle() 的输出结果，用于得到完整的圈数和速度
    float vel_angle_prev;       // 最后一次调用 getVelocity 时的角度
    int32_t full_rotations;     // 总圈数计数
    int32_t vel_full_rotations; // 用于速度计算的先前完整旋转圈数
    float shaftAngle;
    float fullAngle;
    float velocity;
    float Ts; // update period in microsecond
    Direction direction;
    float (*getRawAngle)(void);
} MagEncoder;

void encoderInit(MagEncoder *encoder, float _Ts, float (*_getRawAngle)(void));
// void encoderUpdate(MagEncoder *encoder);
void getVelocity(MagEncoder *encoder);
void encoderUpdate(MagEncoder *encoder);
// float getMechanicalAngle();
// float getFullAngle();

#endif
