#include "knob.h"
#include "bldcMotor.h"
void knobSimulatorInit(KnobSimulator *knob, BldcMotor _motor)
{
    knob->motor = _motor;
    // motor->config.controlMode = Motor::ControlMode_t::TORQUE;
    // motor->config.voltageLimit = 1.5;
    // motor->config.velocityLimit = 100;
    // motor->config.pidVelocity.p = 0.1;
    // motor->config.pidVelocity.i = 0.0;
    // motor->config.pidVelocity.d = 0.0;
    // motor->config.pidAngle.p = 80;
    // motor->config.pidAngle.i = 0;
    // motor->config.pidAngle.d = 0.7;

    // // When motor calibrated, we can replace Init with something like:
    // // motor->Init(1.815850, EncoderBase::CW)
    // if (motor->Init())
    // {
    //     printf("ZeroElectricAngleOffset: %f | Encoder direction: %s\n", motor->zeroElectricAngleOffset,
    //            motor->encoder->countDirection == EncoderBase::CW ? "CW" : "CCW");
    //     motor->target = 0;
    //     motor->SetEnable(false);
    // } else
    //     printf("Error[%d]\n", motor->error);
}

void knobSimulatorSetMode(KnobSimulator *knob)
{
    // mode = _mode;

    // lastAngle = GetPosition();
    // lastVelocity = GetVelocity();

    switch (knob->mode)
    {
    case MODE_DISABLE:
        //         motor->SetEnable(false);
        break;
    case MODE_INERTIA:
    {
        //         motor->SetEnable(true);
        //         motor->SetTorqueLimit(0.5);
        //         motor->config.controlMode = Motor::VELOCITY;
        //         motor->config.pidVelocity.p = 0.1;
        //         motor->config.pidVelocity.i = 0.0;
        //         motor->config.pidVelocity.d = 0.0;
        //         motor->config.pidAngle.p = 20;
        //         motor->config.pidAngle.i = 0;
        //         motor->config.pidAngle.d = 0.7;
        //         motor->target = 0;
    }
    break;
    case MODE_ENCODER:
    {
        //         motor->SetEnable(true);
        //         motor->SetTorqueLimit(1.5);
        //         motor->config.controlMode = Motor::ControlMode_t::ANGLE;
        //         motor->config.pidVelocity.p = 0.1;
        //         motor->config.pidVelocity.i = 0.0;
        //         motor->config.pidVelocity.d = 0.0;
        //         motor->config.pidAngle.p = 100;
        //         motor->config.pidAngle.i = 0;
        //         motor->config.pidAngle.d = 3.5;
        //         motor->target = 4.2;
        //         lastAngle = 4.2;
    }
    break;
    case MODE_SPRING:
    {
        //         motor->SetEnable(true);
        //         motor->SetTorqueLimit(1.5);
        //         motor->config.controlMode = Motor::ControlMode_t::ANGLE;
        //         motor->config.pidVelocity.p = 0.1;
        //         motor->config.pidVelocity.i = 0.0;
        //         motor->config.pidVelocity.d = 0.0;
        //         motor->config.pidAngle.p = 100;
        //         motor->config.pidAngle.i = 0;
        //         motor->config.pidAngle.d = 3.5;
        //         motor->target = 4.2;
    }
    break;
    case MODE_DAMPED:
    {
        //         motor->SetEnable(true);
        //         motor->SetTorqueLimit(1.5);
        //         motor->config.controlMode = Motor::ControlMode_t::VELOCITY;
        //         motor->config.pidVelocity.p = 0.1;
        //         motor->config.pidVelocity.i = 0.0;
        //         motor->config.pidVelocity.d = 0.0;
        //         motor->target = 0;
    }
    break;
    case MODE_SPIN:
    {
        //         motor->SetEnable(true);
        //         motor->SetTorqueLimit(1.5);
        //         motor->config.controlMode = Motor::ControlMode_t::VELOCITY;
        //         motor->config.pidVelocity.p = 0.3;
        //         motor->config.pidVelocity.i = 0.0;
        //         motor->config.pidVelocity.d = 0.0;
        //         motor->target = 20;
    }
    break;
    }
}

void knobSimulatorTick(KnobSimulator *knob)
{
    switch (knob->mode)
    {
    case MODE_INERTIA:
    {
        //         auto v = GetVelocity();
        //         if (v > 1 || v < -1)
        //         {
        //             if (std::abs(v - lastVelocity) > 0.3)
        //                 motor->target = v;
        //         } else
        //         {
        //             motor->target = 0;
        //         }
        //         lastVelocity = v;
    }
    break;
    case MODE_ENCODER:
    {
        //         auto a = GetPosition();
        //         if (a - lastAngle > _PI / (float) encoderDivides)
        //         {
        //             motor->target += _2PI / (float) encoderDivides;
        //             lastAngle = motor->target;
        //             encoderPosition++;
        //         } else if (a - lastAngle < -_PI / (float) encoderDivides)
        //         {
        //             motor->target -= _2PI / (float) encoderDivides;
        //             lastAngle = motor->target;
        //             encoderPosition--;
        //         }
    }
    break;
    case MODE_DAMPED:
        //         if (limitPositionMax != 0 && limitPositionMin != 0)
        //         {
        //             auto a = GetPosition();
        //             if (a > limitPositionMax)
        //             {
        //                 motor->config.controlMode = Motor::ANGLE;
        //                 motor->target = limitPositionMax;
        //             } else if (a < limitPositionMin)
        //             {
        //                 motor->config.controlMode = Motor::ANGLE;
        //                 motor->target = limitPositionMin;
        //             } else
        //             {
        //                 motor->config.controlMode = Motor::VELOCITY;
        //                 motor->target = 0;
        //             }
        //         }
        break;
    case MODE_DISABLE:
    case MODE_SPRING:
    case MODE_SPIN:
        break;
    }

    foc(&knob->motor, 0, 0);
}

// void KnobSimulatorSetLimitPos(float _min, float _max)
// {
//     limitPositionMin = _min;
//     limitPositionMax = _max;
// }

// void KnobSimulator::ApplyZeroPos(float _angle)
// {
//     if (_angle != 0)
//         zeroPosition = _angle;
//     else
//         zeroPosition = motor->GetEstimateAngle();
// }

// int KnobSimulator::GetEncoderModePos()
// {
//     return std::lround(GetPosition() / (_2PI / (float) encoderDivides));
// }

// void KnobSimulator::SetEnable(bool _en)
// {
//     SetPowerMotor(_en);
//     motor->SetEnable(_en);
// }
