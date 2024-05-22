#include "lowpass_filter.h"

void lpfInit(LowPassFilter *filter, const float _Tf, const float _dt)
{
    filter->Tf = _Tf;
    filter->dt = _dt;
    filter->y_prev = 0;
}

float lpfOperator(LowPassFilter *filter, float x)
{

    float alpha = filter->Tf / (filter->Tf + filter->dt);
    float y = alpha * filter->y_prev + (1.0f - alpha) * x;
    filter->y_prev = y;

    return y;
}
