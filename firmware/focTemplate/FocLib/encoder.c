
#include "encoder.h"
#include "math_utils.h"
void encoderInit(MagEncoder *encoder, float _Ts, float (*_getRawAngle)(void))
{
    encoder->angle_prev = 0;
    encoder->vel_angle_prev = 0;
    encoder->full_rotations = 0;
    encoder->vel_full_rotations = 0;
    encoder->shaftAngle = 0;
    encoder->fullAngle = 0;
    encoder->velocity = 0;
    encoder->Ts = _Ts;
    encoder->getRawAngle = _getRawAngle;
    encoder->direction = UNKNOWN;
}

void encoderUpdate(MagEncoder *encoder)
{
    float val = encoder->getRawAngle();

    float d_angle = val - encoder->angle_prev;
    // 圈数检测
    if (abs(d_angle) > (0.8f * _2PI))
        encoder->full_rotations += (d_angle > 0) ? -1 : 1;

    // angle
    encoder->angle_prev = val;
    encoder->shaftAngle = val;
    encoder->fullAngle = (float)encoder->full_rotations * _2PI + encoder->angle_prev;

    // 速度计算
    val = ((float)(encoder->full_rotations - encoder->vel_full_rotations) * _2PI + (encoder->angle_prev - encoder->vel_angle_prev)) / encoder->Ts;
    // 保存变量以待将来使用
    encoder->vel_angle_prev = encoder->angle_prev;
    encoder->vel_full_rotations = encoder->full_rotations;
    encoder->velocity = val;
}


