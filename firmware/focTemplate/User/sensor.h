#ifndef __SENSOR_H
#define __SENSOR_H

#include "userMain.h"

#define MAX_INDEX 0 
#define MIN_INDEX 1
#define SUM_INDEX 2
#define AVERAGE_INDEX 3



#define CHN_NUM 1
#define MIN_FRESH_INTEVAL 3 // 3
#define SAMPLE_PERIOD 10
#define ADC_SAMPLE_START(CHN) // tenx get_ad(CHN)   //cms  getAdcValue(CHN)

#define PULL_UP 1

#define NTC_OPEN 1
#define NTC_SHORT 2

void sensoring();
char getTemp(unsigned int *temp);

#endif