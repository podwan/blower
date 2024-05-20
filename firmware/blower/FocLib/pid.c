#include "pid.h"
#include "math_utils.h"

void pidInit(PidController *pidController, float _P, float _I, float _D, float _ramp, float _limit, float _Ts)
{
    pidController->P = _P;
    pidController->I = _I;
    pidController->D = _D;
    pidController->output_ramp = _ramp;
    pidController->limit = _limit;
    pidController->Ts = _Ts;
    pidController->error_prev = 0;
    pidController->output_prev = 0;
    pidController->integral_prev = 0;
}

// PID controller function
float pidOperator(PidController *pidController, float error)
{
    // u(s) = (P + I/s + Ds)e(s)
    // Discrete implementations
    // proportional part
    // u_p  = P *e(k)
    float proportional = pidController->P * error;
    // Tustin transform of the integral part
    // u_ik = u_ik_1  + I*Ts/2*(ek + ek_1)
    float a = 0.5f * (error + pidController->error_prev);
    float b = pidController->I * pidController->Ts;
    float integral = pidController->integral_prev + pidController->I * pidController->Ts * 0.5f * (error + pidController->error_prev);
    // antiwindup - limit the output
    integral = _constrain(integral, -pidController->limit, pidController->limit);
    // Discrete derivation
    // u_dk = D(ek - ek_1)/Ts
    float derivative = pidController->D * (error - pidController->error_prev) / pidController->Ts;

    // sum all the components
    float output = proportional + integral + derivative;
    // antiwindup - limit the output variable
    output = _constrain(output, -pidController->limit, pidController->limit);

    // if output ramp defined
    if (pidController->output_ramp > 0)
    {
        // limit the acceleration by ramping the output
        float output_rate = (output - pidController->output_prev) / pidController->Ts;
        if (output_rate > pidController->output_ramp)
            output = pidController->output_prev + pidController->output_ramp * pidController->Ts;
        else if (output_rate < -pidController->output_ramp)
            output = pidController->output_prev - pidController->output_ramp * pidController->Ts;
    }
    // saving for the next pass
    pidController->integral_prev = integral;
    pidController->output_prev = output;
    pidController->error_prev = error;
    return output;
}

void reset(PidController *pidController)
{
    pidController->integral_prev = 0.0f;
    pidController->output_prev = 0.0f;
    pidController->error_prev = 0.0f;
}
