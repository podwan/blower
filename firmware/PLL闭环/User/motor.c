#include "motor.h"
#include "svPwm.h"
#include "pwm.h"
#include "foc_utils.h"

Motor motor1;

void motorInit()
{
    motor1.state = MOTOR_START;
    motor1.svPwm.percentMax = MAX_PERCENT;
    motor1.svPwm.setPwm = setPwm1;
}

void motor1Drive()
{
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
            motor1.svPwm.percent = 0.15;
            motor1.svPwm.eAngle += 0.01;
            if (motor1.svPwm.eAngle > _2PI)
                motor1.svPwm.eAngle = 0;
            setSvPwm(&motor1.svPwm, motor1.svPwm.percent, motor1.svPwm.eAngle);
            break;
        default:
            motor1.state = MOTOR_STOP;
            break;
        }
    }

    // DAC看波形

    //    DAC->DHR12R1 = motor1.svPwm.eAngle ;
    DAC->DHR12R1 = motor1.svPwm.CCR1;
}
