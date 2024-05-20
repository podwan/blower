#ifndef __CURRENT_H
#define __CURRENT_H
#include "userMain.h"
#include "bldcMotor.h"
#define SHUNT_RESISTOR 0.005f                         // 5mR
#define GAIN 7.3333f                                  // opAmp
#define VLOTS_AMPS_RATIO 1.0f / SHUNT_RESISTOR / GAIN // 27.27

#define ADC_MAX 4095.0
#define ADC_REF 3.3f
#define ADC_VLOTS_RADIO ADC_REF / ADC_MAX  //0.0008

#define ADC_2_CURRENT(adc) adc *ADC_VLOTS_RADIO *VLOTS_AMPS_RATIO

void getCurrentOffsets(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b, uint32_t rounds);
void getPhaseCurrents(BldcMotor *motor, uint32_t adc_a, uint32_t adc_b);
void getABCurrents(BldcMotor *motor);
void getDQCurrents(BldcMotor *motor);
#endif