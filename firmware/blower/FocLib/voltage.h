

#ifndef __VOLTAGE_H
#define __VOLTAGE_H


#include "bldcMotor.h"
void getDQVoltages(BldcMotor *motor);
void getABVoltages(BldcMotor *motor);
void setTorque(BldcMotor *motor, float Uq, float Ud, float angle_el);
void setSVPWM(BldcMotor *motor);
void svpwm_test(BldcMotor *motor, float Uq, float acc);
extern const char sectorRemap[];
#endif