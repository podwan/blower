#include "motor.h"
#include "voltage.h"
#include "pwm.h"
#include "foc_utils.h"
#include "Adc.h"
#include "current.h"
#include "pid.h"
tGlobal_TypeDef tGlobal;
Motor motor1;

void motorInit()
{
    motor1.state = MOTOR_STOP;
    motor1.voltages.percentMax = MAX_PERCENT;
    motor1.voltages.setPwm = setPwm1;
    tGlobal.OffsetReq = 1;
    CurrentInitialize(&motor1);
    tGlobal.LedStatus = 0;
    motor1.FaultNum = 0;
    motor1.PiId.P = I_KP;
    motor1.PiId.I = I_KI;
    motor1.PiId.limit = I_LIMIT;
}

void motor1Drive()
{
    currentSample(&motor1);
    if (motor1.Tick)
        motor1.Tick--;

    if ((TIM8->SR & 0x00000080) != 0) // BIF = 1, MOE=0  detect whether current overflow
    {
        motor1.FaultNum++;
        if (motor1.FaultNum >= 3)
        {
            motor1.FaultNum = 0;
            motor1.state = MOTOR_STOP;

            Close6Pwm1();
            tGlobal.ErrorCode = 1;
            TIM8->SR &= 0xffffff7f;
        }
        else
        {
            TIM8->SR &= 0xffffff7f;
            TIM8->BDTR |= 0x00008000;
        }
    }
    else
    {
        switch (motor1.state)
        {
        case MOTOR_STOP:

            Close6Pwm1();
            InitAdcOffset();

            tGlobal.LedStatus = 0;

            tGlobal.RunTime = 0;

            if (tGlobal.ErrorCode == 0)
            {
                if (tGlobal.OffsetReq)
                {
                    CalAdcOffset();
                }
                else
                {
                    GetCurrentOffset();
                    motor1.state = MOTOR_START;

                    tGlobal.RunTime = 0;
                    motor1.Tick1s = 25000;
                }
            }

            break;

        case MOTOR_START:
            Open3LowPwm1();

            motor1.Tick = 10000;
            motor1.state = MOTOR_WAIT;
            break;

        case MOTOR_WAIT:
            if (motor1.Tick == 0)
            {
                Close6Pwm1();

                motor1.state = MOTOR_RUN;
            }
            break;

        case MOTOR_RUN:
            Open6WorkPwm1();
            motor1.voltages.percent = 0.15;
            motor1.voltages.eAngle += 0.01;
            if (motor1.voltages.eAngle > _2PI)
                motor1.voltages.eAngle = 0;
            setPhaseVoltage(&motor1.voltages);
            break;
        default:
            motor1.state = MOTOR_STOP;
            break;
        }
    }

    // DAC看波形

    //    DAC->DHR12R1 = motor1.voltages.eAngle ;
    DAC->DHR12R1 = motor1.voltages.CCR1;
}

