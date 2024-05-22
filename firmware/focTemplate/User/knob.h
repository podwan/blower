#ifndef HELLOWORD_DYNAMIC_FW_KNOB_H
#define HELLOWORD_DYNAMIC_FW_KNOB_H

#include "userMain.h"
#include "bldcMotor.h"
typedef enum
{
    MODE_DISABLE = 0,
    MODE_INERTIA,
    MODE_ENCODER,
    MODE_SPRING,
    MODE_DAMPED,
    MODE_SPIN
} KnobMode;

typedef struct
{
    BldcMotor motor;
    KnobMode mode;

} KnobSimulator;

#endif // HELLOWORD_DYNAMIC_FW_KNOB_H
