#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H
#include "userMain.h"
typedef struct
{
    float Tf;     //!< Low pass filter time constant
    float dt;     // 0.0f ~ 0.3f(300ms)
    float y_prev; //!< filtered value in previous execution step
} LowPassFilter;

void lpfInit(LowPassFilter *filter, const float _Tf, const float _dt);
float lpfOperator(LowPassFilter *filter, float x);

#endif // LOWPASS_FILTER_H