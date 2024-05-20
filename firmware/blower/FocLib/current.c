
#include "current.h"
#include "math_utils.h"
#include "comm.h"

// Function finding zero offsets of the ADC
void getCurrentOffsets(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b, uint32_t rounds)
{
    // find adc offset = zero current voltage
    motor->offset_ia = 0;
    motor->offset_ib = 0;
    // read the adc voltage  times ( arbitrary number )
    for (int i = 0; i < rounds; i++)
    {
        motor->offset_ia += ADC_2_CURRENT(adc_a);
        motor->offset_ib += ADC_2_CURRENT(adc_b);
    }
    // calculate the mean offsets
    motor->offset_ia = motor->offset_ia / rounds;
    motor->offset_ib = motor->offset_ib / rounds;

    // FOC_log("[offset_ia]:%f  [offset_ib]:%f\r\n", motor->offset_ia, motor->offset_ib);
    // printf("[offset_ia]:%f  [offset_ib]:%f\r\n", motor->offset_ia, motor->offset_ib);
    FOC_log("[offset_ia]:%f\r\n", motor->offset_ia);
    FOC_log("[offset_ib]:%f\r\n", motor->offset_ib);
    // _dbg_printf("[offset_ia]:%f  [offset_ib]:%f\r\n", motor->offset_ia, motor->offset_ib);
}

// read all three phase currents (if possible 2 or 3)
void getPhaseCurrents(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b)
{
    motor->Ia = ADC_2_CURRENT(adc_a) - motor->offset_ia; // amps
    motor->Ib = ADC_2_CURRENT(adc_b) - motor->offset_ib;
}

/*============================================================================*/
// Clarke变换，计算公式
// Ialpha = Ia
// Ibeta = (Ia + 2Ib)/sqrt(3)
// Ibeta = 1/sqrt(3) * Ia + 1/sqrt(3) * 2Ib
/*============================================================================*/
//   calculating Alpha Beta currents from phase currents
//   - function calculating Clarke transform of the phase currents
void getABCurrents(BldcMotor *motor)
{
    motor->Ialpha = motor->Ia;
    motor->Ibeta = _1_SQRT3 * motor->Ia + _2_SQRT3 * motor->Ib;
}
/*============================================================================*/
// Park变换
// Id = Ialpha * Cosθr + Ibeta * Sinθr
// Iq =Ibeta * Cosθr -Ialpha * Sinθr
/*============================================================================*/
// function used with the foc algorihtm
//   calculating D and Q currents from Alpha Beta currents and electrical angle
//   - function calculating Clarke transform of the phase currents
void getDQCurrents(BldcMotor *motor)
{
    float ct;
    float st;
    _sincos(motor->angle_el, &st, &ct);
    motor->Id = motor->Ialpha * ct + motor->Ibeta * st;
    motor->Iq = motor->Ibeta * ct - motor->Ialpha * st;
}