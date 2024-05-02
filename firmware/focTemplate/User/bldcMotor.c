#include "bldcMotor.h"
#include "foc_utils.h"
// Function finding zero offsets of the ADC
void calibrateOffsets(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b)
{
    const int calibration_rounds = 100;
    // find adc offset = zero current voltage
    motor->offset_ia = 0;
    motor->offset_ib = 0;
    // read the adc voltage 1000 times ( arbitrary number )
    for (int i = 0; i < calibration_rounds; i++)
    {
        motor->offset_ia += adc_a;
        motor->offset_ib += adc_b;
    }
    // calculate the mean offsets
    motor->offset_ia = motor->offset_ia / calibration_rounds;
    motor->offset_ib = motor->offset_ib / calibration_rounds;
}

// read all three phase currents (if possible 2 or 3)
void getPhaseCurrents(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b)
{
    motor->Ia = (adc_a - motor->offset_ia) * VLOTS_AMPS_RATIO; // amps
    motor->Ib = (adc_b - motor->offset_ib) * VLOTS_AMPS_RATIO; // amps
}

// function used with the foc algorihtm
//   calculating Alpha Beta currents from phase currents
//   - function calculating Clarke transform of the phase currents
static void getABCurrents(BldcMotor *motor)
{
    motor->Ialpha = motor->Ia;
    // currents->Ibeta = (currents->Ia + 2.0f * currents->Ib) / _SQRT3;
    motor->Ibeta = _1_SQRT3 * motor->Ia + _2_SQRT3 * motor->Ib;
}

// function used with the foc algorihtm
//   calculating D and Q currents from Alpha Beta currents and electrical angle
//   - function calculating Clarke transform of the phase currents
static void getDQCurrents(BldcMotor *motor)
{
    float ct;
    float st;
    _sincos(motor->angle_el, &st, &ct);
    motor->Id = motor->Ialpha * ct + motor->Ibeta * st;
    motor->Iq = motor->Ibeta * ct - motor->Ialpha * st;
}

void getDQVoltages(BldcMotor *motor)
{
    
    // float Uq = PIDCalculate(&pid_Iq, Iq_set, current.q);
    // float Ud = PIDCalculate(&pid_Id, Id_set, current.d);
}
// PidController pid_id;
// PidController pid_iq;
